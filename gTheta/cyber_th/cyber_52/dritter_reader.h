//头文件引用
#include "cyber_th/theta/autobot.pb.h"
#include "cyber/class_loader/class_loader.h"
#include "cyber/component/timer_component.h"
#include "cyber_th/theta/indicator.h"

using cyber_th::theta::Indicator;
using apollo::cyber::TimerComponent;
using apollo::cyber::Reader;
using apollo::cyber_th::proto::Dritter;

class DritterReader : public TimerComponent {
    public:
        bool Init() override;
        void message_callback(const std::shared_ptr<Dritter>& msg);
        bool Proc() override;

    private:
        std::shared_ptr<Reader<Dritter>> dritter_reader_ = nullptr;
        Indicator theta_;
        int64_t last_time_ = 0;
};
CYBER_REGISTER_COMPONENT(DritterReader) 
