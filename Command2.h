
#include <iostream>
#include<string>
using namespace std;

#include "Command.h"



class Command2 : public Command{
    int& k;
    string& metric;
    public:
    Command2(DefaultIO* dio,int& k,string& metric);
    void execute() override;
};