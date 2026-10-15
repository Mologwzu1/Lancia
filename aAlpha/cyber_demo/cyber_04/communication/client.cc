//头文件引用
#include "cyber_demo/cyber_04/proto/autobot.pb.h"
#include "cyber/cyber.h"

//car数据定义的引用，可以看出其定义来源于一个proto
using apollo::cyber::test::proto::Car;

int main(int argc, char* argv[]) {
    //初始化cyber框架
    apollo::cyber::Init(argv[0]);
    
    //创建client node
    std::shared_ptr<apollo::cyber::Node> node(apollo::cyber::CreateNode("client"));
    auto client = node->CreateClient<Car, Car>("service_client");

    AINFO << "Hi server, I want to know information about the autobot.";

    //创建一个请求
    auto request = std::make_shared<Car>();
    
    //发送请求并获得回应数据
    auto response = client->SendRequest(request);
    while(apollo::cyber::OK){
        if (response == nullptr) {
            AINFO << "out of service!";
            continue;
        }
        AINFO << "brand is : " << response->brand();
        AINFO << "name is : " << response->name();
        AINFO << "autobot is : " << response->description();
        AINFO << "kilometers is : " << response->kilometers();
    }
    
    apollo::cyber::WaitForShutdown();
    return 0;
}