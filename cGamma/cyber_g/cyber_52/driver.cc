//头文件引用
#include "cyber_g/gamma/autobot.pb.h"
#include "cyber_g/cyber_52/driver.h"
#include "cyber/class_loader/class_loader.h"
#include "cyber/component/component.h"
#include "cyber/time/rate.h"
#include "cyber/time/time.h"

using apollo::cyber::Rate;
using apollo::cyber::Time;

bool TimerDriverSample::Init() {
    driver_writer_ = node_->CreateWriter<Dritter>("/apollo/driver");
    return true;
}

bool TimerDriverSample::Proc() {
    auto out_msg = std::make_shared<Dritter>();
    static uint64_t seq = 0;
    // 创建计时器
    Rate rate(0.4);
    while (apollo::cyber::OK() && seq <= 25) {
        out_msg->set_write_time(Time::Now().ToNanosecond());
        out_msg->set_msg_id(seq++);
        out_msg->set_content(std::string("Decepticons ") + std::to_string(seq - 1));
        driver_writer_->Write(out_msg);
        //AINFO << "/apollo/driver sent message, seq=" << (seq - 1);
        AINFO << out_msg->ShortDebugString();
        // 休眠2.5秒，也就是每2.5秒发一次信息。
        rate.Sleep();
    }
    return true;
}