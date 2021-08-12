#include "engine/algorithms/generation.hpp"
#include "engine/plot/plot.hpp"
#include "engine/spectral_analysis/periodogram.hpp"
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

        constexpr double dt = signal_duration / n;

        constexpr double fe = 1 / dt;

        constexpr double freq_res = fe / n;

        constexpr double freq_carrier_Hz = fe / 4;

        constexpr double freq_modu_Hz = freq_carrier_Hz / 2;

        constexpr double amp_modu = 1;

        constexpr double amp_carrier = 1;

        std::vector<double> signal(n);

        std::vector<double> t(n);

        ngn::linespace(t.begin(), t.end(), dt);

        ngn::amplitude_modulated_waveform(t.begin(), t.end(), signal.begin(), amp_carrier, freq_carrier_Hz, amp_modu,
                                          freq_modu_Hz);

        GIVEN("allocated memory for periodogram")
        {
            std::vector<double> periodogram(n / 2 + 1);

            WHEN("calling ngn::periodogram(signal.begin(), signal.end(), periodogram.begin())")
            {
                ngn::periodogram(signal.begin(), signal.end(), periodogram.begin());

                THEN("The periodogram is correctly allocated")
                {
                    std::vector<double> ref_periodogram{
                        0.0354399344, 0.0365927092, 0.0405069557, 0.049102699,  0.0691117078, 0.1379116003,
                        1.839030475,  0.1113244813, 0.0355048641, 0.0550657242, 0.1153842119, 0.3348894392,
                        3.0733326452, 3.0733326452, 0.3348894392, 0.1153842119, 0.0550657242, 0.0355048641,
                        0.1113244813, 1.839030475,  0.1379116003, 0.0691117078, 0.049102699,  0.0405069557,
                        0.0365927092, 0.0354399344};

                    std::vector<double> f(periodogram.size());

                    ngn::linespace(f.begin(), f.end(), freq_res);

                    /// Plot to check the result values
                    // plt::Plot plot_spectre;
                    // plot_spectre.palette("set2");
                    // plot_spectre.drawCurve(f, periodogram).label("periodogram(y)").lineWidth(4);

                    // plt::Figure figure({{plot_spectre}});
                    // figure.size(749, 749);
                    // figure.show();

                    CHECK_THAT(periodogram, Catch::Matchers::Approx(ref_periodogram));
                }
            }
        }
    }
}
