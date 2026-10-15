#include "monitor_agent.h"
#include "cyber/time/time.h"
#include <queue>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <cstring>

namespace cyber_y {
namespace ypsilon {
using apollo::cyber::Time;

    // 共享内存相关常量
    const char* MonitorAgent::SHM_NAME = "output/tmp/cyber_y/monitor_shm";
    const size_t MonitorAgent::SHM_SIZE = 512 * 1024 * 1024; // 512MB
    
    MonitorAgent::MonitorAgent() :
        shm_addr_(nullptr),
        shm_size_(SHM_SIZE),
        shm_key_(0),
        shm_id_(-1),
        is_creator_(false),
        shared_data_(nullptr) {
        file_root_ = "output/logs/";
        log_file_ = "cybery_indic_" + Time::Now().ToString() + ".log";
        InitSharedMemory();
    }
    
    MonitorAgent::~MonitorAgent() {
        SaveLogs();
        DetachSharedMemory();
    }
    
    void MonitorAgent::InitSharedMemory() {
        // 确保output/tmp目录存在
        mkdir("output/tmp", 0755);
        mkdir("output/tmp/cyber_y", 0755);
        
        if (!CreateSharedMemory()) {
            AttachSharedMemory();
            // 从共享内存加载数据到本地map
            DeserializeMonitorMap();
        }
    }
    
    void MonitorAgent::SerializeMonitorMap() {
        if (!shared_data_) {
            return;
        }
        
        std::string result;
        
        // 序列化monitor_map_
        int map_size = monitor_map_.size();
        result.append(reinterpret_cast<const char*>(&map_size), sizeof(map_size));
        
        for (const auto& pair : monitor_map_) {
            // 序列化channel_id
            uint64_t channel_id = pair.first;
            result.append(reinterpret_cast<const char*>(&channel_id), sizeof(channel_id));
            
            // 序列化IndicatorMonitor
            std::string monitor_data = pair.second.Serialize();
            int monitor_size = monitor_data.size();
            result.append(reinterpret_cast<const char*>(&monitor_size), sizeof(monitor_size));
            result.append(monitor_data);
        }
        
        // 检查共享内存大小是否足够
        if (result.size() > SHM_SIZE - sizeof(SharedData)) {
            return; // 共享内存不足
        }
        
        // 写入共享内存
        shared_data_->monitor_count = monitor_map_.size();
        shared_data_->data_size = result.size();
        memcpy(shared_data_->data, result.data(), result.size());
    }
    
    void MonitorAgent::DeserializeMonitorMap() {
        if (!shared_data_ || shared_data_->data_size == 0) {
            return;
        }
        
        std::string data(shared_data_->data, shared_data_->data_size);
        size_t offset = 0;
        
        // 反序列化monitor_map_
        int map_size;
        memcpy(&map_size, data.data() + offset, sizeof(map_size));
        offset += sizeof(map_size);
        
        monitor_map_.clear();
        for (int i = 0; i < map_size; i++) {
            // 反序列化channel_id
            uint64_t channel_id;
            memcpy(&channel_id, data.data() + offset, sizeof(channel_id));
            offset += sizeof(channel_id);
            
            // 反序列化IndicatorMonitor
            int monitor_size;
            memcpy(&monitor_size, data.data() + offset, sizeof(monitor_size));
            offset += sizeof(monitor_size);
            
            std::string monitor_data = data.substr(offset, monitor_size);
            offset += monitor_size;
            
            IndicatorMonitor monitor;
            monitor.Deserialize(monitor_data);
            monitor_map_[channel_id] = monitor;
        }
    }
    
    bool MonitorAgent::CreateSharedMemory() {
        shm_key_ = ftok(SHM_NAME, 0);
        if (shm_key_ == -1) {
            return false;
        }
        
        shm_id_ = shmget(shm_key_, shm_size_, IPC_CREAT | IPC_EXCL | 0666);
        if (shm_id_ == -1) {
            return false;
        }
        
        shm_addr_ = shmat(shm_id_, nullptr, 0);
        if (shm_addr_ == (void*)-1) {
            shmctl(shm_id_, IPC_RMID, nullptr);
            return false;
        }
        
        // 初始化共享内存
        shared_data_ = new (shm_addr_) SharedData();
        shared_data_->monitor_count = 0;
        shared_data_->data_size = 0;
        is_creator_ = true;
        return true;
    }
    
    bool MonitorAgent::AttachSharedMemory() {
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
    
    void MonitorAgent::DetachSharedMemory() {
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
    
    bool MonitorAgent::ServiceFind(const uint64_t channel_id){
        if(monitor_map_.find(channel_id) == monitor_map_.end()){
            IndicatorMonitor monitor;
            monitor_map_[channel_id] = monitor;
            
            // 更新共享内存
            if (shared_data_) {
                shared_data_->monitor_count++;
                SerializeMonitorMap();
            }
        }
        return monitor_map_.find(channel_id) != monitor_map_.end();
    }
    
    void MonitorAgent::WriteRqst(const JuniorLog& log){
        // 先从共享内存读取最新数据
        if (shared_data_) {
            DeserializeMonitorMap();
        }
        if(!ServiceFind(log.channel_id())){
            return;
        }
        monitor_map_[log.channel_id()].WriteLog(log);
        /*std::cout << "WriteRqst: channel_id=" << log.channel_id() 
                  << ", cache_size=" << monitor_map_[log.channel_id()].Serialize().size() << std::endl;*/
        // 同步到共享内存
        if (shared_data_) {
            SerializeMonitorMap();
        }
    }
    
    void MonitorAgent::ReadRqst(const JuniorLog& log){
        // 先从共享内存读取最新数据
        if (shared_data_) {
            DeserializeMonitorMap();
        }
        if(!ServiceFind(log.channel_id())){
            return;
        }
        monitor_map_[log.channel_id()].ReadLog(log);
        /*std::cout << "ReadRqst: channel_id=" << log.channel_id()
                  << ", cache_size=" << monitor_map_[log.channel_id()].Serialize().size() << std::endl;*/
        // 同步到共享内存
        if (shared_data_) {
            SerializeMonitorMap();
        }
    }
    
    void MonitorAgent::SaveLogs(){
        of_.open(file_root_ + log_file_, std::ios::trunc);
        for(auto& monitor_pair : monitor_map_){
            std::queue<JuniorLog> log_queue = monitor_pair.second.ReturnLogs();
            for(; !log_queue.empty(); log_queue.pop()){
                const JuniorLog log = log_queue.front();
                of_ << log.node_name() << "\t";
                of_ << log.node_id() << "\t";
                of_ << log.channel_name() << "\t";
                of_ << log.channel_id() << "\t";
                of_ << log.write_time() << "\t";
                of_ << log.read_time() << "\n";
            }
        }
        of_.close();
    }

    void MonitorAgent::Init() {
        if (shm_addr_ != nullptr) {
            shmdt(shm_addr_);
            shm_addr_ = nullptr;
        }
        shmctl(shm_id_, IPC_RMID, nullptr);
        shm_id_ = -1;
    }
} // namespace ypsilon

} // namespace cyber_y
