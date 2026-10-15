//头文件引用
#include "cyber_demo/cyber_04/proto/autobot.pb.h"
#include "cyber/cyber.h"

//car数据定义的引用，可以看出其定义来源于一个proto
using apollo::cyber::test::proto::Car;

//接收到消息后的响应函数
void message_callback(const std::shared_ptr<Car>& request,std::shared_ptr<Car>& response) {
    response->set_brand("Chevrolet");
    response->set_name("B-127");
    response->set_description("chatter");
    response->set_kilometers(5);
}

int main(int argc, char* argv[]) {
    //初始化cyber框架
    apollo::cyber::Init(argv[0]);
    
    //创建client node
    std::shared_ptr<apollo::cyber::Node> node(apollo::cyber::CreateNode("server"));
    
    AINFO << "Ciao, I am server.";
    
    //创建server node并设置topic名称，定义响应函数
    auto server = node->CreateService<Car, Car>("service_client", message_callback);
    
    apollo::cyber::WaitForShutdown();
    return 0;
}