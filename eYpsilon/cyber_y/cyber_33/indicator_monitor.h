#ifndef INDICATOR_MONITOR_H
#define INDICATOR_MONITOR_H

#include <queue>
#include <string>
#include "cyber_y/ypsilon/indicator_log.pb.h"

namespace cyber_y {
namespace ypsilon {
using cyber_y::proto::IndicatorLog;

    class IndicatorMonitor
    {
    public:
        IndicatorMonitor() = default;
        ~IndicatorMonitor() = default;

        void WriteLostLog(IndicatorLog& log);
        void WriteLog(IndicatorLog& log);
        void ReadLog();
        
        std::queue<IndicatorLog> ReturnLogs();
        std::string Serialize() const;
        void Deserialize(const std::string& data);

    private:
        std::queue<IndicatorLog> log_cache_queue_;
        std::queue<IndicatorLog> log_queue_;
    };
} // namespace ypsilon

} // namespace cyber_y

#endif // INDICATOR_MONITOR_H