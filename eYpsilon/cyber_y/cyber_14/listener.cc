#include <unistd.h>
#include "cyber/time/time.h"
#include "cyber_y/cyber_32/monitor_agent.h"
#include "cyber_y/ypsilon/junior_log.pb.h"  

int main() {
    uint64_t speed = 0;
    while (speed < 300) {
        speed += 60;
        cyber_y::proto::JuniorLog log1;
        log1.set_node_name("Sunstreaker");
        log1.set_node_id(3);
        log1.set_channel_name("Autobot");
        log1.set_channel_id(1);
        log1.set_read_time(apollo::cyber::Time::Now().ToNanosecond());
        cyber_y::ypsilon::MonitorAgent::Instance()->ReadRqst(log1);
        sleep(1);
    }
    return 0;
}
