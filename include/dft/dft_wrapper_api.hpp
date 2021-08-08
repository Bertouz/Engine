#pragma once
#include "dft_policies.hpp"
#include <iterator>

namespace spp
{


/**
 * @brief fft1d - Compute the 1d Fft of a range of values using the default policy
 * @tparam Policy - Type of the policy we want to use for the computation
 * @tparam InputIte - type of input iterator for wich we want to compute the fft
 * @tparam outputite - type of the result iterator 
 * @param[in] first -
 * @param[in] last - 
 * @param[out] res - 
 * @ingroup Dft
 */ 
template<typename Policy, std::input_iterator InputIte, std::input_or_output_iterator OutputIte>
inline auto fft1d(Policy, InputIte first, InputIte last, OutputIte res)->OutputIte;

}
