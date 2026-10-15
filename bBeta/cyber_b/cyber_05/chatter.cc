//头文件引用
#include "cyber_b/proto/autobot.pb.h"
#include "cyber_b/cyber_05/chatter.h"
#include "cyber/class_loader/class_loader.h"
#include "cyber/component/component.h"

bool TimerChatterSample::Init() {
    chatter_writer_ = node_->CreateWriter<Chatter>("/apollo/chatter");
    return true;
}

bool TimerChatterSample::Proc() {
    static int i = 0;
    auto out_msg = std::make_shared<Chatter>();
    out_msg->set_msg_id(i++);
    chatter_writer_->Write(out_msg);
    AINFO << "timer_chatter: Write chattermsg->"<< out_msg->ShortDebugString();
    return true;
}
