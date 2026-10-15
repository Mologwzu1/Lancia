//头文件引用
#include "cyber_g/gamma/autobot.pb.h"
#include <memory>
#include "cyber_g/gamma/indicator.h"
#include "cyber/component/component.h"

using apollo::cyber::Component;
//using apollo::cyber::ComponentBase;
using cyber_g::gamma::Indicator;
using apollo::cyber_g::proto::Dritter;

// 有两个消息源，继承以Driver和Chatter为参数的Component模版类
class CommonComponentSample : public Component<Dritter> {
    public:
        bool Init() override;
        // Proc() 函数的两个参数表示两个channel中的最新的信息
        bool Proc(const std::shared_ptr<Dritter>& msg) override;
    private:
        Indicator gamma;
        int64_t last_time_ = 0;
};
// 将CommonComopnentSample注册在cyber中
CYBER_REGISTER_COMPONENT(CommonComponentSample)