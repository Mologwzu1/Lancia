#include "writer_agent.h"
#include "cyber/time/time.h"
#include <fstream>
#include <stack>
#include <sys/stat.h>

namespace cyber_y {
namespace ypsilon {
using cyber_y::proto::Role;
using apollo::cyber::Time;

const char* WriterAgent::SHM_NAME = "output/tmp/cyber_y/writer_shm";
const size_t WriterAgent::SHM_SIZE = 1024 * 1024; // 1MB

WriterAgent::WriterAgent() :
    shm_addr_(nullptr),
    shm_size_(SHM_SIZE),
    shm_key_(0),
    shm_id_(-1),
    is_creator_(false),
    shared_data_(nullptr) {
    log_file_ = "output/logs/cybery_" + Time::Now().ToString() + ".log";
    Init();
}

WriterAgent::~WriterAgent() {
    SaveLogs();
    DetachSharedMemory();
}

WriterAgent& WriterAgent::Instance() {
    static WriterAgent instance;
    return instance;
}

void WriterAgent::Init() {
    // 确保output/tmp目录存在
    mkdir("output/tmp", 0755);
    
    if (!CreateSharedMemory()) {
        AttachSharedMemory();
    }
}

bool WriterAgent::CreateSharedMemory() {
    shm_key_ = ftok(SHM_NAME, 0);
    if (shm_key_ == -1) {
        return false;
    }
    
    shm_id_ = shmget(shm_key_, shm_size_, IPC_CREAT | IPC_EXCL | 0666);
    if (shm_id_ == -1) {//std::cerr << strerror(errno) << std::endl;
        return false;
    }
    
    shm_addr_ = shmat(shm_id_, nullptr, 0);
    if (shm_addr_ == (void*)-1) {//std::cerr << "shmat failed: " << strerror(errno) << std::endl;
        shmctl(shm_id_, IPC_RMID, nullptr);
        return false;
    }
    //std::cerr << "CreateSharedMemory" << std::endl;
    // 初始化共享内存
    shared_data_ = new (shm_addr_) SharedData();
    shared_data_->writer_count = 0;
    is_creator_ = true;
    return true;
}

bool WriterAgent::AttachSharedMemory() {
    shm_key_ = ftok(SHM_NAME, 0);
    if (shm_key_ == -1) {
        return false;
    }
    
    shm_id_ = shmget(shm_key_, shm_size_, 0666);
    if (shm_id_ == -1) {
        return false;
    }
    
    shm_addr_ = shmat(shm_id_, nullptr, 0);
    if (shm_addr_ == (void*)-1) {
        return false;
    }
    
    shared_data_ = reinterpret_cast<SharedData*>(shm_addr_);
    return true;
}

void WriterAgent::DetachSharedMemory() {
    if (shm_addr_ != nullptr) {
        shmdt(shm_addr_);
        shm_addr_ = nullptr;
    }
    
    // 只有创建者才删除共享内存
    if (is_creator_ && shm_id_ != -1) {
        shmctl(shm_id_, IPC_RMID, nullptr);
        shm_id_ = -1;
    }
}

LogWriter& WriterAgent::GetLogWriter(const uint64_t node_id) {
    if (writer_map_.find(node_id) == writer_map_.end()) {
        writer_map_[node_id] = LogWriter();
        // 更新共享内存中的writer_count
        if (shared_data_) {
            shared_data_->writer_count++;
        }
    }
    return writer_map_[node_id];
}

void WriterAgent::SaveLogs() {
    std::ofstream of(log_file_, std::ios::trunc);
    
    for (auto& writer_pair : writer_map_) {//td::cerr << "CreateSharedMemory" << std::endl;
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