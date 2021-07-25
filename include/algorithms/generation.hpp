#include <iterator>
#include <algorithm>
#include <numbers>

namespace spp
{

template<std::forward_iterator Ite, typename T>
inline void linespace(Ite first, Ite last, T delta)
{
    std::generate(first, last, [id=0, delta]()mutable{
        return id++*delta;
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