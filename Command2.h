
#include <iostream>
#include<string>
using namespace std;

#include "Command.h"



class Command2 : public Command{
    int k;
    string distance_metric;
    public:
    Command2();
    void execute() override;
};