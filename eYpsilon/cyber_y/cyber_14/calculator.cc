#include "cyber_y/cyber_32/monitor_agent.h"
int main()
{
    cyber_y::ypsilon::MonitorAgent::Instance()->SaveLogs();
    cyber_y::ypsilon::MonitorAgent::Instance()->Init();
    return 0;
}