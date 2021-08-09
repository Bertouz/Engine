#include <string>

namespace ngn
{
    template<typename From, typename To>
    struct Convert;

    /**
     * @brief The Convert struct
     * @ingroup Utils
     */
    template<>
    struct Convert<std::string, double>
    {
        double operator()(const std::string& str)const
        {
            return std::stod(str);
        }
    };

}
