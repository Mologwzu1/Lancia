#ifndef WRITER_AGENT_H
#define WRITER_AGENT_H

#include <map>
#include <string>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "cyber_y/cyber_21/log_writer.h"
#include "cyber_y/ypsilon/log.pb.h"

namespace cyber_y {
namespace ypsilon {

using cyber_y::ypsilon::LogWriter;

class WriterAgent {
public:
    WriterAgent()=default;
    ~WriterAgent();
    WriterAgent(const WriterAgent&) = delete;
    WriterAgent& operator=(const WriterAgent&) = delete;
    
    static WriterAgent& Instance();
    
    LogWriter& GetLogWriter(const uint64_t node_id);
    void SaveLogs();
    
private:
    std::map<uint64_t, LogWriter> writer_map_;
    
};

} // namespace ypsilon
} // namespace cyber_y

#endif // WRITER_AGENT_H
