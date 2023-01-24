#pragma once
#include <string.h>
#include <iostream>

/*
this is an abstract class for reading and writing data. it has read() function which reads
data and write() function that write data. both methods do not have implementation yet.
*/
class DefaultIO{

public:

virtual std::string read() = 0;

virtual void write(std::string output) = 0;

};