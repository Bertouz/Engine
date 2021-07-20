#include "dft/fftw3/fftw3_wrapper.hpp"
#include "plot/plot.hpp"

#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <functional>
#include <numeric>
#include <vector>
#include <cmath>
#include <iostream>
#include <complex>
#include <complex.h>
//#include <numbers>

SCENARIO("We want to be able to compute the real to real fft using fftw3 library", "[dft][fftw3_wrapper][r2c]")
{
    ///! [fftw_wrapper_1d_r2r]
    constexpr int n = 100;
    constexpr double freq = 4.0 / 100;

    double* signal = (double*) fftw_malloc(sizeof(double) * n);

    fftw_complex* spectrum = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (n/2+1));

    fftw_plan p = fftw_plan_dft_r2c_1d(n, signal, spectrum, FFTW_ESTIMATE /*FFTW_PRESERVE_INPUT*/);

    std::vector<double> t(n);

    std::iota(t.begin(), t.end(), 0);

    for(size_t id = 0; id < n; ++id)
    {
       signal[id] = std::sin(2*3.14*freq*t[id]);
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


    auto figure = plt::make_figure(std::vector<std::vector<double>>{t, t}, std::vector<std::vector<double>>{ss, s_norm});
    //plt::Plot plot;
    //plot.palette("set2");
    //plot.drawCurve(t, ss).label("signal").lineWidth(4);


    //plt::Plot plot_spectre;
    //plot_spectre.palette("set2");
    //plot_spectre.drawCurve(t, s_norm).label("spectre real").lineWidth(4);


    //plt::Figure figure({{plot}, {plot_spectre}});
    //figure.size(749, 749);
    //figure.show();
    //figure.save("/tmp/ffwt3_wrapper.svg");

    //fftw_destroy_plan(p);
    //fftw_free(signal); 
    //fftw_free(spectrum);

    ///! [fftw_wrapper_1d_r2r]
}
