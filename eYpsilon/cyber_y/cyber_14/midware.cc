#include "cyber_y/cyber_32/monitor_agent.h"
#include "cyber_y/ypsilon/junior_log.pb.h"
#include "cyber/time/time.h"
using apollo::cyber::Time;
using cyber_y::proto::JuniorLog;
using cyber_y::ypsilon::MonitorAgent;
int main()
{
    JuniorLog log0, log1;
    log0.set_node_name("Sideswipe");
    log0.set_node_id(0);
    log0.set_channel_name("Autobot");
    log0.set_channel_id(1);
    log0.set_write_time(Time::Now().ToNanosecond());
    MonitorAgent::Instance()->WriteRqst(log0);
    log0.set_node_name("Soundwave");
    log0.set_node_id(1);
    log0.set_channel_name("Decepticon");
    log0.set_channel_id(0);
    log0.set_write_time(Time::Now().ToNanosecond());
    MonitorAgent::Instance()->WriteRqst(log0);
    log1.set_node_name("Shockwave");
    log1.set_node_id(2);
    log1.set_channel_name("Decepticon");
    log1.set_channel_id(0);
    log1.set_read_time(Time::Now().ToNanosecond());
    MonitorAgent::Instance()->ReadRqst(log1);
    log1.set_node_name("Sunstreaker");
    log1.set_node_id(3);
    log1.set_channel_name("Autobot");
    log1.set_channel_id(1);
    log1.set_read_time(Time::Now().ToNanosecond());
    MonitorAgent::Instance()->ReadRqst(log1);
    MonitorAgent::Instance()->SaveLogs();
    MonitorAgent::Instance()->Init();
    return 0;
}