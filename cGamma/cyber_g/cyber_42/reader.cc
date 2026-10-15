#include "cyber_g/cyber_42/reader.h"
#include "cyber/time/time.h"
// 在加载component时调用
bool DritterComponent::Init() {
    last_time_ = 0;
    AINFO << "Cybertron init";
    return true;
}
// 在主channel，也就是Driver有消息到达时调用
bool DritterComponent::Proc(const std::shared_ptr<Dritter>& msg) {
    
    msg->set_read_time(apollo::cyber::Time::Now().ToNanosecond());
    if(last_time_ != 0) {
        // 计算当前消息与上一个消息的时间差，并格式化输出
        gamma.SetJitterNS(msg->write_time() - last_time_-1000000000);
        AINFO << "msg jitter: " << gamma.JitterNS() << " ns";
    }
    last_time_ = msg->write_time();
    gamma.SetDelayNS(msg->read_time() - last_time_);
    
    AINFO << "msg content: " << msg->content();
    AINFO << "msg delay: " << gamma.DelayNS() << " ns";
    AINFO << "\n\n";
    return true;
}