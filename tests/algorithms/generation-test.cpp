#include <vector>
#include "engine/algorithms/generation.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

SCENARIO("We want to be able to compute a linear spaced range starting at zero", "[algorithms][generation][linespace]")
{
    GIVEN("a vector with a size n = 50 and dt = 5")
    {
        constexpr int n = 10;

        constexpr double dt = 5;

        std::vector<double> t(n);

        WHEN("calling ngn::linespace")
        {
            ngn::linespace(t.begin(), t.end(), dt);

            THEN("We have {0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0}")
            {
                std::vector<double> ref_linspace{0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0};

                CHECK_THAT(t, Catch::Matchers::Approx(ref_linspace));
            }
        }
    }


}

SCENARIO("We want to be able to compute linear spaced range between two given values", "[algorithms][generation][range]")
{
    GIVEN("a vector with a size n = 50 and dt = 5")
    {
        constexpr int n = 10;

        std::vector<double> t(n);

        WHEN("calling ngn::range(begin, end, -5, 5)")
        {
            ngn::range(t.begin(), t.end(), -5.0, 5.0);

            THEN("We have 10 values in [-5.. 5]")
            {
                std::vector<double> ref_linspace{ -5.0, -3.8888888889, -2.7777777778, -1.6666666667,
                                                  -0.5555555556, 0.5555555556, 1.6666666667,
                                                  2.7777777778, 3.8888888889, 5.0 };

                CHECK_THAT(t, Catch::Matchers::Approx(ref_linspace));
            }
        }

        WHEN("calling ngn::range(begin, end, 0, 10)")
        {
            ngn::range(t.begin(), t.end(), 0.0, 10.0);

            THEN("We have 10  value in [0.. 10]")
            {
                std::vector<double> ref_linspace{ 0.0, 1.1111111111, 2.2222222222, 3.3333333333, 4.4444444444, 5.5555555556,
                                                  6.6666666667, 7.7777777778, 8.8888888889, 10.0};

                CHECK_THAT(t, Catch::Matchers::Approx(ref_linspace));
            }
        }
    }


}

SCENARIO("We want to be able to compute an amplitude modulated waveform", "[algorithms][generation][amplitude_modulated_waveform]")
{
    GIVEN("Some parameters")
    {
        constexpr int n = 50;

        constexpr double tstart_s = 0;

        constexpr double tstop_s = 1;

        constexpr double signal_duration = tstop_s - tstart_s;

        constexpr double dt =  signal_duration / n; 

        constexpr double fe = 1 / dt;

        constexpr double freq_res =  fe / n;

        constexpr double freq_carrier_Hz = fe/4;

        constexpr double freq_modu_Hz = freq_carrier_Hz/2;

        constexpr double amp_modu = 1;
        
        constexpr double amp_carrier = 1;
    
        std::vector<double> signal(n);

        std::vector<double> t(n);

        ngn::linespace(t.begin(), t.end(), dt);

        WHEN("calling ngn::amplitude_modulated_waveform")
        {
            ngn::amplitude_modulated_waveform(t.begin(), t.end(), signal.begin(), amp_carrier, freq_carrier_Hz, amp_modu, freq_modu_Hz);

            THEN("We have an amplitude modulated waveforme")
            {

                std::vector<double> ref_waveform{
                    0.0, -0.0914985754, -0.2006721044, -0.3570844584, -0.6357488894, 
                    -1.3449970239, -7.7089328815, 2.9076279039, 1.4022053526, 1.0037421793, 
                    0.8312538756, 0.7470418822, 0.7113204416, 0.7113204416, 0.7470418822, 
                    0.8312538756, 1.0037421793, 1.4022053526, 2.9076279039, -7.7089328815, 
                    -1.3449970239, -0.6357488894, -0.3570844584, -0.2006721044, -0.0914985754, 0.0                     
                };

                CHECK_THAT(ref_waveform, Catch::Matchers::Approx(ref_waveform));
            }
        }
    }
}
