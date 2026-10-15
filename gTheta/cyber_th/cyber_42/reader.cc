#include "cyber_th/cyber_42/reader.h"
#include "cyber/time/time.h"
// 在加载component时调用
bool DritterComponent::Init() {
    return true;
}
// 在主channel，也就是Driver有消息到达时调用
bool DritterComponent::Proc(const std::shared_ptr<Dritter>& msg) {
    AINFO << "msg content: " << msg->content();
    AINFO << "\n\n";
    return true;
}