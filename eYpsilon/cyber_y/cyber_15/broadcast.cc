#include <unistd.h>
#include "cyber_y/cyber_33/manager_agent.h"
#include "cyber_y/ypsilon/indicator_log.pb.h"

int main() {
    cyber_y::proto::IndicatorLog log;
    log.set_node_name("Soundwave");
    log.set_node_id(0);
    log.set_channel_name("Decepticon");
    log.set_channel_id(0);
    cyber_y::ypsilon::ManagerAgent::Instance()->WriterRegist(log.channel_id(), log.node_id());
    for (uint64_t speed = 0;speed < 300;speed += 15) {
        cyber_y::ypsilon::ManagerAgent::Instance()->WriteArrange(log, 1000);
        sleep(1);
    }
    cyber_y::ypsilon::ManagerAgent::Instance()->WriterCancel(log.channel_id(), log.node_id());
    return 0;
}
