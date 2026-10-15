#ifndef MONITOR_MANAGER_H
#define MONITOR_MANAGER_H

#include <queue>
#include "indicator_monitor.h"
#include "cyber_y/ypsilon/indicator_log.pb.h"

namespace cyber_y {
namespace ypsilon {
using cyber_y::ypsilon::IndicatorMonitor;
using cyber_y::proto::IndicatorLog;
    class MonitorManager
    {
    public:
        MonitorManager()=default;
        ~MonitorManager()=default;

        void WriterRegist(const uint64_t writer_id);
        void ReaderRegist(const uint64_t reader_id);
        void WriterCancel(const uint64_t writer_id);
        void ReaderCancel(const uint64_t reader_id);

        void WriteRqst(IndicatorLog log);
        void ReadRqst();
        
        std::queue<IndicatorLog> ReturnLogs();
        std::string Serialize() const;
        void Deserialize(const std::string& data);

    private:
        std::queue<uint64_t> writer_queue_;
        std::queue<uint64_t> reader_queue_;
        IndicatorMonitor monitor_;

    };
} // namespace ypsilon

} // namespace cyber_y

#endif // MONITOR_MANAGER_H
