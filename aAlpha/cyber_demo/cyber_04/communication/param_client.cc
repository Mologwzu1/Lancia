#include "cyber/cyber.h"
#include "cyber/parameter/parameter_client.h"


using apollo::cyber::Parameter;
using apollo::cyber::ParameterClient;

int main(int argc, char** argv) {
    //初始化cyber框架
    apollo::cyber::Init(*argv);

    //创建一个node，该node的名字和Topic名字同名
    std::shared_ptr<apollo::cyber::Node> client_node = apollo::cyber::CreateNode("parameters_client");
    AINFO<<"Hi, I'm car's parameters client!";

    //从该node创建参数客户端
    auto param_client = std::make_shared<ParameterClient>(client_node,"parameters_server");
        
    //获取所有参数,用vector获取所有参数
    std::vector<Parameter> car_parameters;
    param_client->ListParameters(&car_parameters);
    //遍历获取的参数，显示参数的名字以及参数的类型
    for(auto &&parameter : car_parameters){
        AINFO << parameter.Name() << " is " << parameter.TypeName();
    }

    //客户端选择一个参数进行修改,比如修改max_speed
    param_client->SetParameter(Parameter("max_speed",180));
    //获取修改后的max_speed
    Parameter car_parameter;
    param_client->GetParameter("max_speed", &car_parameter);
    AINFO << "now max_speed " << car_parameter.AsInt64();
    
    apollo::cyber::WaitForShutdown();
    return 0;
}