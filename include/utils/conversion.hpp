#include <string>

namespace spp
{
    template<typename From, typename To>
    struct Convert;

    template<>
    struct Convert<std::string, double>
    {
        double operator()(const std::string& str)const
        {
            return std::stod(str);
        }
    };

}