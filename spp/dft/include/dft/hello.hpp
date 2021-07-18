#ifndef HELLO_HPP
#define HELLO_HPP
#include <iostream>

namespace my_cpp_project
{
class IPolite
{
  public:
    virtual void hello() = 0;
};

class PolitePerson : public IPolite
{
  public:
    enum Sex
    {
        MALE,
        FEMELLE
    } sex;

    void hello() override;
};

/**
 * @brief greet - Function that append to a given stream the message "hello world"
 * @param pOs - stream in which we want to greet
 */
void greet(std::ostream &pOs);

} // namespace my_cpp_project

#endif // HELLO_HPP
