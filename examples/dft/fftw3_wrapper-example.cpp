#include "dft/dft.hpp"
#include "plot/plot.hpp"
#include "spectral_analysis/spectral_analysis.hpp"

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
    ///! [fftw_wrapper_1d_r2r]
    constexpr int n = 10'000;

    constexpr double tstart_s = 0;

    constexpr double tstop_s = 1;

    constexpr double signal_duration = tstop_s - tstart_s;

    constexpr double dt =  signal_duration / n; 

    constexpr double fe = 1 / dt;

    constexpr double freq_res =  fe / n;

    constexpr double freq_carrier_Hz = fe/4;

    constexpr double freq_modu_Hz = freq_carrier_Hz/2;

    static_assert(freq_carrier_Hz < fe / 2);

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

    //std::vector<fftw_complex> spectrum(n/2+1);

    std::vector<double> t(n);

    std::generate(t.begin(), t.end(), [id=0, dt]()mutable{
        return id++*dt;
    });

    for(size_t id = 0; id < n; ++id)
    {
        signal[id] = (1 + amp_modu * cos(2*std::numbers::pi * freq_modu_Hz * t[id])) * amp_carrier * sin(2 * std::numbers::pi * freq_carrier_Hz * t[id]);
    }

    //spp::fft1d(spp::dft::policy::fftw, signal.begin(), signal.end(), spectrum.begin());

    std::vector<double> periodogram(n/2+1);

    spp::periodogram(signal.begin(), signal.end(), periodogram.begin());


    //std::transform(spectrum.begin(), spectrum.end(), std::back_inserter(s_norm.begin()), [](fftw_complex const& cpx){
    //    return std::norm(std::complex<double>(cpx[0], cpx[1]));
    //});

    //const double normalisation = std::reduce(s_norm.begin(), s_norm.end(), 0.0);

    //for(auto& v : s_norm)
    //{
    //    v /= normalisation;
    //}

    plt::Plot plot;
    plot.palette("set2");
    plot.drawCurve(t, signal).label("y(t)").lineWidth(4);

    std::vector<double> f(n/2+1);

    std::generate(f.begin(), f.end(), [id=0.0, freq_res]()mutable{
        return id++ * freq_res;
    });

    plt::Plot plot_spectre;
    plot_spectre.palette("set2");
    plot_spectre.drawCurve(f, periodogram).label("|FFT(y(t))|^2").lineWidth(4);


    plt::Figure figure({{plot}, {plot_spectre}});
    figure.size(749, 749);
    figure.show();
    
    // Save image for documentation
    std::filesystem::path fftw3_wrapper_image_dir = std::filesystem::path(DOC_IMAGE_BUILD_DIR) / std::filesystem::path("ffwt3_wrapper");
    std::filesystem::create_directories(fftw3_wrapper_image_dir);
    const std::filesystem::path image_path =  fftw3_wrapper_image_dir / "r2c_sinus.svg";
    figure.save(image_path.string());

    //fftw_destroy_plan(p);
    //fftw_free(signal); 
    //fftw_free(spectrum);

    ///! [fftw_wrapper_1d_r2r]
}