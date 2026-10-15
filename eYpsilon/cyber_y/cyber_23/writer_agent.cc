#include "writer_agent.h"
#include "cyber/time/time.h"
#include <fstream>
#include <stack>
#include <sys/stat.h>

namespace cyber_y {
namespace ypsilon {
using cyber_y::proto::Role;
using apollo::cyber::Time;

const char* WriterAgent::ROOT_DIR = "output/logs";
const char* WriterAgent::SHM_NAME = "output/tmp";
const size_t WriterAgent::SHM_SIZE = 1024 * 1024; // 1MB

WriterAgent::WriterAgent() :
    writer_map_(),
    capsule_id_(-1) {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        process_shm_[i].shm_addr_ = nullptr;
        process_shm_[i].shm_size_ = SHM_SIZE;
        process_shm_[i].shm_key_ = 0;
        process_shm_[i].shm_id_ = -1;
        process_shm_[i].is_creator_ = false;
        process_shm_[i].shared_data_ = nullptr;
    }
    // 自动分配capsule_id
    AssignCapsuleId();
    Init();
}

WriterAgent::~WriterAgent() {
    SaveLogs();
    for (int i = 0; i < MAX_PROCESSES; i++) {
        DetachSharedMemory(i);
    }
}

WriterAgent& WriterAgent::Instance() {
    static WriterAgent instance;
    return instance;
}

void WriterAgent::AssignCapsuleId() {
    // 遍历0-15的capsule_id，寻找可用的
    for (int i = 0; i < MAX_PROCESSES; i++) {
        char shm_name[256];
        snprintf(shm_name, sizeof(shm_name), "%s/%d", SHM_NAME, i);
        
        // 检查目录是否存在
        struct stat st;
        if (stat(shm_name, &st) == 0 && S_ISDIR(st.st_mode)) {
            // 目录存在，尝试附加共享内存
            key_t shm_key = ftok(shm_name, i);
            if (shm_key != -1) {
                int shm_id = shmget(shm_key, SHM_SIZE, 0666);
                if (shm_id == -1) {
                    // 共享内存不存在，说明该capsule_id可用
                    capsule_id_ = i;
                    return;
                }
            }
        }
    }
    
    // 如果所有capsule_id都被使用，使用默认值0
    capsule_id_ = 0;
    std::cout << "AssignCapsuleId: using default 0" << std::endl;
}

void WriterAgent::Init() {
    // 确保当前进程的目录存在
    char process_dir[256];
    snprintf(process_dir, sizeof(process_dir), "%s/%d", SHM_NAME, capsule_id_);
    mkdir(process_dir, 0755);
    
    // 为当前进程分配共享内存
    if (!CreateSharedMemory(capsule_id_)) {
        AttachSharedMemory(capsule_id_);
    }
}

bool WriterAgent::CreateSharedMemory(int capsule_id) {
    if (capsule_id < 0 || capsule_id >= MAX_PROCESSES) {
        return false;
    }
    
    char shm_name[256];
    snprintf(shm_name, sizeof(shm_name), "%s/%d", SHM_NAME, capsule_id);
    
    process_shm_[capsule_id].shm_key_ = ftok(shm_name, capsule_id);
    if (process_shm_[capsule_id].shm_key_ == -1) {
        return false;
    }
    
    process_shm_[capsule_id].shm_id_ = shmget(process_shm_[capsule_id].shm_key_, 
                                               process_shm_[capsule_id].shm_size_, 
                                               IPC_CREAT | IPC_EXCL | 0666);
    if (process_shm_[capsule_id].shm_id_ == -1) {
        return false;
    }
    
    process_shm_[capsule_id].shm_addr_ = shmat(process_shm_[capsule_id].shm_id_, nullptr, 0);
    if (process_shm_[capsule_id].shm_addr_ == (void*)-1) {
        shmctl(process_shm_[capsule_id].shm_id_, IPC_RMID, nullptr);
        return false;
    }
    
    process_shm_[capsule_id].shared_data_ = new (process_shm_[capsule_id].shm_addr_) ProcessSharedMemory::SharedData();
    process_shm_[capsule_id].shared_data_->writer_count = 0;
    process_shm_[capsule_id].is_creator_ = true;
    return true;
}

bool WriterAgent::AttachSharedMemory(int capsule_id) {
    if (capsule_id < 0 || capsule_id >= MAX_PROCESSES) {
        return false;
    }
    
    char shm_name[256];
    snprintf(shm_name, sizeof(shm_name), "%s/%d", SHM_NAME, capsule_id);
    
    process_shm_[capsule_id].shm_key_ = ftok(shm_name, capsule_id);
    if (process_shm_[capsule_id].shm_key_ == -1) {
        return false;
    }
    
    process_shm_[capsule_id].shm_id_ = shmget(process_shm_[capsule_id].shm_key_, 
                                               process_shm_[capsule_id].shm_size_, 
                                               0666);
    if (process_shm_[capsule_id].shm_id_ == -1) {
        return false;
    }
    
    process_shm_[capsule_id].shm_addr_ = shmat(process_shm_[capsule_id].shm_id_, nullptr, 0);
    if (process_shm_[capsule_id].shm_addr_ == (void*)-1) {
        return false;
    }
    
    process_shm_[capsule_id].shared_data_ = reinterpret_cast<ProcessSharedMemory::SharedData*>(process_shm_[capsule_id].shm_addr_);
    return true;
}

void WriterAgent::DetachSharedMemory(int capsule_id) {
    if (capsule_id < 0 || capsule_id >= MAX_PROCESSES) {
        return;
    }
    
    if (process_shm_[capsule_id].shm_addr_ != nullptr) {
        shmdt(process_shm_[capsule_id].shm_addr_);
        process_shm_[capsule_id].shm_addr_ = nullptr;
    }
    
    // 只有创建者才删除共享内存
    if (process_shm_[capsule_id].is_creator_ && process_shm_[capsule_id].shm_id_ != -1) {
        shmctl(process_shm_[capsule_id].shm_id_, IPC_RMID, nullptr);
        process_shm_[capsule_id].shm_id_ = -1;
    }
}

LogWriter& WriterAgent::GetLogWriter(const uint64_t node_id) { 
    // 确保当前进程的共享内存已分配
    if (process_shm_[capsule_id_].shm_addr_ == nullptr) {
        if (!CreateSharedMemory(capsule_id_)) {
            if (!AttachSharedMemory(capsule_id_)) {
                // 如果无法创建或附加共享内存，仍然返回LogWriter，但不使用共享内存
            }
        }
    }
    
    if (writer_map_.find(node_id) == writer_map_.end()) {
        writer_map_[node_id] = LogWriter();
        if (process_shm_[capsule_id_].shared_data_) {
            process_shm_[capsule_id_].shared_data_->writer_count++;
        }
    }
    return writer_map_[node_id];
}

void WriterAgent::SaveLogs() {
    // 确保当前进程的目录存在
    char log_dir[256];
    snprintf(log_dir, sizeof(log_dir), "%s/%d/cybery_%s.log", 
             ROOT_DIR, capsule_id_, Time::Now().ToString().c_str());
    //mkdir(log_dir, 0755);
    // 所有进程都保存自己的日志
    std::ofstream of(log_dir, std::ios::trunc);
    
    for (auto& writer_pair : writer_map_) {
        std::stack<IndicatorLog> log_stack = writer_pair.second.Logs();
        
        // 直接遍历日志栈
        std::stack<IndicatorLog> temp_stack = log_stack;
        while (!temp_stack.empty()) {
            const IndicatorLog& log = temp_stack.top();
            of << log.node_name() << "\t";
            of << log.node_id() << "\t";
            of << log.channel_name() << "\t";
            of << log.channel_id() << "\t";
            if (log.role() == Role::WRITER) {
                of << "WRITER" << "\t";
            }
            else if (log.role() == Role::READER) {
                of << "READER" << "\t";
            }
            else {
                of << "UNKNOWN" << "\t";
            }
            of << log.exec_time() << "\n";
            temp_stack.pop();
        }
    }
    
    of.close();
}

} // namespace ypsilon
} // namespace cyber_y