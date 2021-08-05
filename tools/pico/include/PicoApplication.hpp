#include <filesystem>
#include <string>
#include <CLI/CLI.hpp>
#include <optional>

class PicoApplication
{
public:
    PicoApplication(int argc, char** argv);

    void exec()const;

    std::filesystem::path inputs;
    std::filesystem::path report_file = "pico.results";
    std::string input_file_format = "csv";
    std::string output_file_format = "csv";

private:
    CLI::App cli_app;
};
