#include <istream>
#include <string>
#include "utils/conversion.hpp"
namespace spp
{

template<typename TableType>
inline void parse_csv_header(std::istream& input, TableType& res_table)
{
    const static std::string sep = ",";

    std::string curr_line;

    std::getline(input, curr_line);

    size_t start = 0;

    size_t end = 0;

    while((end = curr_line.find(sep, start)) != std::string::npos)
    {
        res_table[curr_line.substr(start, end-start)];
        start = end+1;
    }

    res_table[curr_line.substr(start, end-start)];

}

template<typename TableType>
inline void parse_csv(std::istream& input, TableType& res_table)
{
    const static std::string sep = ",";

    parse_csv_header(input, res_table);

    std::string curr_line;

    std::getline(input, curr_line);

    using convertor_type = Convert<typename TableType::key_type, typename TableType::mapped_type::value_type>;

    while(!curr_line.empty())
    {
        size_t start = 0;

        for(auto& kv : res_table)
        {
            if(size_t end = curr_line.find(sep, start); end != std::string::npos)
            {
                kv.second.push_back(convertor_type{}(curr_line.substr(start, end-start)));
                start = end+1;
            }
            else
            {
                kv.second.push_back(convertor_type{}(curr_line.substr(start, end-start)));                
            }
        }
        std::getline(input, curr_line);
    }
}
}