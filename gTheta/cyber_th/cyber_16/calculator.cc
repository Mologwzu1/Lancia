#include "cyber_y/cyber_33/manager_agent.h"
int main()
{
    cyber_y::ypsilon::ManagerAgent::Instance()->SaveLogs();
    cyber_y::ypsilon::ManagerAgent::Instance()->SaveIndicatorLogs();
    cyber_y::ypsilon::ManagerAgent::Instance()->Init();
    return 0;
}