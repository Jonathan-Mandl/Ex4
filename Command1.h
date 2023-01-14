#include <iostream>
#include<string>

#include <vector>
using namespace std;

#include "Command.h"

class Command1 : public Command{
    string train_file;
    string test_file;
    string get_train();
    string get_test();

    std::vector<std::vector<double>>& Xexamples;
    std::vector<std::string>& Yexamples;
    std::vector<std::vector<double>>& XtoClassify;


    public:
    Command1(DefaultIO* dio, 
            std::vector<std::vector<double>>& Xexamples,
            std::vector<std::string>& Yexamples,
            std::vector<std::vector<double>>& XtoClassify);

    void execute() override;
};