#pragma once
/**
 * @defgroup fftw3
 * @addtogroup dft
 */
#include "fftw3.h"
#include "dft/dft_policies.hpp"
#include "dft/dft_api.hpp"
#include "dft/dft_types.hpp"
#include "dft/dft_concepts.hpp"

namespace dft // definitions
{
/**
 * @brief fft1d - Compute the 1d Fft of a range of values using the fftw library
 * @tparam Policy - Type of the policy we want to use for the computation
 * @tparam InputIte - type of input iterator for wich we want to compute the fft
 * @tparam outputite - type of the result iterator 
 * @param[in] first -
 * @param[in] last - 
 * @param[out] res - 
 * @addtogroup dft
 */ 
template<typename InputIte, typename OutputIte>
OutputIte fft1d(policy::Fftw, InputIte first, InputIte last, OutputIte res);

namespace fftw
{
auto fft1d_r2c( double* first, double* last, fftw_complex* res)->void;

template<RealContiguousIterator InputIte, ComplexContiguousIterator OutputIte>
auto fft1d( InputIte first, InputIte last, OutputIte res)->OutputIte;

template<ComplexContiguousIterator InputIte, ComplexContiguousIterator OutputIte>
auto fft1d( InputIte first, InputIte last, OutputIte res)->OutputIte;

}

}

namespace dft //declarations
{
template<typename InputIte, typename OutputIte>
OutputIte fft1d(policy::Fftw, InputIte first, InputIte last, OutputIte res)
{
    return fftw::fft1d(first, last, res);
}

namespace fftw
{

auto fft1d_r2c( double* first, double* last, fftw_complex* res)->void
{
    int n = std::distance(first, last);
    fftw_plan p = fftw_plan_dft_r2c_1d(n, first, res, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
    fftw_execute(p);
    fftw_destroy_plan(p);
}

template<RealContiguousIterator InputIte, ComplexContiguousIterator OutputIte>
auto fft1d( InputIte first, InputIte last, OutputIte res)->OutputIte
{
    auto in_start = std::addressof(*first);
    auto in_end = std::addressof(*last);
    auto out_start = std::addressof(*res);
    fft1d_r2c(in_start, in_end, out_start);
    return res;
}

template<ComplexContiguousIterator InputIte, ComplexContiguousIterator OutputIte>
auto fft1d( InputIte first, InputIte last, OutputIte res)->OutputIte
{
    throw std::runtime_error("ididi");
    return res;
}

}

}