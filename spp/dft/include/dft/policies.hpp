
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
struct fftw_t{};

using default_policy_t = fftw_t;

inline constexpr fftw_t fftw{};
inline constexpr default_policy_t default_policy{};

}
}