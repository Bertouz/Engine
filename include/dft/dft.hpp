#pragma once

#include "fftw3/fftw3_wrapper.hpp"


namespace spp
{

template<RealIterator InputIte>
constexpr auto dft_size_r2c(InputIte first, InputIte last)->size_t
{
   return std::distance(first, last) / 2 + 1;
}

/**
 * @brief fft1d - Compute the 1d Fft of a range of values using the default policy
 * @tparam InputIte - type of input iterator for wich we want to compute the fft
 * @tparam OutputIte - type of the result iterator 
 * @param[in] first -
 * @param[in] last - 
 * @param[out] res - 
 * @addtogroup dft
 */ 
template<std::input_iterator InputIte, std::input_or_output_iterator OutputIte>
inline auto fft1d(InputIte first, InputIte last, OutputIte res)->OutputIte
{
    return fft1d(dft::policy::defaut, first, last, res);
}
}