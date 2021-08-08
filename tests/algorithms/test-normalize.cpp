#include <random>
#include <vector>
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include <catch2/catch_approx.hpp>
#include <iostream>
#include <filesystem>

#include "spectral_analysis/spectral_analysis.hpp"
#include "plot/plot.hpp"


TEST_CASE("We want to be able to normalize an input range of real data","[algorithms][normalize]")
{
///! [normalize_real_data]
    std::mt19937 gen(0); //Standard mersenne_twister_engine seeded with 0

    std::uniform_real_distribution<> dis(1.0, 2.0);

    std::vector<double> random_signal(10);

    std::generate(random_signal.begin(), random_signal.end(), std::bind(dis, gen));

    spp::normalise(random_signal.begin(), random_signal.end(), random_signal.begin());

    CHECK(spp::integrate(random_signal.begin(), random_signal.end()) == Catch::Approx(1.0));
///! [normalize_real_data]
}

TEST_CASE("We want to be able to normalize an input range of real data using the rms","[algorithms][normalize_rms]")
{
///! [normalize_real_data_rms]
    std::mt19937 gen(0); //Standard mersenne_twister_engine seeded with 0

    std::uniform_real_distribution<> dis(0.0, 10.0);

    std::vector<double> random_signal(10);

    std::generate(random_signal.begin(), random_signal.end(), std::bind(dis, gen));

    std::vector<double> normalized_signal(10);

    spp::normalise(random_signal.begin(), random_signal.end(), normalized_signal.begin());

    std::vector<double> ref{
        5.9284461652, 8.4426574426, 8.5794561999, 8.4725173738, 6.235636965,
        3.8438170837, 2.9753460536, 0.5671297593, 2.7265629474, 4.7766511174
    };

    //std::vector<double> x(10);
    //std::iota(x.begin(), x.end(), 10);

    //plt::Plot plot;
    //plot.palette("set2");
    //plot.drawCurve(x, normalized_signal).label("normalized signal with rms").lineWidth(4);

    //plt::Plot plot2;
    //plot2.palette("set2");
    //plot2.drawCurve(x, random_signal).label("signal").lineWidth(4);

    //plt::Figure figure({{plot2}, {plot}});
    //figure.size(749, 749);
    //figure.show();

    CHECK_THAT(random_signal, Catch::Matchers::Approx(ref));

///! [normalize_real_data_rms]
}

TEST_CASE("We want to be able to compute the rms of real data","[algorithms][rms]")
{
///! [rms_real_data]
    std::mt19937 gen(0); //Standard mersenne_twister_engine seeded with 0

    std::uniform_real_distribution<> dis(1.0, 2.0);

    std::vector<double> random_signal(10);

    std::generate(random_signal.begin(), random_signal.end(), std::bind(dis, gen));

    auto rms = spp::rms(random_signal.begin(), random_signal.end());

    CHECK(rms == Catch::Approx(1.5478575322));
///! [rms_real_data]
}
