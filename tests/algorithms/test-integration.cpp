#include <random>
#include <vector>
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <iostream>

#include "algorithms/integration.hpp"
#include "algorithms/generation.hpp"


TEST_CASE("We want to be able to compute the integral of an input range of real data","[algorithms][integration]")
{
    SECTION("Default between 0 and 1")
    {
///! [integration_real_data_default_01]
    std::mt19937 gen(0); //Standard mersenne_twister_engine seeded with 0
    std::vector<double> x(3000);
    constexpr double a = 0.0;
    constexpr double b = 10.0;
    spp::range(x.begin(), x.end(), a, b);
    std::vector<double> x2(x.size());
    std::transform(x.begin(), x.end(), x2.begin(),[](auto x){return x*x;});
    const auto I = spp::integrate(x2.begin(), x2.end()) * (b - a);
    CHECK(I == Catch::Approx(1000.0/3).epsilon(0.1));
///! [integration_real_data_default_01]
  }
    SECTION("Default between a and b")
    {
///! [integration_real_data_default_ab]
    std::mt19937 gen(0); //Standard mersenne_twister_engine seeded with 0
    std::vector<double> x(3000);
    constexpr double a = 0.0;
    constexpr double b = 10.0;
    spp::range(x.begin(), x.end(), a, b);
    std::vector<double> x2(x.size());
    std::transform(x.begin(), x.end(), x2.begin(),[](auto x){return x*x;});
    const auto I = spp::integrate(x2.begin(), x2.end(), a, b);
    CHECK(I == Catch::Approx(1000.0/3).epsilon(0.1));
///! [integration_real_data_default_ab]
  }
}
