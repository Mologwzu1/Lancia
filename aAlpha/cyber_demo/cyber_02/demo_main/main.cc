#include "cyber_demo/cyber_02/demo_lib/getName.h"
#include <iostream>

int main()
{
    for (int i = 0; i< 5; ++i)
    {
        std::cout << get_name(" Decepticons ") << std::endl;
    }
    return 0;
}