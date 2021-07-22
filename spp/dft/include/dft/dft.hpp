#pragma once

#include "fftw3/fftw3_wrapper.hpp"


namespace dft
{
template<typename InputIte, typename OutputIte>
OutputIte fft1d(InputIte first, InputIte last, OutputIte res)
{
    return fft1d(policy::defaut, first, last, res);
}
}