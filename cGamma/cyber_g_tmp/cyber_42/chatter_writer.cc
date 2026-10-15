#include "cyber_g/gamma/autobot.pb.h"
#include "cyber/cyber.h"
#include "cyber/time/rate.h"
#include "cyber/time/time.h"

using apollo::cyber::Rate;
using apollo::cyber::Time;
using apollo::cyber_g::proto::Dritter;

int main(int argc, char *argv[]) {
    // 初始化一个cyber框架
    apollo::cyber::Init(argv[0]);
    // 创建node
    auto talker_node = apollo::cyber::CreateNode("chatter_writer");
    // 创建writer，写Dritter类型消息
    auto talker = talker_node->CreateWriter<Dritter>("/apollo/dritter");
    // 创建计时器
    Rate rate(1.0);
    auto msg = std::make_shared<Dritter>();
    msg->set_msg_id(0);
    while (apollo::cyber::OK() && msg->msg_id() <= 60) {
        msg->set_write_time(Time::Now().ToNanosecond());
        msg->set_msg_id(msg->msg_id() + 1);
        msg->set_content(std::string("Autobots ") + std::to_string(msg->msg_id()));
        talker->Write(msg);
        AINFO << "chatter_writer sent message, seq=" << (msg->msg_id());
        // 休眠1秒，也就是每1秒发一次信息。
        rate.Sleep();
    }
    return 0;
}