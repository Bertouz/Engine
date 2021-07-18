#include "lib2/hello.hpp"

namespace my_cpp_project
{
void greet(std::ostream &pOs)
{
    pOs << "hello world";
}

void PolitePerson::hello()
{
    greet(std::cout);
}
} // namespace my_cpp_project
