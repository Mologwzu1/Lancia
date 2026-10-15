#include <unistd.h>
#include "cyber_y/cyber_33/manager_agent.h"
#include "cyber_y/ypsilon/indicator_log.pb.h"  

int main() {
    cyber_y::proto::IndicatorLog log;
    log.set_node_name("Sunstreaker");
    log.set_node_id(3);
    log.set_channel_name("Autobot");
    log.set_channel_id(1);
    cyber_y::ypsilon::ManagerAgent::Instance()->ReaderRegist(log.channel_id(), log.node_id());
    for (uint64_t speed = 0;speed < 300;speed += 30) {
        cyber_y::ypsilon::ManagerAgent::Instance()->ReadArrange(log.channel_id());
        sleep(1);
    }
    cyber_y::ypsilon::ManagerAgent::Instance()->ReaderCancel(log.channel_id(), log.node_id());
    return 0;
}
