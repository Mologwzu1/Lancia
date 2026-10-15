#include <unistd.h>
#include <cstring>
#include "indicator_monitor.h"

namespace cyber_y {
namespace ypsilon {

    bool IndicatorMonitor::JudgeLog(const JuniorLog& log0, const JuniorLog& log1){
        return log0.channel_id() == log1.channel_id();
    }
    void IndicatorMonitor::WriteLog(const JuniorLog& log){
        log_cache_queue_.push(log);
    }
    void IndicatorMonitor::ReadLog(const JuniorLog& log){
        while (log_cache_queue_.empty()) {sleep(1);}
        JuniorLog log_cache = log_cache_queue_.front();
        while(!JudgeLog(log, log_cache)) {sleep(1);}
        log_cache.set_read_time(log.read_time());
        log_cache_queue_.pop();
        log_queue_.push(log_cache);
        /*if (log_cache_queue_.empty()) {return;}
        
        // 遍历队列中的所有元素，找到匹配的log
        std::queue<JuniorLog> temp_queue;
        
        while (!log_cache_queue_.empty()) {
            JuniorLog log_cache = log_cache_queue_.front();
            log_cache_queue_.pop();
            
            if (JudgeLog(log, log_cache)) {
                log_cache.set_read_time(log.read_time());
                log_queue_.push(log_cache);
            } else {
                temp_queue.push(log_cache);
            }
        }
        
        // 将未匹配的元素放回队列
        while (!temp_queue.empty()) {
            log_cache_queue_.push(temp_queue.front());
            temp_queue.pop();
        }*/
    }
    std::queue<JuniorLog> IndicatorMonitor::ReturnLogs(){
        /*for(; !log_cache_queue_.empty(); log_cache_queue_.pop()){
            log_queue_.push(log_cache_queue_.front());
        }*/
        return log_queue_;
    }
    
    std::string IndicatorMonitor::Serialize() const {
        std::string result;
        
        // 序列化log_cache_queue_
        int cache_size = log_cache_queue_.size();
        result.append(reinterpret_cast<const char*>(&cache_size), sizeof(cache_size));
        
        // 使用临时队列来避免修改原始队列
        std::queue<JuniorLog> temp_cache = log_cache_queue_;
        while (!temp_cache.empty()) {
            std::string log_data;
            temp_cache.front().SerializeToString(&log_data);
            int log_size = log_data.size();
            result.append(reinterpret_cast<const char*>(&log_size), sizeof(log_size));
            result.append(log_data);
            temp_cache.pop();
        }
        
        // 序列化log_queue_
        int queue_size = log_queue_.size();
        result.append(reinterpret_cast<const char*>(&queue_size), sizeof(queue_size));
        
        // 使用临时队列来避免修改原始队列
        std::queue<JuniorLog> temp_queue = log_queue_;
        while (!temp_queue.empty()) {
            std::string log_data;
            temp_queue.front().SerializeToString(&log_data);
            int log_size = log_data.size();
            result.append(reinterpret_cast<const char*>(&log_size), sizeof(log_size));
            result.append(log_data);
            temp_queue.pop();
        }
        
        return result;
    }
    
    void IndicatorMonitor::Deserialize(const std::string& data) {
        size_t offset = 0;
        
        // 反序列化log_cache_queue_
        int cache_size;
        memcpy(&cache_size, data.data() + offset, sizeof(cache_size));
        offset += sizeof(cache_size);
        
        log_cache_queue_ = std::queue<JuniorLog>();
        for (int i = 0; i < cache_size; i++) {
            int log_size;
            memcpy(&log_size, data.data() + offset, sizeof(log_size));
            offset += sizeof(log_size);
            
            std::string log_data = data.substr(offset, log_size);
            offset += log_size;
            
            JuniorLog log;
            log.ParseFromString(log_data);
            log_cache_queue_.push(log);
        }
        
        // 反序列化log_queue_
        int queue_size;
        memcpy(&queue_size, data.data() + offset, sizeof(queue_size));
        offset += sizeof(queue_size);
        
        log_queue_ = std::queue<JuniorLog>();
        for (int i = 0; i < queue_size; i++) {
            int log_size;
            memcpy(&log_size, data.data() + offset, sizeof(log_size));
            offset += sizeof(log_size);
            
            std::string log_data = data.substr(offset, log_size);
            offset += log_size;
            
            JuniorLog log;
            log.ParseFromString(log_data);
            log_queue_.push(log);
        }
    }

} // namespace ypsilon

} // namespace cyber_y