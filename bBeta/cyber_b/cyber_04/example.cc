#include "cyber_b/cyber_04/example.h"
// 在加载component时调用
bool CommonComponentSample::Init() {
    AINFO << "Cybertron init";
    return true;
}
// 在主channel，也就是Driver有消息到达时调用
bool CommonComponentSample::Proc(const std::shared_ptr<Driver>& msg0, const std::shared_ptr<Chatter>& msg1) {
    // 将两个消息的序号格式化输出
    AINFO << "Start common component Proc [" << msg0->msg_id() << "] ["<< msg1->msg_id() << "]";
    return true;
}