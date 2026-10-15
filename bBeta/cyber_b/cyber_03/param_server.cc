#include "cyber/cyber.h"
#include "cyber/parameter/parameter_client.h"
#include "cyber/parameter/parameter_server.h"

using apollo::cyber::Parameter;
using apollo::cyber::ParameterServer;

int main(int argc, char** argv) {
    //初始化cyber框架
    apollo::cyber::Init(*argv);

    //创建一个node，该node的名字和Topic名字同名
    std::shared_ptr<apollo::cyber::Node> server_node = apollo::cyber::CreateNode("parameters_server");
    AINFO << "Hi，I'am your car's parameter server.";
    
    //从该node创建参数服务器
    auto param_server = std::make_shared<ParameterServer>(server_node);
    
    //服务端进行参数设置，对小车的最高速度、最大人数、是否自动驾驶等参数进行了设置
    param_server->SetParameter(Parameter("max_speed", 120));
    param_server->SetParameter(Parameter("max_people", 5));
    param_server->SetParameter(Parameter("if_auto", true));






    //查看服务端目前的值
    Parameter car_parameter;
    param_server->GetParameter("max_speed", &car_parameter);
    AINFO << "origin max_speed " << car_parameter.AsInt64();
    
    apollo::cyber::WaitForShutdown();
    return 0;
}
