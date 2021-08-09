#pragma once
#include "fftw3.h"
#include "engine/dft/dft_policies.hpp"
#include "engine/dft/dft_wrapper_api.hpp"
#include "engine/dft/dft_types.hpp"
#include "engine/complex/concepts.hpp"

#include <iterator>

/**
 * @defgroup FFTW3
 * @ingroup Dft
 */

namespace ngn // definitions
{
namespace fftw
{

/**
 * @brief fft1d_r2c
 * @param first
 * @param last
 * @param res
 * @ingroup FFTW3
 */
auto fft1d_r2c( const double* first, const double* last, fftw_complex* res)->fftw_complex*;

/**
 * @brief fft1d_r2c
 * @param first
 * @param last
 * @param res
 * @ingroup FFTW3
 */
auto fft1d_r2c( const double* first, const double* last, std::complex<double>* res)->std::complex<double>*;

/**
 * @brief fft1d
 * @param first
 * @param last
 * @param res
 * @return
 * @ingroup FFTW3
 */
template<RealInputContiguousIterator InputIte, ComplexOutputContiguousIterator OutputIte>
inline auto fft1d(InputIte first, InputIte last, OutputIte res)->OutputIte
{
    auto in_start = std::addressof(*first);
    auto in_end = std::addressof(*last);
    auto out_start = std::addressof(*res);
    auto tmp = fft1d_r2c(in_start, in_end, out_start);
    std::advance(res, std::distance(first, last));
    return res;
}

}

/**
 * @brief fft1d - Compute the 1d Fft of a range of values using the fftw library
 * @tparam Policy - Type of the policy we want to use for the computation
 * @tparam InputIte - type of input iterator for wich we want to compute the fft
 * @tparam outputite - type of the result iterator 
 * @param[in] first -
 * @param[in] last - 
 * @param[out] res - 
 * @ingroup FFTW3
 */ 
template<std::input_iterator InputIte, std::input_or_output_iterator OutputIte>
inline auto fft1d(dft::policy::Fftw, InputIte first, InputIte last, OutputIte res)->OutputIte
{
    return fftw::fft1d(first, last, res);
}

}
