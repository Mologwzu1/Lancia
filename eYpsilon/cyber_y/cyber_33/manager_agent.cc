#include "manager_agent.h"
#include "cyber/time/time.h"
#include <queue>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <cstring>
#include <fstream>
#include <vector>
#include <iostream>

namespace cyber_y {
namespace ypsilon {
using apollo::cyber::Time;
    
    const char* ManagerAgent::SHM_NAME = "output/tmp/cyber_y/manager_shm";
    const size_t ManagerAgent::SHM_SIZE = 64 * 1024; // 64KB

    ManagerAgent::ManagerAgent() :
        shm_addr_(nullptr),
        shm_size_(SHM_SIZE),
        shm_key_(0),
        shm_id_(-1),
        is_creator_(false),
        shared_data_(nullptr) {
        file_root_ = "output/logs/cybery_";
        log_file_ = Time::Now().ToString() + ".log";
        indicator_log_file_ = "indic_" + log_file_;
        InitSharedMemory();
    }
    
    ManagerAgent::~ManagerAgent() {
        SaveLogs();
        DetachSharedMemory();
    }
    
    void ManagerAgent::Init() {
        if (shm_addr_ != nullptr) {
            shmdt(shm_addr_);
            shm_addr_ = nullptr;
        }
        shmctl(shm_id_, IPC_RMID, nullptr);
        shm_id_ = -1;
    }
    void ManagerAgent::WriterRegist(const uint64_t channel_id, const uint64_t writer_id){
        // 先从共享内存读取最新数据
        if (shared_data_) {
            DeserializeManagerMap();
        }
        if(!ServiceFind(channel_id)){
            return;
        }
        manager_map_[channel_id].WriterRegist(writer_id);
        // 添加同步到共享内存
        if (shared_data_) {
            SerializeManagerMap();
        }
    }
    void ManagerAgent::ReaderRegist(const uint64_t channel_id, const uint64_t reader_id){
        // 先从共享内存读取最新数据
        if (shared_data_) {
            DeserializeManagerMap();
        }
        if(!ServiceFind(channel_id)){
            return;
        }
        manager_map_[channel_id].ReaderRegist(reader_id);
        // 添加同步到共享内存
        if (shared_data_) {
            SerializeManagerMap();
        }
    }   
    void ManagerAgent::WriterCancel(const uint64_t channel_id, const uint64_t writer_id){
        // 先从共享内存读取最新数据
        if (shared_data_) {
            DeserializeManagerMap();
        }
        if(!ServiceFind(channel_id)){
            return;
        }
        manager_map_[channel_id].WriterCancel(writer_id);
        // 添加同步到共享内存
        if (shared_data_) {
            SerializeManagerMap();
        }
    }
    void ManagerAgent::ReaderCancel(const uint64_t channel_id, const uint64_t reader_id){
        // 先从共享内存读取最新数据
        if (shared_data_) {
            DeserializeManagerMap();
        }
        if(!ServiceFind(channel_id)){
            return;
        }
        manager_map_[channel_id].ReaderCancel(reader_id);
        // 添加同步到共享内存
        if (shared_data_) {
            SerializeManagerMap();
        }
    }
    
