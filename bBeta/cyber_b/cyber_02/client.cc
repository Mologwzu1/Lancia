//头文件引用
#include "cyber_b/proto/autobot.pb.h"
#include "cyber/cyber.h"

//car数据定义的引用，可以看出其定义来源于一个proto
using apollo::cyber_b::proto::Car;

int main(int argc, char* argv[]) {
    //初始化cyber框架
    apollo::cyber::Init(argv[0]);
    AINFO << "Hi server, I want to know information about the autobot.";
    
    //创建client node
    std::shared_ptr<apollo::cyber::Node> node(apollo::cyber::CreateNode("client"));
    auto client = node->CreateClient<Car, Car>("service_client");
        
    while(apollo::cyber::OK){
        //创建一个请求
        auto request = std::make_shared<Car>();

        //发送请求并获得回应数据
        auto response = client->SendRequest(request);
        if (response == nullptr) {
            AINFO << "out of service!";
        }
        
        AINFO << "At" << apollo::cyber::Time(response->now()) << "\trequest received.";
        AINFO << "At" << apollo::cyber::Time::Now() << "\tresponse received.";
        AINFO << "brand is : " << response->brand();
        AINFO << "name is : " << response->name();
        AINFO << "autobot is : " << response->description();
        AINFO << "kilometers is : " << response->kilometers();
        sleep(2);
    }
    
    apollo::cyber::WaitForShutdown();
    return 0;
}