#include<cyber/cyber.h>

int main(int argc, char const *argv[])
{
    apollo::cyber::Init(argv[0]);
    AINFO << "Autobots, transform and roll out!";
    AWARN << "Autobots, transform and roll out!";
    AERROR << "Autobots, transform and roll out!";
    AFATAL << "Autobots, transform and roll out!";
    return 0;
}
