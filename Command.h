#include <iostream>
#include<string>
using namespace std;

#include "StandardIO.h"

class StandardIO;

class Command{
    protected:
    string description;
    StandardIO dio;

    public:

    virtual void execute() = 0;

};


