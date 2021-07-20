#ifndef DFT_HPP
#define DFT_HPP
#include "policies.hpp"
#include "fftw3/fftw3_wrapper.hpp"

/**
 * @defgroup dft
 */

/**
 * @brief fft1d - Compute the 1d Fft of a range of values using the default policy
 * @tparam InputIte - type of input iterator for wich we want to compute the fft
 * @tparam OutputIte - type of the result iterator 
 * @param[in] first -
 * @param[in] last - 
 * @param[out] res - 
 * @addtogroup dft
 */ 
template<typename InputIte, typename OutputIte>
OutputIte fft1d(InputIte first, InputIte last, OutputIte res);

/**
 * @brief fft1d - Compute the 1d Fft of a range of values using the default policy
 * @tparam Policy - Type of the policy we want to use for the computation
 * @tparam InputIte - type of input iterator for wich we want to compute the fft
 * @tparam outputite - type of the result iterator 
 * @param[in] first -
 * @param[in] last - 
 * @param[out] res - 
 * @addtogroup dft
 */ 
template<typename Policy, typename InputIte, typename OutputIte>
OutputIte fft1d(Policy, InputIte first, InputIte last, OutputIte res);

/**
 * @brief fft1d - Compute the 1d Fft of a range of values using the default policy
 * @tparam InputIte - type of input iterator for wich we want to compute the fft
 * @tparam outputite - type of the result iterator 
 * @tparam FFTPlan - type of the precomputed plan we want to use to speed up the computation 
 * @param[in] first -
 * @param[in] last - 
 * @param[out] res - 
 * @addtogroup dft
 */ 
template<typename InputIte, typename OutputIte, typename FFTPlan>
OutputIte fft1d(InputIte first, InputIte last, OutputIte res, FFTPlan const& plan);

/**
 * @brief fft1d - Compute the 1d Fft of a range of values using the default policy
 * @tparam Policy - Type of the policy we want to use for the computation
 * @tparam InputIte - type of input iterator for wich we want to compute the fft
 * @tparam outputite - type of the result iterator 
 * @tparam FFTPlan - type of the precomputed plan we want to use to speed up the computation 
 * @param[in] first -
 * @param[in] last - 
 * @param[out] res - 
 * @addtogroup dft
 */ 
template<typename Policy, typename InputIte, typename OutputIte, typename FFTPlan>
OutputIte fft1d(Policy, InputIte first, InputIte last, OutputIte res, FFTPlan const& plan);


#endif // DFT_HPP
