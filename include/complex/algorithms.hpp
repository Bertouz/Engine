#include "concepts.hpp"

namespace spp
{

template<CComplex T>
constexpr auto norm(T cpx)
{
    return cpx[0]*cpx[0] + cpx[1]*cpx[1];
}

template<StdComplex T>
constexpr auto norm(T cpx)
{
    return std::norm(cpx);
}

template<typename InputIte, typename OutputIte>
requires ComplexIterator<InputIte> && RealIterator<OutputIte>
inline auto norm(InputIte first, InputIte last, OutputIte res)->OutputIte
{
    return std::transform(first, last, res, norm<typename InputIte::value_type>);
}

}