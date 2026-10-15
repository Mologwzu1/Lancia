#include <unistd.h>
#include "cyber/time/time.h"
#include "cyber_y/cyber_32/monitor_agent.h"
#include "cyber_y/ypsilon/junior_log.pb.h"

int main() {
    uint64_t speed = 0;
    while (speed < 300) {
        cyber_y::proto::JuniorLog log0;
        log0.set_node_name("Soundwave");
        log0.set_node_id(0);
        log0.set_channel_name("Decepticon");
        log0.set_channel_id(0);
        log0.set_write_time(apollo::cyber::Time::Now().ToNanosecond());
        cyber_y::ypsilon::MonitorAgent::Instance()->WriteRqst(log0);
        speed += 30;
        sleep(1);
    }
    return 0;
}
