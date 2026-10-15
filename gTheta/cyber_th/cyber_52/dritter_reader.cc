//头文件引用
#include "dritter_reader.h"
#include "cyber/cyber.h"
#include "cyber/time/time.h"
using apollo::cyber::Time;

bool DritterReader::Init() {
    return true;
}

void DritterReader::message_callback(const std::shared_ptr<Dritter>& msg) {
    msg->set_read_time(apollo::cyber::Time::Now().ToNanosecond());
    if(last_time_ != 0) {
        // 计算当前消息与上一个消息的时间差，并格式化输出
        theta_.SetJitterNS(msg->write_time() - last_time_-1000000000);
        AINFO << "msg jitter: " << theta_.JitterNS() << " ns";
    }
    last_time_ = msg->write_time();
    theta_.SetDelayNS(msg->read_time() - last_time_);
    AINFO << "msg delay: " << theta_.DelayNS() << " ns";
    AINFO << "\n\n";
}

bool DritterReader::Proc() {
    dritter_reader_ = node_->CreateReader<Dritter>("/apollo/dritter",
        [this](const std::shared_ptr<Dritter>& msg) {
            this->message_callback(msg);
        });
    return true;
}