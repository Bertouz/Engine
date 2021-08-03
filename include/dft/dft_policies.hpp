#pragma once
#include <type_traits>
#include <array>

/**
 * @defgroup dft_policy
 * @addtogroup dft
 */
namespace spp 
{
namespace dft
{
namespace policy
{
/**
 * @brief fftw_t - fftw policy for selecting fftw for computing dft
 * @addtogroup dft_policy
 */
struct Fftw{};

inline constexpr Fftw fftw{};

inline constexpr auto defaut = fftw;

using default_type = std::remove_const_t<decltype(policy::defaut)>;

}

template<typename T>
struct complex;

template<>
struct complex<policy::Fftw>
{
    using type = std::array<double,2>;
};

using defaut_cpx_value_type = typename complex<policy::default_type>::type;

}
}