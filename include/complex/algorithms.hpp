#include "concepts.hpp"

namespace spp
{

template<CComplex T>
constexpr auto real(const T& cpx)
{
    return cpx[0];
}

template<CComplex T>
constexpr auto imag(const T& cpx)
{
    return cpx[1];
}

template<StdComplex T>
constexpr auto real(const T& cpx)
{
    return std::real(cpx);
}

template<StdComplex T>
constexpr auto imag(const T& cpx)
{
    return std::imag(cpx);
}

template<CComplex T>
constexpr auto norm(const T& cpx)
{
    return cpx[0]*cpx[0] + cpx[1]*cpx[1];
}

template<StdComplex T>
constexpr auto norm(const T& cpx)
{
    return std::norm(cpx);
}

template<typename InputIte, typename OutputIte>
requires ComplexIterator<InputIte> && RealIterator<OutputIte>
inline auto norm(InputIte first, InputIte last, OutputIte res)->OutputIte
{
    return std::transform(first, last, res, norm<typename InputIte::value_type>);
}

template<typename InputIte, typename OutputIte>
requires ComplexIterator<InputIte> && RealIterator<OutputIte>
inline auto copy_real(InputIte first, InputIte last, OutputIte res)->OutputIte
{
    return std::transform(first, last, res, real<typename InputIte::value_type>);
}

template<typename InputIte, typename OutputIte>
requires ComplexIterator<InputIte> && RealIterator<OutputIte>
inline auto copy_imag(InputIte first, InputIte last, OutputIte res)->OutputIte
{
    return std::transform(first, last, res, imag<typename InputIte::value_type>);
}

}