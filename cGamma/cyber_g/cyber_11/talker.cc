//头文件引用
#include "cyber_g/gamma/autobot.pb.h"
#include "cyber/cyber.h"
#include "cyber/time/time.h"
//car数据定义的引用，可以看出其定义来源于一个proto
using apollo::cyber_g::proto::Car;

int main(int argc, char *argv[]) {
    // 初始化一个cyber框架
    apollo::cyber::Init(argv[0]);

    // 创建talker节点
    auto talker_node = apollo::cyber::CreateNode("talker");

    // 从节点创建一个Topic,来实现对车速的查看
    auto talker = talker_node->CreateWriter<Car>("talker_listener");
    AINFO << "Autobots, transform and roll out!";
    
    //设置初始速度与时间为0，然后速度每秒增加6kkm/h
    uint64_t t = 0;
    uint64_t speed = 0;
    while (apollo::cyber::OK() && speed < 300) {
        auto msg = std::make_shared<Car>();
        msg->set_now(apollo::cyber::Time::Now().ToNanosecond());
        msg->set_speed(speed);
        
        msg->set_brand("Porsche");
        msg->set_name("Mirage");
        msg->set_description("funny");
        msg->set_kilometers(speed * t * 500);
    
        t++;
        speed += 6;
        talker->Write(msg);
        sleep(1);
    }
    if (speed == 300) {
        AINFO << "That day, Autobots turned to lights.";
    }
    else {
        AINFO << "Autobots failed to be lights.";
    }
    return 0;
}
