#pragma once
#include <iterator>
#include <algorithm>
#include <numbers>
#include <cmath>
#include <iostream>

namespace ngn
{

/**
 * @brief linespace
 * @param first
 * @param last
 * @param delta
 * @ingroup Algorithms
 */
template<std::forward_iterator Ite, typename T>
inline void linespace(Ite first, Ite last, T delta);

/**
 * @brief range
 * @param first
 * @param last
 * @param start
 * @param end
 * @ingroup Algorithms
 */
template<std::forward_iterator Ite, typename T>
inline void range(Ite first, Ite last, T start, T end);

/**
 * @brief amplitude_modulated_waveform
 * @param first
 * @param last
 * @param res
 * @param carrier_amplitude
 * @param carrier_frequency
 * @param modu_amplitude
 * @param modu_frequency
 * @ingroup Algorithms
 * @return
 */
template<typename IteIn, typename IteOut, typename T>
inline auto amplitude_modulated_waveform(IteIn first, IteIn last, IteOut res, T carrier_amplitude, T carrier_frequency, T modu_amplitude, T modu_frequency)->IteOut;

}

namespace ngn
{

template<std::forward_iterator Ite, typename T>
inline void linespace(Ite first, Ite last, T delta)
{
    std::generate(first, last, [id=0, delta]()mutable{
        return id++*delta;
    });
}

template<std::forward_iterator Ite, typename T>
inline void range(Ite first, Ite last, T start, T end)
{
    double delta = (end - start) / static_cast<double>(std::distance(first, last) - 1);
    std::generate(first, last, [id=0, delta, start]()mutable{
        return start + id++*delta;
    });
}

template<typename IteIn, typename IteOut, typename T>
inline auto amplitude_modulated_waveform(IteIn first, IteIn last, IteOut res, T carrier_amplitude, T carrier_frequency, T modu_amplitude, T modu_frequency)->IteOut
{
    return std::transform(first, last, res, [&](auto time){
        auto a = 2 * std::numbers::pi * time;
        return (1 + modu_amplitude * cos(a * modu_frequency )) * carrier_amplitude * sin(a * carrier_frequency);
    });
}

}
