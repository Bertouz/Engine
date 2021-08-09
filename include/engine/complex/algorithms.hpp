#pragma once
#include "concepts.hpp"
#include <functional>
#include <algorithm>
#include <complex>

// definitions
namespace ngn
{
/**
 * @brief real - return the real value of array as complex type like fftw_complex
 * @tparam T - array of size twà
 * @param[in] cpx - complex value
 * @ingroup Complex
 */
template<CComplex T>
constexpr auto real(const T& cpx);

/**
 * @brief imag
 * @param cpx
 * @ingroup Complex
 */
template<CComplex T>
constexpr auto imag(const T& cpx);

/**
 * @brief real -Return the real part of a std complex
 * @param[in] cpx
 * @ingroup Complex
 */
template<StdComplex T>
constexpr auto real(const T& cpx);

/**
 * @brief imag - Return the imaginary part of a std complex
 * @param cpx
 * @ingroup Complex
 */
template<StdComplex T>
constexpr auto imag(const T& cpx);

/**
 * @brief norm
 * @param first
 * @param last
 * @param res
 * @return
 * @ingroup Complex
 */
template<ComplexIterator InputIte, RealIterator OutputIte>
inline auto norm(InputIte first, InputIte last, OutputIte res)->OutputIte;

/**
 * @brief norm - compute the |cpx|^2 of a fftw_complex style complex number
 * @param cpx
 * @ingroup Complex
 */
template<CComplex T>
constexpr auto norm(const T& cpx);

/**
 * @brief norm
 * @param cpx
 * @ingroup Complex
 */
template<StdComplex T>
constexpr auto norm(const T& cpx);

/**
 * @brief copy_real
 * @param first
 * @param last
 * @param res
 * @return
 * @ingroup Complex
 */
template<ComplexIterator InputIte, RealIterator OutputIte>
inline auto copy_real(InputIte first, InputIte last, OutputIte res)->OutputIte;

/**
 * @brief copy_imag
 * @param first
 * @param last
 * @param res
 * @return
 * @ingroup Complex
 */
template<ComplexIterator InputIte, RealIterator OutputIte>
inline auto copy_imag(InputIte first, InputIte last, OutputIte res)->OutputIte;
}

// declarations
namespace  ngn{

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

template<ComplexIterator InputIte, RealIterator OutputIte>
inline auto norm(InputIte first, InputIte last, OutputIte res)->OutputIte
{
    OutputIte res_last = std::transform(first, last, res, std::bind(norm<typename InputIte::value_type>, std::placeholders::_1));
    return res_last;
}

template<ComplexIterator InputIte, RealIterator OutputIte>
inline auto copy_real(InputIte first, InputIte last, OutputIte res)->OutputIte
{
    return std::transform(first, last, res, real<typename InputIte::value_type>);
}

template<ComplexIterator InputIte, RealIterator OutputIte>
inline auto copy_imag(InputIte first, InputIte last, OutputIte res)->OutputIte
{
    return std::transform(first, last, res, imag<typename InputIte::value_type>);
}

}
