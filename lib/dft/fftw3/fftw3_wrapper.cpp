#include "engine/dft/fftw3/fftw3_wrapper.hpp"

namespace ngn
{
namespace fftw
{

auto fft1d_r2c(const double *first, const double *last, std::complex<double> *res) -> std::complex<double> *
{
    fftw_complex *res_fftw = reinterpret_cast<fftw_complex *>(res);
    fft1d_r2c(first, last, res_fftw);
    const int n = std::distance(first, last);
    return res + n;
}

auto fft1d_r2c(const double *first, const double *last, fftw_complex *res) -> fftw_complex *
{
    const int n = std::distance(first, last);
    // We remove the const of the ptr because we use the flag 'FFTW_PRESERVE_INPUT' that assure us to not modify the
    // input Else we can't do that We know the risks
    fftw_plan p = fftw_plan_dft_r2c_1d(n, (double *)first, res, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
    fftw_execute(p);
    fftw_destroy_plan(p);
    return res + n;
}

} // namespace fftw
} // namespace ngn
