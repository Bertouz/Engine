#pragma once
#include <istream>
#include <string>
#include "engine/utils/conversion.hpp"


// Definitions
namespace ngn
{

/**
 * @brief parse_csv_header - Parse the headers of a csv files into an associative container with the headers as keys
 * Our compatible csv files are one with the first line containing the header of every column, it is the line we add to the result table
 * @tparam TableType     - Is an associative container type
 * @param[in] input      - input stream from wich we take the first line as header
 * @param[out] res_table - output container in wich we create the keys from the input
 * @ingroup Parser
 */
template<typename TableType>
inline void parse_csv_header(std::istream& input, TableType& res_table);

/**
 * @brief parse_csv
 * @param input
 * @param res_table
 * @ingroup Parser
 */
template<typename TableType>
inline void parse_csv(std::istream& input, TableType& res_table);

}

// Declarations
namespace ngn
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
