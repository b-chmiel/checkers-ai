#include "hello-greet.hpp"
#include "time/hello-time.hpp"
#include <string>

std::string get_greet(const std::string& who)
{
    print_localtime();
    return "Hello " + who;
}
