#include "lib2/hello.hpp"
#include <catch2/catch_test_macros.hpp>
#include <sstream>

SCENARIO("We want to be able to greet someone in a stream", "[hello][greet]")
{
    GIVEN("A ostream")
    {
        std::ostringstream oss;
        WHEN("calling greet methode")
        {
            my_cpp_project::greet(oss);
            THEN("We have our stream with a greeting")
            {
                REQUIRE(oss.str() == "hello world");
            }
        }
    }
}
