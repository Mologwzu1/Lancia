#include "writer_agent.h"
#include "cyber/time/time.h"
#include <fstream>
#include <stack>
#include <sys/stat.h>

namespace cyber_y {
namespace ypsilon {
using cyber_y::proto::Role;
using apollo::cyber::Time;


WriterAgent::~WriterAgent() {
    SaveLogs();
}

WriterAgent& WriterAgent::Instance() {
    static WriterAgent instance;
    return instance;
}

LogWriter& WriterAgent::GetLogWriter(const uint64_t node_id) {
    if (writer_map_.find(node_id) == writer_map_.end()) {
        writer_map_[node_id] = LogWriter();
    }
    return writer_map_[node_id];
}

void WriterAgent::SaveLogs() {
    std::ofstream of("output/logs/cybery_" + Time::Now().ToString() + ".log", std::ios::trunc);
    
    for (auto& writer_pair : writer_map_) {//td::cerr << "CreateSharedMemory" << std::endl;
        std::stack<IndicatorLog> log_stack = writer_pair.second.Logs();
        
        // 直接遍历日志栈
        std::stack<IndicatorLog> temp_stack = log_stack;
        while (!temp_stack.empty()) {
            const IndicatorLog& log = temp_stack.top();
            of << log.node_name() << "\t";
            of << log.node_id() << "\t";
            of << log.channel_name() << "\t";
            of << log.channel_id() << "\t";
            if (log.role() == Role::WRITER) {
                of << "WRITER" << "\t";
            }
            else if (log.role() == Role::READER) {
                of << "READER" << "\t";
            }
            else {
                of << "UNKNOWN" << "\t";
            }
            of << log.exec_time() << "\n";
            temp_stack.pop();
        }
    }
    
    of.close();
}

} // namespace ypsilon
} // namespace cyber_y