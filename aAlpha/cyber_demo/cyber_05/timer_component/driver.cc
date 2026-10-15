//头文件引用
#include "cyber_demo/cyber_05/proto/examples.pb.h"
#include "cyber_demo/cyber_05/timer_component/driver.h"
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