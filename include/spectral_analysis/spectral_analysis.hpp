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

        return std::transform(first, last, res, [normalisation_factor](auto const& value){
            return value / normalisation_factor;
        });
    }

    template<std::input_iterator InputIte, typename OutputIte>
    requires std::input_or_output_iterator<OutputIte> && RealIterator<OutputIte>
    inline auto periodogram(InputIte first, InputIte last, OutputIte res)->OutputIte
    {
        // using temporary complex spectrum so we use {real/cpx} to cpx dft

        using cpx_value_type = dft::defaut_cpx_value_type;

        auto spectrum_size = dft_size_r2c(first, last);

        std::vector<cpx_value_type> spectrum(std::move(spectrum_size));// @todo use pmr style allocation 

        fft1d(first, last, spectrum.begin()); 

        auto res_last = norm(spectrum.begin(), spectrum.end(), res);

        normalise(res, res_last, res);

        return res_last;
    }

}