#include "engine/dft/dft.hpp"
#include "engine/algorithms/generation.hpp"
#include "engine/complex/algorithms.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

SCENARIO("We want to be able to compute the real to complex fft using fftw3 library", "[dft][fftw3_wrapper][r2c]")
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

        ngn::linespace(t.begin(), t.end(), dt);

        ngn::amplitude_modulated_waveform(t.begin(), t.end(), signal.begin(), amp_carrier, freq_carrier_Hz, amp_modu, freq_modu_Hz);

        GIVEN("allocated memory for periodogram")
        {
            auto spectrum_size = ngn::dft_size_r2c(t.begin(), t.end());

            std::vector<fftw_complex> spectrum(std::move(spectrum_size));// @todo use pmr style allocation 

            WHEN("calling fft1d(dft::policy::fftw, signal.begin(), signal.end(), spectrum.begin())")
            {
                ngn::fft1d(ngn::dft::policy::fftw, signal.begin(), signal.end(), spectrum.begin());

                THEN("The periodogram is correctly allocated")
                {
                    std::vector<double> spectrum_real(spectrum_size);

                    ngn::copy_real(spectrum.begin(), spectrum.end(), spectrum_real.begin());

                    std::vector<double> spectrum_imag(spectrum_size);

                    ngn::copy_imag(spectrum.begin(), spectrum.end(), spectrum_imag.begin());

                    std::vector<double> ref_spectrum_real{ 
                        1.7071067812, 1.7322337742, 1.8140021164, 1.9774196978, 2.2975759404, 
                        3.0872975643, 9.5809808711, -0.8365844907, 0.9764081408, 1.8763094389, 
                        2.9659772208, 5.1942055518, 15.881218621, -15.881218621, -5.1942055518, 
                        -2.9659772208, -1.8763094389, -0.9764081408, 0.8365844907, -9.5809808711, 
                        -3.0872975643, -2.2975759404, -1.9774196978, -1.8140021164, -1.7322337742, 
                        -1.7071067812 
                    };

                    std::vector<double> ref_spectrum_imag{
                        0.0, -0.0914985754, -0.2006721044, -0.3570844584, -0.6357488894, 
                        -1.3449970239, -7.7089328815, 2.9076279039, 1.4022053526, 1.0037421793, 
                        0.8312538756, 0.7470418822, 0.7113204416, 0.7113204416, 0.7470418822, 
                        0.8312538756, 1.0037421793, 1.4022053526, 2.9076279039, -7.7089328815, 
                        -1.3449970239, -0.6357488894, -0.3570844584, -0.2006721044, -0.0914985754, 0.0                     
                    };

                    CHECK_THAT(spectrum_real, Catch::Matchers::Approx(ref_spectrum_real));

                    CHECK_THAT(spectrum_imag, Catch::Matchers::Approx(ref_spectrum_imag));
                }
            }
        }
    }
}
