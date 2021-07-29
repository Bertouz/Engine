#include "PicoApplication.hpp"


auto main(int argc, char** argv)->int
{
    try 
    {
        auto pico_app = PicoApplication(argc, argv);

        pico_app.exec();
    }
    catch(std::runtime_error & e)
    {
        std::cerr<<"Pico processing failed : "<<std::endl;
        std::cerr<<e.what()<<std::endl;
    }

    return 1;

}