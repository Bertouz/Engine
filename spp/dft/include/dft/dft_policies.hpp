
#pragma once

/**
 * @defgroup dft_policy
 * @addtogroup dft
 */
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

}
}