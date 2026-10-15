#include <unistd.h>
#include "cyber/time/time.h"
#include "cyber_y/cyber_23/writer_agent.h"
#include "cyber_y/ypsilon/log.pb.h"

int main() {
    uint64_t speed = 0;
    while (speed < 300) {
        cyber_y::proto::Log log0;
        log0.set_node_name("Shockwave");
        log0.set_node_id(1);
        log0.set_channel_name("Decepticon");
        log0.set_channel_id(0);
        log0.set_role(cyber_y::proto::Role::READER);
        log0.set_exec_time(apollo::cyber::Time::Now().ToNanosecond());
        cyber_y::ypsilon::WriterAgent::Instance().GetLogWriter(1).WriteLog(log0);
        speed += 30;
        sleep(1);
    }
    return 0;
}
