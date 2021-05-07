#include "greet/hello-greet.hpp"
#include "greet/time/hello-time.hpp"
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    std::string who = "world";
    if (argc > 1) {
        who = argv[1];
    }
    std::cout << get_greet(who) << std::endl;
    print_localtime();
    return 0;
}
