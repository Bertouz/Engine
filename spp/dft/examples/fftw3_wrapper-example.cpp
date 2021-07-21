#include "dft/fftw3/fftw3_wrapper.hpp"
#include "plot/plot.hpp"

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

    //static_assert(freq_carrier_Hz > 2*fe );

    //static_assert(freq_modu_Hz > 2*fe );

    constexpr double amp_modu = 1;
     
    constexpr double amp_carrier = 1;

    double* signal = (double*) fftw_malloc(sizeof(double) * n);

    fftw_complex* spectrum = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (n/2+1));

    fftw_plan p = fftw_plan_dft_r2c_1d(n, signal, spectrum, FFTW_ESTIMATE /*FFTW_PRESERVE_INPUT*/);

    std::vector<double> t(n);

    std::generate(t.begin(), t.end(), [id=0, dt]()mutable{
        return id++*dt;
    });

    for(size_t id = 0; id < n; ++id)
    {
        signal[id] = (1 + amp_modu * cos(2*std::numbers::pi * freq_modu_Hz * t[id])) * amp_carrier * sin(2 * std::numbers::pi * freq_carrier_Hz * t[id]);
    }

    fftw_execute(p);
    std::vector<double> ss(n);
    std::copy(signal, signal+n, ss.begin());
    std::vector<double> s_real(n/2+1);
    std::vector<double> s_imag(n/2+1);
    std::vector<double> s_norm(n/2+1);
    for(size_t id = 0; id < n/2+1; ++id)
    {
        s_real[id] = spectrum[id][0];
        s_imag[id] = spectrum[id][1];
        s_norm[id] = std::norm(std::complex<double>(s_real[id], s_imag[id]));
    }

    const double normalisation = std::accumulate(s_norm.begin(), s_norm.end(), 0.0);

    for(auto& v : s_norm)
    {
        v /= normalisation;
    }

    plt::Plot plot;
    plot.palette("set2");
    plot.drawCurve(t, ss).label("y(t)").lineWidth(4);

    std::vector<double> f(n/2+1);

    std::generate(f.begin(), f.end(), [id=0.0, freq_res]()mutable{
        return id++ * freq_res;
    });

    plt::Plot plot_spectre;
    plot_spectre.palette("set2");
    plot_spectre.drawCurve(f, s_norm).label("|FFT(y(t))|^2").lineWidth(4);


    plt::Figure figure({{plot}, {plot_spectre}});
    figure.size(749, 749);
    figure.show();
    
    // Save image for documentation
    std::filesystem::path fftw3_wrapper_image_dir = std::filesystem::path(DOC_IMAGE_BUILD_DIR) / std::filesystem::path("ffwt3_wrapper");
    std::filesystem::create_directories(fftw3_wrapper_image_dir);
    const std::filesystem::path image_path =  fftw3_wrapper_image_dir / "r2c_sinus.svg";
    figure.save(image_path.string());

    fftw_destroy_plan(p);
    fftw_free(signal); 
    fftw_free(spectrum);

    ///! [fftw_wrapper_1d_r2r]
}