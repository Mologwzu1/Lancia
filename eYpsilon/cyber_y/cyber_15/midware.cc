#include "cyber_y/cyber_33/manager_agent.h"
#include "cyber_y/ypsilon/indicator_log.pb.h"
using cyber_y::proto::IndicatorLog;
using cyber_y::ypsilon::ManagerAgent;
int main()
{
    IndicatorLog log0, log1;    
    log0.set_node_name("Sideswipe");
    log0.set_node_id(0);
    log0.set_channel_name("Autobot");
    log0.set_channel_id(1);
    ManagerAgent::Instance()->WriterRegist(log0.channel_id(), log0.node_id());
    ManagerAgent::Instance()->WriteArrange(log0, 0);
    
    log1.set_node_name("Sunstreaker");
    log1.set_node_id(3);
    log1.set_channel_name("Autobot");
    log1.set_channel_id(1);
    ManagerAgent::Instance()->ReaderRegist(log1.channel_id(), log1.node_id());

    ManagerAgent::Instance()->WriteArrange(log0, 0);
    ManagerAgent::Instance()->ReadArrange(log1.channel_id());
    
    ManagerAgent::Instance()->ReaderCancel(log1.channel_id(), log1.node_id());
    ManagerAgent::Instance()->WriterCancel(log0.channel_id(), log0.node_id());

    log0.set_node_name("Soundwave");
    log0.set_node_id(1);
    log0.set_channel_name("Decepticon");
    log0.set_channel_id(0);
    ManagerAgent::Instance()->WriterRegist(log0.channel_id(), log0.node_id());
    log1.set_node_name("Shockwave");
    log1.set_node_id(2);
    log1.set_channel_name("Decepticon");
    log1.set_channel_id(0);
    ManagerAgent::Instance()->ReaderRegist(log1.channel_id(), log1.node_id());

    ManagerAgent::Instance()->WriteArrange(log0, 0);
    ManagerAgent::Instance()->WriteArrange(log0, 0);
    ManagerAgent::Instance()->ReadArrange(log1.channel_id());
    ManagerAgent::Instance()->ReadArrange(log1.channel_id());

    ManagerAgent::Instance()->ReaderCancel(log1.channel_id(), log1.node_id());
    ManagerAgent::Instance()->WriterCancel(log0.channel_id(), log0.node_id());
    
    ManagerAgent::Instance()->SaveIndicatorLogs();
    ManagerAgent::Instance()->Init();
    return 0;
}