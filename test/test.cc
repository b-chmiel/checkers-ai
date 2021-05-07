#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "greet/hello-greet.hpp"

TEST_CASE("Test1", "[test1]")
{
    REQUIRE(get_greet("ttt") == "Hello ttt");
}