//头文件引用
#include "cyber_g/gamma/autobot.pb.h"
#include "cyber_g/gamma/indicator.h"
#include "cyber/cyber.h"
#include "cyber/time/time.h"
using cyber_g::gamma::Indicator;
using apollo::cyber::Time;
using apollo::cyber_g::proto::Car;
//接收到消息后的响应函数
void message_callback(const std::shared_ptr<Car>& msg) {
    Indicator indicator;
    indicator.SetDelayNS((Time::Now().ToNanosecond() - msg->now()));
    AINFO << "delay: " << indicator.DelayNS() << " ns";
}

int main(int argc, char* argv[]) {
    //初始化cyber框架
    apollo::cyber::Init(argv[0]);

    // 检查参数
    if (argc != 2) {
        AERROR << "Usage: " << argv[0] << " <frequency>";
        return 1;
    }
    std::string frequency = argv[1];

    //创建监听节点
    auto listener_node = apollo::cyber::CreateNode("midware");

    //创建监听响应进行消息读取
    auto listener = listener_node->CreateReader<Car>(frequency, message_callback);
    apollo::cyber::WaitForShutdown();
    return 0;
}
