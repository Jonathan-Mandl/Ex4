#include <iostream>
#include<string>

#include <vector>
using namespace std;

#include "Command.h"

class Command1 : public Command{

    std::vector<std::vector<double>>& Xexamples;
    std::vector<std::string>& Yexamples;
    std::vector<std::vector<double>>& XtoClassify;


    public:
    void readExample(string line,std::vector<std::vector<double>>& Xexamples,
    std::vector<std::string>& Yexamples);
    void readTest(string line,std::vector<std::vector<double>>& XtoClassify);
    Command1(DefaultIO* dio, 
            std::vector<std::vector<double>>& Xexamples,
            std::vector<std::string>& Yexamples,
            std::vector<std::vector<double>>& XtoClassify);

    void execute() override;
};