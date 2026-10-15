//头文件引用
#include "cyber_th/theta/autobot.pb.h"
#include "cyber/cyber.h"
#include "cyber/time/time.h"
using apollo::cyber::Time;
using apollo::cyber_th::proto::Car;
//接收到消息后的响应函数
void message_callback(const std::shared_ptr<Car>& msg) {
    AINFO << "speed: " << msg->speed() << " kkm/h";
    AINFO << "kilometers: " << msg->kilometers() << " km";
    AINFO << "brand: " << msg->brand();
    AINFO << "name: " << msg->name();
    AINFO << "autobot is " << msg->description() << "\n\n\n";
}

int main(int argc, char* argv[]) {
    //初始化cyber框架
    apollo::cyber::Init(argv[0]);

    //创建监听节点
    auto listener_node = apollo::cyber::CreateNode("audience");

    //创建监听响应进行消息读取
    auto listener = listener_node->CreateReader<Car>("broadcast_audience", message_callback);
    apollo::cyber::WaitForShutdown();
    return 0;
}
