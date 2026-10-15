#include "cyber_y/cyber_21/writer_agent.h"
#include "cyber_y/ypsilon/log.pb.h"
#include "cyber/time/time.h"
using apollo::cyber::Time;
using cyber_y::proto::Log;
using cyber_y::ypsilon::WriterAgent;
using cyber_y::proto::Role;
int main()
{
    Log log0, log1;
    log0.set_node_name("Sideswipe");
    log0.set_node_id(0);
    log0.set_channel_name("Autobot");
    log0.set_channel_id(1);
    log0.set_role(Role::WRITER);
    log0.set_exec_time(Time::Now().ToNanosecond());
    WriterAgent::Instance().GetLogWriter(0).WriteLog(log0);
    log0.set_node_name("Soundwave");
    log0.set_node_id(1);
    log0.set_channel_name("Decepticon");
    log0.set_channel_id(0);
    log0.set_role(Role::WRITER);
    log0.set_exec_time(Time::Now().ToNanosecond());
    WriterAgent::Instance().GetLogWriter(1).WriteLog(log0);
    log1.set_node_name("Shockwave");
    log1.set_node_id(2);
    log1.set_channel_name("Decepticon");
    log1.set_channel_id(0);
    log1.set_role(Role::READER);
    log1.set_exec_time(Time::Now().ToNanosecond());
    WriterAgent::Instance().GetLogWriter(2).WriteLog(log1);
    log1.set_node_name("Sunstreaker");
    log1.set_node_id(3);
    log1.set_channel_name("Autobot");
    log1.set_channel_id(1);
    log1.set_role(Role::READER);
    log1.set_exec_time(Time::Now().ToNanosecond());
    WriterAgent::Instance().GetLogWriter(3).WriteLog(log1);
    //WriterAgent::Instance().SaveLogs();
    //WriterAgent::Instance().CleanUp();    
    return 0;
}