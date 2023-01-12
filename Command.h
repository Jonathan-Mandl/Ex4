#include <iostream>
#include<string>
using namespace std;

#include "DefaultIO.h"
#include "StandardIO.h"



class Command{
    protected:
    string description;
    StandardIO dio;

    public:
    virtual void execute() = 0;

};


