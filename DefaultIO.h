
#include <string.h>
#include <iostream>


class DefaultIO{

public:

virtual std::string read() = 0;

virtual void write(std::string output) = 0;

};