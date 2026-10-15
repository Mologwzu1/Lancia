//头文件引用
#include "cyber_demo/cyber_05/proto/examples.pb.h"
#include <memory>
#include "cyber/component/component.h"

using apollo::cyber::Component;
using apollo::cyber::ComponentBase;
using apollo::cyber::test::proto::Driver;
using apollo::cyber::test::proto::Chatter;

// 有两个消息源，继承以Driver和Chatter为参数的Component模版类
class CommonComponentSample : public Component<Driver, Chatter> {
    public:
        bool Init() override;
        // Proc() 函数的两个参数表示两个channel中的最新的信息
        bool Proc(const std::shared_ptr<Driver>& msg0, const std::shared_ptr<Chatter>& msg1) override;
};
// 将CommonComopnentSample注册在cyber中
CYBER_REGISTER_COMPONENT(CommonComponentSample)