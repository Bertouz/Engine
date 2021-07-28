#include "spectral_analysis/spectral_analysis.hpp"
#include "algorithms/generation.hpp"
#include "plot/plot.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

SCENARIO("We want to compute the periodogram of a real waveform", "[periodogram]")
{
    GIVEN("A real waveform")
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

        spp::amplitude_modulated_waveform(t.begin(), t.end(), signal.begin(), amp_carrier, freq_carrier_Hz, amp_modu, freq_modu_Hz);

        GIVEN("allocated memory for periodogram")
        {
            std::vector<double> periodogram(n/2+1);

            WHEN("calling spp::periodogram(signal.begin(), signal.end(), periodogram.begin())")
            {
                spp::periodogram(signal.begin(), signal.end(), periodogram.begin());

                THEN("The periodogram is correctly allocated")
                {
                    std::vector<double> ref_periodogram{
                            0.0029865797, 0.0030837259, 0.0034135857, 0.0041379627, 0.0058241537, 
                            0.0116220302, 0.1549780276, 0.0093814914, 0.0029920515, 0.0046404763, 
                            0.0097236113, 0.0282216665, 0.2589946376, 0.2589946376, 0.0282216665, 
                            0.0097236113, 0.0046404763, 0.0029920515, 0.0093814914, 0.1549780276, 
                            0.0116220302, 0.0058241537, 0.0041379627, 0.0034135857, 0.0030837259, 
                            0.0029865797 
                    };

                    std::vector<double> f(periodogram.size());

                    spp::linespace(f.begin(), f.end(), freq_res);

                    /// Plot to check the result values
                    //plt::Plot plot_spectre;
                    //plot_spectre.palette("set2");
                    //plot_spectre.drawCurve(f, periodogram).label("periodogram(y)").lineWidth(4);

                    //plt::Figure figure({{plot_spectre}});
                    //figure.size(749, 749);
                    //figure.show();

                    CHECK_THAT(periodogram, Catch::Matchers::Approx(ref_periodogram));
                }
            }
        }
    }
}
