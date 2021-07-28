#pragma once 
#include <iterator>
#include <concepts>
#include <type_traits>
#include <complex>

namespace spp 
{
///@note ce sont plus des concepts sur les complex... 

template<typename T>
using IsReal = std::is_arithmetic<T>;

template<typename T>
concept Real = IsReal<T>::value;

template<typename T>
struct IsStdComplex;

template<typename T>
struct IsStdComplex<std::complex<T>>;

template<typename T>
struct IsStdComplex : std::false_type
{};

template<typename T>
struct IsStdComplex<std::complex<T>> : std::true_type
{};

template<typename T>
struct IsCComplex
{
    static constexpr bool value = std::is_array_v<T> && std::extent_v<T> == 2;
};

template<typename T>
concept CComplex = IsCComplex<T>::value;

template<typename T>
concept StdComplex = IsStdComplex<T>::value;

template<typename T>
concept Complex = StdComplex<T> || CComplex<T>;

template<typename T>
concept RealIterator = Real<typename std::iterator_traits<T>::value_type>;

template<typename T>
concept ComplexIterator = Complex<typename std::iterator_traits<T>::value_type>;

template<typename T>
concept RealContiguousIterator = RealIterator<T> && std::contiguous_iterator<T>;

template<typename T>
concept ComplexContiguousIterator = ComplexIterator<T> && std::contiguous_iterator<T>;

template<typename T>
concept RealInputContiguousIterator = RealContiguousIterator<T> && std::input_iterator<T>;

template<typename T>
concept ComplexInputContiguousIterator = ComplexContiguousIterator<T> && std::input_iterator<T>;

template<typename T>
concept RealInputOutputContiguousIterator = RealContiguousIterator<T> && std::input_or_output_iterator<T>;

template<typename T>
concept ComplexInputOutputContiguousIterator = ComplexContiguousIterator<T> && std::input_or_output_iterator<T>;

template<typename IteType>
concept RealOutputContiguousIterator = RealContiguousIterator<IteType>  && std::input_or_output_iterator<IteType>/*Real<RealValueType> &&std::output_iterator<IteType, RealValueType>*/;

template<typename IteType>
concept ComplexOutputContiguousIterator = ComplexContiguousIterator<IteType> &&  std::input_or_output_iterator<IteType>/*&&Complex<ComplexValueType> && std::output_iterator<IteType, ComplexValueType>*/;

}