    bool ManagerAgent::ServiceFind(const uint64_t channel_id){
        if(manager_map_.find(channel_id) == manager_map_.end()){
            MonitorManager manager;
            manager_map_[channel_id] = manager;
            // 添加同步到共享内存
            if (shared_data_) {
                shared_data_->manager_count++;
                SerializeManagerMap();
            }
        }
        return manager_map_.find(channel_id) != manager_map_.end();
    }
    void ManagerAgent::WriteArrange(IndicatorLog& log, const uint64_t interval){
        // 先从共享内存读取最新数据
        if (shared_data_) {
            DeserializeManagerMap();
        }
        if(!ServiceFind(log.channel_id())){
            return;
        }
        
        log.set_cpu_usage(GetCpuUsage());
        log.set_shm_usage(static_cast<double>(shared_data_->data_size) * 100 / SHM_SIZE);
        log.set_interval(interval*1000*1000);
        
        manager_map_[log.channel_id()].WriteRqst(log);
        // 同步到共享内存
        if (shared_data_) {
            SerializeManagerMap();
        }
    }
    void ManagerAgent::ReadArrange(const uint64_t channel_id){
        // 先从共享内存读取最新数据
        if (shared_data_) {
            DeserializeManagerMap();
        }
        if(!ServiceFind(channel_id)){
            return;
        }
        manager_map_[channel_id].ReadRqst();
        // 同步到共享内存
        if (shared_data_) {
            SerializeManagerMap();
        }
    }
    void ManagerAgent::SaveLogs(){
        of_.open(file_root_ + log_file_, std::ios::trunc);
        for(auto& manager_pair : manager_map_){
            std::queue<IndicatorLog> log_queue = manager_pair.second.ReturnLogs();
            for(; !log_queue.empty(); log_queue.pop()){
                const IndicatorLog log = log_queue.front();
                of_ << log.node_name() << "\t";
                of_ << log.node_id() << "\t";
                of_ << log.channel_name() << "\t";
                of_ << log.channel_id() << "\t";
                of_ << log.cpu_usage() << "\t";
                of_ << log.shm_usage() << "\t";
                of_ << log.write_time() << "\t";
                of_ << log.enqueue_time() << "\t";
                of_ << log.dequeue_time() << "\t";
                of_ << log.read_time() << "\n";
            }
        }
        of_.close();
    }
    void ManagerAgent::SaveIndicatorLogs(){
        of_.open(file_root_ + indicator_log_file_, std::ios::trunc);
        for(auto& manager_pair : manager_map_){
            std::queue<IndicatorLog> log_queue = manager_pair.second.ReturnLogs();
            std::map<uint64_t, std::queue<IndicatorLog>> node_map;
            for(; !log_queue.empty(); log_queue.pop()){
                node_map[log_queue.front().node_id()].push(log_queue.front());
            }
            for(auto& node_pair : node_map){
                IndicatorLog last = node_pair.second.front();
                node_pair.second.pop();
                
                for(;!node_pair.second.empty();node_pair.second.pop()){
                    IndicatorLog log = node_pair.second.front();
                    if(log.enqueue_time() != 0 && log.dequeue_time() != 0 && log.read_time() != 0){
                        of_ << log.node_name() << "\t";
                        of_ << log.node_id() << "\t";
                        of_ << log.channel_name() << "\t";
                        of_ << log.channel_id() << "\t";
                        of_ << log.cpu_usage() << "\t";
                        of_ << log.shm_usage() << "\t";
                        of_ << log.write_time() - last.write_time() - log.interval() << "\t";
                        of_ << log.dequeue_time() - log.enqueue_time() << "\t";
                        of_ << (log.read_time() - log.write_time()) - (log.dequeue_time() - log.enqueue_time()) << "\n";
                    }
                    last = log;
                }
            }
        }
        of_.close();
    }
    void ManagerAgent::WriteArrange(const RoleAttributes node_attr_, const uint64_t interval){
        // 先从共享内存读取最新数据
        if (shared_data_) {
            DeserializeManagerMap();
        }
        if(!ServiceFind(node_attr_.channel_id())){
            return;
        }
        IndicatorLog log;
        log.set_node_name(node_attr_.node_name());
        log.set_node_id(node_attr_.node_id());
        log.set_channel_name(node_attr_.channel_name());
        log.set_channel_id(node_attr_.channel_id());

        log.set_cpu_usage(GetCpuUsage());
        log.set_shm_usage(static_cast<double>(shared_data_->data_size) * 100 / SHM_SIZE);
        log.set_interval(interval*1000*1000);
        
        manager_map_[log.channel_id()].WriteRqst(log);
        // 同步到共享内存
        if (shared_data_) {
            SerializeManagerMap();
        }
    }

    void ManagerAgent::ReadArrange(const RoleAttributes node_attr_){
        // 先从共享内存读取最新数据
        if (shared_data_) {
            DeserializeManagerMap();
        }
        if(!ServiceFind(node_attr_.channel_id())){
            return;
        }
        manager_map_[node_attr_.channel_id()].ReadRqst();
        // 同步到共享内存
        if (shared_data_) {
            SerializeManagerMap();
        }
    }

