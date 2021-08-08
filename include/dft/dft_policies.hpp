#pragma once
#include <type_traits>
#include <array>

namespace spp 
{
namespace dft
{
namespace policy
{
/**
 * @brief fftw_t - fftw policy for selecting fftw for computing dft
 * @ingroup Dft
 */
struct Fftw{};

/**
 * @ingroup Dft
 */
inline constexpr Fftw fftw{};

/**
 * @ingroup Dft
 */
inline constexpr auto defaut = fftw;

/**
 * @ingroup Dft
 */
using default_type = std::remove_const_t<decltype(policy::defaut)>;

}

template<typename T>
struct complex;

/**
 * @brief The complex struct
 * @ingroup Dft
 */
template<>
struct complex<policy::Fftw>
{
    using type = std::array<double,2>;
};

/**
 * @ingroup Dft
 */
using defaut_cpx_value_type = typename complex<policy::default_type>::type;

}
}
