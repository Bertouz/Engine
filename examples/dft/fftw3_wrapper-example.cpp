#include "dft/dft.hpp"
#include "plot/plot.hpp"
#include "spectral_analysis/spectral_analysis.hpp"
#include "algorithms/generation.hpp"

#include <sstream>
#include <functional>
#include <numeric>
#include <vector>
#include <cmath>
#include <iostream>
#include <complex>
#include <complex.h>
#include <numbers>
#include <filesystem>

int main()
{
    ///! [periodogram]
    constexpr int n = 10'000;

    constexpr double tstart_s = 0;

    constexpr double tstop_s = 1;

    constexpr double signal_duration = tstop_s - tstart_s;

    constexpr double dt =  signal_duration / n; 

    constexpr double fe = 1 / dt;

    constexpr double freq_res =  fe / n;

    constexpr double freq_carrier_Hz = fe/4;

    constexpr double freq_modu_Hz = freq_carrier_Hz/2;

    std::cout<<"tstart_s = "<<tstart_s<<std::endl;
    std::cout<<"tstop_s = "<<tstop_s<<std::endl;
    std::cout<<"signal_duration = "<<tstop_s<<std::endl;
    std::cout<<"dt = "<<dt<<std::endl;
    std::cout<<"fe = "<<fe<<std::endl;
    std::cout<<"freq_res = "<<freq_res<<std::endl;
    std::cout<<"freq_carrier_Hz = "<<freq_carrier_Hz<<std::endl;
    std::cout<<"freq_modu_Hz = "<<freq_modu_Hz<<std::endl;

    static_assert(freq_carrier_Hz < fe/2 );

    static_assert(freq_modu_Hz < fe/2 );

    constexpr double amp_modu = 1;
     
    constexpr double amp_carrier = 1;
    
    std::vector<double> signal(n);

    std::vector<double> t(n);

    spp::linespace(t.begin(), t.end(), dt);

    spp::amplitude_modulated_waveform(t.begin(), t.end(), signal.begin(), amp_carrier, freq_carrier_Hz, amp_modu, freq_modu_Hz);

    std::vector<double> periodogram(n/2+1);

    spp::periodogram(signal.begin(), signal.end(), periodogram.begin());

    plt::Plot plot;
    plot.palette("set2");
    plot.drawCurve(t, signal).label("y(t)").lineWidth(4);

    std::vector<double> f(periodogram.size());

    spp::linespace(f.begin(), f.end(), freq_res);

    plt::Plot plot_spectre;
    plot_spectre.palette("set2");
    plot_spectre.drawCurve(f, periodogram).label("periodogram(y)").lineWidth(4);

    plt::Figure figure({{plot}, {plot_spectre}});
    figure.size(749, 749);
    //figure.show();
    
    // Save image for documentation
    std::filesystem::path fftw3_wrapper_image_dir = std::filesystem::path(DOC_IMAGE_BUILD_DIR) / std::filesystem::path("spectral_analysis");
    std::filesystem::create_directories(fftw3_wrapper_image_dir);
    const std::filesystem::path image_path =  fftw3_wrapper_image_dir / "periodogram.svg";
    figure.save(image_path.string());

    ///! [periodogram]
}