    void ManagerAgent::InitSharedMemory() {
        // 确保output/tmp目录存在
        mkdir("output/tmp", 0755);
        mkdir("output/tmp/cyber_y", 0755);
        
        if (!CreateSharedMemory()) {
            AttachSharedMemory();
            // 从共享内存加载数据到本地map
            DeserializeManagerMap();
        }
    }
    
    bool ManagerAgent::CreateSharedMemory() {
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
        shared_data_->manager_count = 0;
        shared_data_->data_size = 0;
        is_creator_ = true;
        return true;
    }
    
    bool ManagerAgent::AttachSharedMemory() {
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
    
    void ManagerAgent::DetachSharedMemory() {
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
    
    void ManagerAgent::SerializeManagerMap() {
        if (!shared_data_) {
            return;
        }
        
        std::string result;
        
        // 序列化manager_map_
        int map_size = manager_map_.size();
        result.append(reinterpret_cast<const char*>(&map_size), sizeof(map_size));
        
        for (const auto& pair : manager_map_) {
            // 序列化channel_id
            uint64_t channel_id = pair.first;
            result.append(reinterpret_cast<const char*>(&channel_id), sizeof(channel_id));
            
            // 序列化MonitorManager
            std::string manager_data = pair.second.Serialize();
            int manager_size = manager_data.size();
            result.append(reinterpret_cast<const char*>(&manager_size), sizeof(manager_size));
            result.append(manager_data);
        }
        
        // 检查共享内存大小是否足够
        if (result.size() > SHM_SIZE - sizeof(SharedData)) {
            return; // 共享内存不足
        }
        
        // 写入共享内存
        shared_data_->manager_count = manager_map_.size();
        shared_data_->data_size = result.size();
        memcpy(shared_data_->data, result.data(), result.size());
    }
    
    void ManagerAgent::DeserializeManagerMap() {
        if (!shared_data_ || shared_data_->data_size == 0) {
            return;
        }
        
        std::string data(shared_data_->data, shared_data_->data_size);
        size_t offset = 0;
        
        // 反序列化manager_map_
        int map_size;
        memcpy(&map_size, data.data() + offset, sizeof(map_size));
        offset += sizeof(map_size);
        
        manager_map_.clear();
        for (int i = 0; i < map_size; i++) {
            // 反序列化channel_id
            uint64_t channel_id;
            memcpy(&channel_id, data.data() + offset, sizeof(channel_id));
            offset += sizeof(channel_id);
            
            // 反序列化MonitorManager
            int manager_size;
            memcpy(&manager_size, data.data() + offset, sizeof(manager_size));
            offset += sizeof(manager_size);
            
            std::string manager_data = data.substr(offset, manager_size);
            offset += manager_size;
            
            MonitorManager manager;
            manager.Deserialize(manager_data);
            manager_map_[channel_id] = manager; 
        }
    }
    
    double ManagerAgent::GetCpuUsage() {
        // 读取/proc/stat文件获取CPU使用情况
        std::ifstream proc_stat("/proc/stat");
        std::string line;
        if (!proc_stat.is_open()) {
            return 0;
        }
        
        // 读取第一行（CPU总体使用情况）
        std::getline(proc_stat, line);
        proc_stat.close();
        
        // 解析CPU使用数据
        std::istringstream iss(line);
        std::string cpu;
        iss >> cpu;
        
        std::vector<unsigned long long> times;
        unsigned long long time;
        while (iss >> time) {
            times.push_back(time);
        }
        
        if (times.size() < 4) {
            return 0;
        }
        
        // 计算总时间和空闲时间
        unsigned long long total_time = 0;
        for (size_t i = 0; i < times.size(); i++) {
            total_time += times[i];
        }
        unsigned long long idle_time = times[3]; // 空闲时间
        
        // 计算CPU使用率（百分比）
        return (total_time - idle_time) * 100 / total_time;
    }
    
} // namespace ypsilon

} // namespace cyber_y
