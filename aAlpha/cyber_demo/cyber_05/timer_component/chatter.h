//头文件引用
#include "cyber_demo/cyber_05/proto/examples.pb.h"
#include <memory>
#include "cyber/class_loader/class_loader.h"
#include "cyber/component/component.h"
#include "cyber/component/timer_component.h"

using apollo::cyber::Component;
using apollo::cyber::ComponentBase;
using apollo::cyber::TimerComponent;
using apollo::cyber::Writer;
using apollo::cyber::test::proto::Chatter;

class TimerChatterSample : public TimerComponent {
  public:
    bool Init() override;
    bool Proc() override;

  private:
    std::shared_ptr<Writer<Chatter>> chatter_writer_ = nullptr;
};
CYBER_REGISTER_COMPONENT(TimerChatterSample)
