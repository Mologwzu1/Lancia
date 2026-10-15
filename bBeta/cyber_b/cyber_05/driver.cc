//头文件引用
#include "cyber_b/proto/autobot.pb.h"
#include "cyber_b/cyber_05/driver.h"
#include "cyber/class_loader/class_loader.h"
#include "cyber/component/component.h"

bool TimerDriverSample::Init() {
    driver_writer_ = node_->CreateWriter<Driver>("/apollo/driver");
    return true;
}

bool TimerDriverSample::Proc() {
    static int i = 0;
    auto out_msg = std::make_shared<Driver>();
    out_msg->set_msg_id(i++);
    driver_writer_->Write(out_msg);
    AINFO << "timer_driver: Write drivermsg->"<< out_msg->ShortDebugString();
    return true;
}