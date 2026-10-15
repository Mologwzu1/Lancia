#include <unistd.h>
#include "cyber_y/cyber_33/manager_agent.h"
#include "cyber_y/ypsilon/indicator_log.pb.h"

int main() {
    cyber_y::proto::IndicatorLog log;
    log.set_node_name("Shockwave");
    log.set_node_id(1);
    log.set_channel_name("Decepticon");
    log.set_channel_id(0);
    cyber_y::ypsilon::ManagerAgent::Instance()->ReaderRegist(log.channel_id(), log.node_id());
    for (uint64_t speed = 0;speed < 300;speed += 60) {
        cyber_y::ypsilon::ManagerAgent::Instance()->ReadArrange(log.channel_id());
        sleep(4);
    }
    cyber_y::ypsilon::ManagerAgent::Instance()->ReaderCancel(log.channel_id(), log.node_id());
    return 0;
}
