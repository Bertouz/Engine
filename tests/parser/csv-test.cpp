#include "engine/parser/csv_parser.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

std::unique_ptr<std::istream> make_inputs()
{
    return std::make_unique<std::istringstream>("Seconds,Volts\n"
                                                "0, -0.02503107\n"
                                                "7.619228E-09, -0.00430085\n"
                                                "1.523846E-08, 0.01638979\n"
                                                "2.285768E-08, 0.02664651\n"
                                                "3.047691E-08, 0.02684325\n"
                                                "3.809614E-08, 0.0269058\n"
                                                "4.571537E-08, 0.02681732\n"
                                                "5.33346E-08, 0.02657055\n"
                                                "6.095382E-08, 0.02616828\n"
                                                "6.857305E-08, 0.0256231\n"
                                                "7.619228E-08, 0.02495668\n"
                                                "8.381151E-08, 0.02419838\n"
                                                "9.143073E-08, 0.02338336\n"
                                                "9.904996E-08, 0.02255038\n");
}

SCENARIO("We want to parse a csv file ", "[parser][csv]")
{
    GIVEN("an input stream with csv formatted data")
    {

        auto inputs = make_inputs();

        std::map<std::string, std::vector<double>> table;

        WHEN("using parse_csv(*inputs, table);")
        {
            ngn::parse_csv(*inputs, table);

            THEN("We extract correctly the data")
            {
                std::vector<double> ref_secondes{
                    0,           7.619228E-09, 1.523846E-08, 2.285768E-08, 3.047691E-08, 3.809614E-08, 4.571537E-08,
                    5.33346E-08, 6.095382E-08, 6.857305E-08, 7.619228E-08, 8.381151E-08, 9.143073E-08, 9.904996E-08,
                };

                std::vector<double> ref_volts{-0.02503107, -0.00430085, 0.01638979, 0.02664651, 0.02684325,
                                              0.0269058,   0.02681732,  0.02657055, 0.02616828, 0.0256231,
                                              0.02495668,  0.02419838,  0.02338336, 0.02255038};

                CHECK_THAT(table["Seconds"], Catch::Matchers::Approx(ref_secondes));
                CHECK_THAT(table["Volts"], Catch::Matchers::Approx(ref_volts));
            }
        }
    }
}
