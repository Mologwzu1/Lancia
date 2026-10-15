#ifndef INDICATOR_MONITOR_H
#define INDICATOR_MONITOR_H


#include <queue>
#include "cyber_y/ypsilon/junior_log.pb.h"  


namespace cyber_y {
namespace ypsilon {
    
using cyber_y::proto::JuniorLog;
    class IndicatorMonitor
    {
    public:
        IndicatorMonitor()=default;
        ~IndicatorMonitor()=default;

        bool JudgeLog(const JuniorLog& log0, const JuniorLog& log1);
        void WriteLog(const JuniorLog& log);
        void ReadLog(const JuniorLog& log);
        std::queue<JuniorLog> ReturnLogs();

    private:
        std::queue<JuniorLog> log_cache_queue_;
        std::queue<JuniorLog> log_queue_;  
    };
} // namespace ypsilon

} // namespace cyber_y

#endif // INDICATOR_MONITOR_H