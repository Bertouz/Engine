#pragma once
#include "engine/dft.hpp"
#include "engine/complex.hpp"
#include <algorithm>
#include <functional>
#include <numeric>
#include "engine/algorithms.hpp"

//Declarations
namespace ngn
{

/**
 * @brief periodogram - peridogram compute the periodogram of real input data
 * Since the inputs is real the periodogram will be symetric around the zero frequency so we have an output of N/2 +1 where N is the size of the input range
 * @tparam InputIte - Type of the input iterator
 * @tparam OuputIte - Type of the result iterator
 * @param[in] first - Iterator to the beginning of the range of the real signal whom we want the periodogram
 * @param[in] last  - Iterator to the end of the range of the real signal whom we want the periodogram
 * @param[out] res - Iterator to the beginning of the periodogram
 * @snippet spectral_analysis/periodogram-example.cpp periodogram
 * @image html spectral_analysis/periodogram.svg
 * @ingroup SpectralAnalysis
 * @return
 */
template<RealInputOutputIterator InputIte, RealInputOutputIterator OutputIte>
inline auto periodogram(InputIte first, InputIte last, OutputIte res)->OutputIte;
}




//Definitions
namespace ngn
{

template<RealInputOutputIterator InputIte, RealInputOutputIterator OutputIte>
inline auto periodogram(InputIte first, InputIte last, OutputIte res)->OutputIte
{
    // using temporary complex spectrum so we use {real/cpx} to cpx dft

    size_t spectrum_size = dft_size_r2c(first, last);

    std::vector<std::complex<double>> spectrum(spectrum_size, {0.0,0.0});// @todo use pmr style allocation to avoid temporary allocation

    fft1d(first, last, spectrum.begin());

    OutputIte res_last = norm(spectrum.cbegin(), spectrum.cend(), res);

    // We normalize the periodogram with the rms
    normalise(res, res_last, res, rms<OutputIte>);

    return res_last;
}

}
