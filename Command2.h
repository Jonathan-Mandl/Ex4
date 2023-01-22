
#include <iostream>
#include<string>
using namespace std;
#include <vector>

#include "Command.h"



class Command2 : public Command{
    int& k;
    string& metric;
    std::vector<std::vector<double>>& Xexamples;

    public:
    Command2(DefaultIO* dio,int& k,string& metric,std::vector<std::vector<double>>& Xexamples);
    void execute() override;
};