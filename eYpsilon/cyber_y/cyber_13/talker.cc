#include <unistd.h>
#include "cyber/time/time.h"
#include "cyber_y/cyber_22/writer_agent.h"
#include "cyber_y/ypsilon/log.pb.h"

int main() {
    uint64_t speed = 0;
    while (speed < 300) {
        speed += 15;
        cyber_y::proto::Log log1;
        log1.set_node_name("Sideswipe");
        log1.set_node_id(2);
        log1.set_channel_name("Autobot");
        log1.set_channel_id(1);
        log1.set_role(cyber_y::proto::Role::WRITER);
        log1.set_exec_time(apollo::cyber::Time::Now().ToNanosecond());
        cyber_y::ypsilon::WriterAgent::Instance().GetLogWriter(2).WriteLog(log1);
        sleep(1);
    }
    return 0;
}
