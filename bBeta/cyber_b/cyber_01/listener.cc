//头文件引用
#include "cyber_b/proto/autobot.pb.h"
#include "cyber/cyber.h"
#include "cyber/time/time.h"
//car数据定义的引用，可以看出其定义来源于一个proto
using apollo::cyber_b::proto::Car;

//接收到消息后的响应函数
void message_callback(const std::shared_ptr<Car>& msg) {
    AINFO << "At " << apollo::cyber::Time(msg->now()) << "\tspeed is: " << msg->speed() << " kkm/h";
}

int main(int argc, char* argv[]) {
    //初始化cyber框架
    apollo::cyber::Init(argv[0]);

    //创建监听节点
    auto listener_node = apollo::cyber::CreateNode("listener");

    //创建监听响应进行消息读取
    auto listener = listener_node->CreateReader<Car>("talker_listener", message_callback);
    apollo::cyber::WaitForShutdown();
    return 0;
}
