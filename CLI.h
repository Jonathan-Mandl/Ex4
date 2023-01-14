#include <vector>
#include <string>
#include "DefaultIO.h"
#include "Command.h"

class CLI{
    std::vector<std::vector<double>> Xexamples;
    std::vector<std::string> Yexamples;

    std::vector<std::vector<double>> XtoClassify;
    std::vector<std::string> Yresults;

    int k;
    std::string metric;

    DefaultIO* dio;

    Command* commands[5];

    public:

    void start();

    CLI(DefaultIO* dio);

    ~CLI();
};