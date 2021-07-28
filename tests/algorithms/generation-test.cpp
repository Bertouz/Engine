#include <vector>
#include "algorithms/generation.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

SCENARIO("We want to be able to compute a linear spaced range", "[algorithms][generation][linespace]")
{
    GIVEN("a vector with a size n = 50 and dt = 5")
    {
        constexpr int n = 50;

        constexpr double dt = 5;

        std::vector<double> t(n);

        WHEN("calling spp::linespace")
        {
            spp::linespace(t.begin(), t.end(), dt);

            THEN("We have { 0,5,10,15,20,25,30,35,40,45,50 }")
            {
                std::vector<double> ref_linspace{ 0,5,10,15,20,25,30,35,40,45,50 };

                CHECK_THAT(ref_linspace, Catch::Matchers::Approx(ref_linspace));
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

        spp::linespace(t.begin(), t.end(), dt);

        WHEN("calling spp::amplitude_modulated_waveform")
        {
            spp::amplitude_modulated_waveform(t.begin(), t.end(), signal.begin(), amp_carrier, freq_carrier_Hz, amp_modu, freq_modu_Hz);

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