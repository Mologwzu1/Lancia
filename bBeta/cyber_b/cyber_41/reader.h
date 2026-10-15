//头文件引用
#include "cyber_b/proto/autobot.pb.h"
#include <memory>
#include "cyber/component/component.h"
#include "cyber/time/time.h"

using apollo::cyber::Time;
using apollo::cyber::Component;
using apollo::cyber::ComponentBase;
using apollo::cyber_b::proto::Dritter;

// 有两个消息源，继承以Driver和Chatter为参数的Component模版类
class CommonComponentSample : public Component<Dritter/*, Dritter*/> {
    public:
        bool Init() override;
        // Proc() 函数的两个参数表示两个channel中的最新的信息
        bool Proc(const std::shared_ptr<Dritter>& msg0/*, const std::shared_ptr<Dritter>& msg1*/) override;
    private:
        Time msg0_last_time_ = Time(0);
        //Time msg1_last_time_ = Time(0);
};
// 将CommonComopnentSample注册在cyber中
CYBER_REGISTER_COMPONENT(CommonComponentSample)