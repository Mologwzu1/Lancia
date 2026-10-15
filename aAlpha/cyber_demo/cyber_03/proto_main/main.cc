#include "cyber_demo/cyber_03/proto/autobot.pb.h"
#include <array>
using namespace std;

string analysis(const apollo::cyber::test::proto::CarMsg& car)
{
    string result = car.name() + "\t" + car.brand() + "\t" + to_string(car.age()) + "\t";
    for (int i = 0; i < car.description_size(); i++){
        result +=  car.description(i) + " ";
    }
    return result;
}

int main()
{
    //apollo::cyber::test::proto::CarMsg[] car = new apollo::cyber::test::proto::CarMsg[2];
    array<apollo::cyber::test::proto::CarMsg, 2> car;
    car[0].set_name("Orion Pax");
    car[0].set_brand("Peterbilt");
    car[0].set_age(8000);
    car[0].add_description("innovative");
    car[0].add_description("mercyful");
    car[0].add_description("leader");
    car[1].set_name("D      16");
    car[1].set_brand("M1    A2");
    car[1].set_age(8000);
    car[1].add_description("routineer");
    car[1].add_description("ruler");

    cout << "name\t\tbrand\t\tage\tdescription" << endl;
    for (int i = 0; i < 2; i++){
        cout << analysis(car[i]) << endl;
    }
    return 0;
}