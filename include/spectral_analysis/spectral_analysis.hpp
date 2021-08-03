#include "dft/dft.hpp"
#include <algorithm>
#include <functional>
#include <numeric>
#include "complex/algorithms.hpp"

namespace spp
{
    template<std::input_iterator InputIte, std::input_or_output_iterator OutputIte>
    inline auto normalise(InputIte first, InputIte last, OutputIte res)->OutputIte
    {
        const auto normalisation_factor = std::reduce(first, last, 0.0);

        OutputIte res_last = std::transform(first, last, res, [normalisation_factor](auto const& value){
            return value / normalisation_factor;
        });
        return res_last;
    }

    template<RealInputOutputIterator InputIte, RealInputOutputIterator OutputIte>
    inline auto periodogram(InputIte first, InputIte last, OutputIte res)->OutputIte
    {
        // using temporary complex spectrum so we use {real/cpx} to cpx dft

        using cpx_value_type = dft::defaut_cpx_value_type;

        size_t spectrum_size = dft_size_r2c(first, last);

        std::vector<cpx_value_type> spectrum(spectrum_size, {0.0,0.0});// @todo use pmr style allocation to avoid temporary allocation

        fft1d(first, last, spectrum.begin()); 

        OutputIte res_last = spp::norm(spectrum.cbegin(), spectrum.cend(), res);

        normalise(res, res_last, res);

        return res_last;
    }

}