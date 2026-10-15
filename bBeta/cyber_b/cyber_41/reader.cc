#include "cyber_b/cyber_41/reader.h"
#include "cyber_b/beta/delay.h"
#include "cyber_b/beta/jitter.h"

using cyber_b::beta::Delay;
using cyber_b::beta::Jitter;
// 在加载component时调用
bool CommonComponentSample::Init() {
    msg0_last_time_ = Time(0);
    //msg1_last_time_ = Time(0);
    AINFO << "Cybertron init";
    return true;
}
// 在主channel，也就是Driver有消息到达时调用
bool CommonComponentSample::Proc(const std::shared_ptr<Dritter>& msg0/*, const std::shared_ptr<Dritter>& msg1*/) {
    msg0->set_read_time(Time::Now().ToNanosecond());
    if(!msg0_last_time_.IsZero()) {
        // 计算当前消息与上一个消息的时间差，并格式化输出
        AINFO << "msg0 jitter: " << Jitter(Time(msg0->write_time()) - msg0_last_time_).JitterNS()-2500000000 << " ns";
    }
    msg0_last_time_ = Time(msg0->write_time());
    AINFO << "msg0 content: " << msg0->content();
    AINFO << "msg0 delay: " << Delay(Time(msg0->read_time()) - msg0_last_time_).DelayNS() << " ns";
    /*
    msg1->set_read_time(Time::Now().ToNanosecond());
    if(!msg1_last_time_.IsZero()) {
        // 计算当前消息与上一个消息的时间差，并格式化输出
        AINFO << "msg1 jitter: " << Jitter(Time(msg1->write_time()) - msg1_last_time_).JitterNS()-2500000000 << " ns";
    }
    msg1_last_time_ = Time(msg1->write_time());
    AINFO << "msg1 content: " << msg1->content();
    AINFO << "msg1 delay: " << Delay(Time(msg1->read_time()) - msg1_last_time_).DelayNS() << " ns";
    */
    AINFO << "\n\n";
    return true;
}