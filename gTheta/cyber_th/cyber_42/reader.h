//头文件引用
#include "cyber_th/theta/autobot.pb.h"
#include <memory>
#include "cyber/component/component.h"

using apollo::cyber::Component;
using apollo::cyber_th::proto::Dritter;

// 有两个消息源，继承以Driver和Chatter为参数的Component模版类
class DritterComponent : public Component<Dritter> {
    public:
        bool Init() override;
        // Proc() 函数的两个参数表示两个channel中的最新的信息
        bool Proc(const std::shared_ptr<Dritter>& msg) override;
};
// 将DritterComponent注册在cyber中
CYBER_REGISTER_COMPONENT(DritterComponent)