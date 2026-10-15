#include "cyber_demo/cyber_05/proto/examples.pb.h"
#include "cyber/cyber.h"
#include "cyber/time/rate.h"
#include "cyber/time/time.h"

using apollo::cyber::Rate;
using apollo::cyber::Time;
using apollo::cyber::test::proto::Chatter;

int main(int argc, char *argv[]) {
    // 初始化一个cyber框架
    apollo::cyber::Init(argv[0]);
    // 创建node
    auto talker_node = apollo::cyber::CreateNode("chatter_writer");
    // 创建writer，写Chatter类型消息
    auto talker = talker_node->CreateWriter<Chatter>("/apollo/chatter");
    // 创建计时器
    Rate rate(3.0);
    std::string content("Autobots ");
    while (apollo::cyber::OK()) {
        static uint64_t seq = 0;
        auto msg = std::make_shared<Chatter>();
        msg->set_timestamp(Time::Now().ToNanosecond());
        msg->set_lidar_timestamp(Time::Now().ToNanosecond());
        msg->set_msg_id(seq++);
        msg->set_content(content + std::to_string(seq - 1));
        talker->Write(msg);
        AINFO << "/apollo/chatter sent message, seq=" << (seq - 1) << ";";
        // 休眠3秒，也就是每3秒发一次信息。
        rate.Sleep();
    }
    return 0;
}