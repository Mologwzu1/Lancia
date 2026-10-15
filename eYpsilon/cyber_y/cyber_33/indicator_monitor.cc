#include <unistd.h>
#include <cstring>
#include "cyber/time/time.h"
#include "indicator_monitor.h"

namespace cyber_y {
namespace ypsilon {
using apollo::cyber::Time;

    void IndicatorMonitor::WriteLostLog(IndicatorLog& log){
        log_queue_.push(log);
    }
        
    void IndicatorMonitor::WriteLog(IndicatorLog& log){
        log.set_enqueue_time(Time::Now().ToNanosecond());
        log_cache_queue_.push(log);
    }
    void IndicatorMonitor::ReadLog(){
        while (log_cache_queue_.empty()) {sleep(1);}
        IndicatorLog log_cache = log_cache_queue_.front();
        if(log_cache.dequeue_time() == 0){
            log_cache.set_dequeue_time(Time::Now().ToNanosecond());
        }
        log_cache_queue_.pop();
        if (!log_cache_queue_.empty()) {std::cout << "Code3" << std::endl;
            log_cache_queue_.front().set_dequeue_time(Time::Now().ToNanosecond());
        }
        log_cache.set_read_time(Time::Now().ToNanosecond());
        log_queue_.push(log_cache);
    }

    std::queue<IndicatorLog> IndicatorMonitor::ReturnLogs(){
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
        std::queue<IndicatorLog> temp_cache = log_cache_queue_;
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
        std::queue<IndicatorLog> temp_queue = log_queue_;
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
        
        log_cache_queue_ = std::queue<IndicatorLog>();
        for (int i = 0; i < cache_size; i++) {
            int log_size;
            memcpy(&log_size, data.data() + offset, sizeof(log_size));
            offset += sizeof(log_size);
            
            std::string log_data = data.substr(offset, log_size);
            offset += log_size;
            
            IndicatorLog log;
            log.ParseFromString(log_data);
            log_cache_queue_.push(log);
        }
        
        // 反序列化log_queue_
        int queue_size;
        memcpy(&queue_size, data.data() + offset, sizeof(queue_size));
        offset += sizeof(queue_size);
        
        log_queue_ = std::queue<IndicatorLog>();
        for (int i = 0; i < queue_size; i++) {
            int log_size;
            memcpy(&log_size, data.data() + offset, sizeof(log_size));
            offset += sizeof(log_size);
            
            std::string log_data = data.substr(offset, log_size);
            offset += log_size;
            
            IndicatorLog log;
            log.ParseFromString(log_data);
            log_queue_.push(log);
        }
    }

} // namespace ypsilon

} // namespace cyber_y