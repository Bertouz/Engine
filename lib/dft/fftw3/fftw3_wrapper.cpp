#include "dft/fftw3/fftw3_wrapper.hpp"

namespace spp
{
namespace fftw
{


auto fft1d_r2c( double* first, double* last, fftw_complex* res)->fftw_complex*
{
    const int n = std::distance(first, last);
    fftw_plan p = fftw_plan_dft_r2c_1d(n, first, res, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
    fftw_execute(p);
    fftw_destroy_plan(p);
    return res + n;
}

}
}