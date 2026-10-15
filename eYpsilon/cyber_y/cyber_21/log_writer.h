#ifndef LOG_WRITER_H
#define LOG_WRITER_H

#include <stack>
#include "cyber_y/ypsilon/log.pb.h"

namespace cyber_y {
namespace ypsilon {
using cyber_y::proto::Log;

    class LogWriter
    {
    public:
        LogWriter() = default;
        LogWriter(const LogWriter&) = delete;
        LogWriter& operator=(const LogWriter&) = default;
        ~LogWriter() = default;
        
        void WriteLog(const Log& log);
        const std::stack<Log> Logs();

    private:
        std::stack<Log> log_stack_;
    };
} // namespace ypsilon

} // namespace cyber_y

#endif // LOG_WRITER_H
