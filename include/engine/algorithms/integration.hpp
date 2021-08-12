#pragma once

#include "engine/complex/concepts.hpp"
#include <iostream>
#include <numeric>

namespace ngn
{

/**
 * @brief integrate - compute the default integral of the given range
 * We use the zero order midpoint method with a domain in [0.. 1]
 * @tparam InputIte - Type of the input iterator, it must be a real data iterator
 * @param[in] first - Iterator to the beginning of the range we want to integrate
 * @param[in] last  - Iterator to the end of the range we want to integrate
 * @snippet algorithms/test-integration.cpp integration_real_data_default_01
 * @ingroup Algorithms
 */
template <RealInputOutputIterator InputIte> inline auto integrate(InputIte first, InputIte last);

/**
 * @brief integrate - compute the default integral of the given range
 * We use the zero order midpoint method with a domain in [0.. 1]
 * @tparam InputIte - Type of the input iterator, it must be a real data iterator
 * @param[in] first - Iterator to the beginning of the range we want to integrate
 * @param[in] last  - Iterator to the end of the range we want to integrate
 * @param[in] a - inferior born of the integration
 * @param[in] b - superior born of the integration
 * @snippet algorithms/test-integration.cpp integration_real_data_default_ab
 * @ingroup Algorithms
 */
template <RealInputOutputIterator InputIte, Real T> inline auto integrate(InputIte first, InputIte last, T a, T b);

/**
 * @brief rms
 * @param first
 * @param last
 * @snippet algorithms/test-normalize.cpp rms_real_data
 */
template <RealInputOutputIterator InputIte> inline auto rms(InputIte first, InputIte last);

/**
 * @brief normalise - Normalize the input range so that sum(first, last) / N = 1
 * We use the midpoint integration method within interval x in [0..1]
 * @tparam InputIte - Type of the input iterator
 * @tparam OuputIte - Type of the result iterator
 * @param[in] first - Iterator to the beginning of the range we want to normalize
 * @param[in] last  - Iterator to the end of the range we want to normalize
 * @param[out] res - Iterator to the beginning of the normalized signal
 * @snippet algorithms/test-normalize.cpp normalize_real_data
 * @ingroup Algorithms
 * @return
 */
template <RealInputOutputIterator InputIte, RealInputOutputIterator OutputIte>
inline auto normalise(InputIte first, InputIte last, OutputIte res) -> OutputIte;

/**
 * @brief normalise - Normalize the input range so that sum(first, last) / N = 1
 * We use the midpoint integration method within interval x in [0..1]
 * @tparam InputIte - Type of the input iterator
 * @tparam OuputIte - Type of the result iterator
 * @tparam Func - Callable
 * @param[in] first - Iterator to the beginning of the range we want to normalize
 * @param[in] last  - Iterator to the end of the range we want to normalize
 * @param[out] res - Iterator to the beginning of the normalized signal
 * @param[in] f - Callable that compute the normalisation foctor of the input range
 * @snippet algorithms/test-normalize.cpp normalize_real_data_rms
 * @ingroup Algorithms
 * @return

 */
template <RealInputOutputIterator InputIte, RealInputOutputIterator OutputIte, typename Func>
inline auto normalise(InputIte first, InputIte last, OutputIte res, Func f) -> OutputIte;

} // namespace ngn

namespace ngn
{

template <RealInputOutputIterator InputIte> inline auto rms(InputIte first, InputIte last)
{
    auto sum2 = std::accumulate(first, last, 0.0, [](auto first, auto curr) { return first + curr * curr; });
    auto size = std::distance(first, last);

    return std::sqrt(std::move(sum2) / std::move(size));
}

template <RealInputOutputIterator InputIte> inline auto integrate(InputIte first, InputIte last)
{
    return integrate(first, last, 0.0, 1.0);
}

template <RealInputOutputIterator InputIte, Real T> inline auto integrate(InputIte first, InputIte last, T a, T b)
{
    return std::reduce(first, last) * (b - a) / std::distance(first, last);
}

template <RealInputOutputIterator InputIte, RealInputOutputIterator OutputIte, typename Func>
inline auto normalise(InputIte first, InputIte last, OutputIte res, Func fun) -> OutputIte
{
    const auto normalisation_factor = fun(first, last);

    OutputIte res_last = std::transform(
        first, last, res, [normalisation_factor](auto const &value) { return value / normalisation_factor; });
    return res_last;
}

template <RealInputOutputIterator InputIte, RealInputOutputIterator OutputIte>
inline auto normalise(InputIte first, InputIte last, OutputIte res) -> OutputIte
{
    return normalise(first, last, res, integrate<InputIte>);
}

} // namespace ngn
