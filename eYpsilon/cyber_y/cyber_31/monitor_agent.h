#ifndef MONITOR_AGENT_H
#define MONITOR_AGENT_H

#include <map>
#include <fstream>
#include "indicator_monitor.h"
#include "cyber/common/macros.h"
#include "cyber_y/ypsilon/junior_log.pb.h"

namespace cyber_y {
namespace ypsilon {
using cyber_y::ypsilon::IndicatorMonitor;
using cyber_y::proto::JuniorLog;
    class MonitorAgent
    {
    public:
        ~MonitorAgent();

        void Init();
        bool ServiceFind(const uint64_t channel_id);
        void WriteRqst(const JuniorLog& log);
        void ReadRqst(const JuniorLog& log);
        void SaveLogs();

        //static MonitorAgent& Instance();

    private:
        /**MonitorAgent() = default;
        MonitorAgent(const MonitorAgent&) = delete;
        MonitorAgent& operator=(const MonitorAgent&) = delete;
        MonitorAgent(MonitorAgent&&) = delete;
        MonitorAgent& operator=(MonitorAgent&&) = delete;**/

        std::map<uint64_t, IndicatorMonitor> monitor_map_;
        std::ofstream of_;
        std::string file_root_;
        std::string log_file_;
        DECLARE_SINGLETON(MonitorAgent)

    };
} // namespace ypsilon

} // namespace cyber_y

#endif // MONITOR_AGENT_H