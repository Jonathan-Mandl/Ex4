#include <iostream>
#include<string>
using namespace std;

#include "Command.h"

class Command1 : public Command{
    string train_file;
    string test_file;
    public:
    Command1();
    void execute() override;
    string get_train();
    string get_test();
};