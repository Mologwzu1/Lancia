#include <unistd.h>
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
    }
    std::queue<JuniorLog> IndicatorMonitor::ReturnLogs(){
        for(; !log_cache_queue_.empty(); log_cache_queue_.pop()){
            log_queue_.push(log_cache_queue_.front());
        }
        return log_queue_;
    }

} // namespace ypsilon

} // namespace cyber_y