#include <iostream>
#include<string>
using namespace std;

#include "DefaultIO.h"




class Command{
    protected:
    string description;
    DefaultIO* dio;

    public:
    virtual void execute() = 0;
    Command(string description, DefaultIO* dio);
};


