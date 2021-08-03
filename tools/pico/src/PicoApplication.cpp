#include "PicoApplication.hpp"
#include <map>
#include <set>
#include <iostream>
#include "parser/csv_parser.hpp"
#include "spectral_analysis/spectral_analysis.hpp"
#if PLOT_DEBUG
#include "plot/plot.hpp"
#endif
#include "algorithms/generation.hpp"

const static std::map<std::string, std::string> format_ext_mapper{{"csv",".csv"}};

PicoApplication::PicoApplication(int argc, char** argv) : cli_app("pico is a little tool to compute the frequency of the highest amplitude wave in a waveform from file")
{
    this->cli_app.add_option("-f,--file", inputs, "File containing the data of the waveform we want to analyze, if its a directory then we look for all files matching the format at the first level");
    this->cli_app.add_option("-o, --out", report_file, "Output file, default : pico.results");
    this->cli_app.add_option("--input_format", input_file_format, "Format of waveform file, currently supported : [csv]");
    this->cli_app.add_option("--output_format", input_file_format, "Format of report file, currently supported : [csv]");

    this->cli_app.parse(argc, argv);                                                                                   

    if(this->inputs.empty())
    {
        throw std::runtime_error("You didn't provide any input file, for more informations refer to the help using -h or --help");
    }
    else if(!std::filesystem::exists(this->inputs))
    {
        throw std::runtime_error("The file \"" + this->inputs.string() + " doesn't exist, please provide a valide path");
    }
}

void PicoApplication::exec()const
{
    std::set<std::filesystem::path> input_waveforms;

    if(std::filesystem::is_directory(this->inputs))
    {
        const std::string correction_ext = format_ext_mapper.at(this->input_file_format);

        for(auto ite = std::filesystem::directory_iterator(this->inputs); ite != std::filesystem::directory_iterator(); ite++)
        {
            if(std::filesystem::path(*ite).extension() == correction_ext)
            {
                std::cout<<*ite<<std::endl;
                input_waveforms.insert(*ite);
            }
        }
    }
    else
    {
        input_waveforms.insert(this->inputs);
    }

    std::vector<std::pair<std::string, double>> results;

    results.reserve(input_waveforms.size());

    for(const auto& curr_waveform_path : input_waveforms)
    {
        std::ifstream ifs_curr(curr_waveform_path.string());

        std::map<std::string, std::vector<double>> curr_table;
        
        spp::parse_csv(ifs_curr, curr_table);

        if(curr_table.size() == 2) 
        {
            auto time = curr_table.at("Seconds");

            // Now time is in microsecs
            std::transform(time.begin(), time.end(), time.begin(), [](auto v){
                return v*1'000'000;
            });

            const auto signal_volts= curr_table.at("Volts");

            const double integration_time = *std::prev(time.end());

            const size_t nb_points = signal_volts.size();

            std::vector<double> periodogram(nb_points / 2 + 1);// The periodogram is real so the complex dft is symetric

            spp::periodogram(signal_volts.cbegin(), signal_volts.cend(), periodogram.begin());

            const auto max_element = std::max_element(periodogram.begin(), periodogram.end());

            const size_t id_max_element = std::distance(periodogram.begin(), max_element);

            const double periodogram_freq_res = 1'000'000 / integration_time;
            
            const double max_amp_freq = id_max_element * periodogram_freq_res;

#if PLOT_DEBUG
            if(max_amp_freq < 1e-06)
            {
                plt::Plot plot;
                plot.palette("set2");
                plot.drawCurve(time, signal_volts).label("y(t)").lineWidth(4);

                std::vector<double> f(periodogram.size());

                spp::linespace(f.begin(), f.end(), periodogram_freq_res);

                plt::Plot plot_spectre;
                plot_spectre.palette("set2");
                plot_spectre.drawCurve(f, periodogram).label("periodogram(y)").lineWidth(4);

                plt::Figure figure({{plot}, {plot_spectre}});
                figure.size(749, 749);
                figure.show();
            }
#endif

            results.push_back(std::make_pair(curr_waveform_path.filename().string(), max_amp_freq));
        }
        else
        {
            throw std::runtime_error("The CSC must contain only two columns");
        }
    }

    std::ofstream ofile(this->report_file.string());
    ofile<<"filename, highest_amplitude_frequency"<<std::endl;
    for(const auto& result : results)
    {
        ofile<<result.first<<","<<result.second<<std::endl;
    }
}
