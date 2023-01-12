
#include <string.h>
#include <iostream>
using namespace std;

class DefaultIO{

public:

virtual string read() = 0;

virtual void write(string output) = 0;

};