#pragma once
#include <type_traits>
#include <iterator>
#include "complex/concepts.hpp"

/// @note Voir comment remplacer tous ça par des concepts pour être moins verbeux et plus propre

namespace spp 
{
namespace types
{
/**
 * @ingroup Dft
 */
struct R2C{};
/**
 * @ingroup Dft
 */
struct C2C{};
/**
 * @ingroup Dft
 */
struct C2R{};
/**
 * @ingroup Dft
 */
struct R2R{};

namespace internal
{
template<bool  T, bool U>
struct DftType;

template<>
struct DftType<false , false> : C2C
{};

template<>
struct DftType<true, false> : R2C
{};

template<>
struct DftType<false, true> : C2R
{};

template<>
struct DftType<true, true> : R2R
{};
}

/**
 * @ingroup Dft
 */
template<typename  T, typename U>
struct DftType;


/**
 * @ingroup Dft
 */
template<typename  T, typename U>
struct DftType : internal::DftType<IsReal<T>::value, IsReal<U>::value>
{};
}
}
