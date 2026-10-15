#ifndef INDICATOR_MONITOR_H
#define INDICATOR_MONITOR_H

#include <queue>
#include <string>
#include "cyber_y/ypsilon/junior_log.pb.h"

namespace cyber_y {
namespace ypsilon {
using cyber_y::proto::JuniorLog;

    class IndicatorMonitor
    {
    public:
        IndicatorMonitor() = default;
        ~IndicatorMonitor() = default;

        bool JudgeLog(const JuniorLog& log0, const JuniorLog& log1);
        void WriteLog(const JuniorLog& log);
        void ReadLog(const JuniorLog& log);
        std::queue<JuniorLog> ReturnLogs();
        
        // 序列化和反序列化方法
        std::string Serialize() const;
        void Deserialize(const std::string& data);

    private:
        std::queue<JuniorLog> log_cache_queue_;
        std::queue<JuniorLog> log_queue_;
    };
} // namespace ypsilon

} // namespace cyber_y

#endif // INDICATOR_MONITOR_H