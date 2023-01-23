#include <vector>
#include <string>
#include "Command.h"
#include "Command1.h"
#include "Command2.h"
#include "Command3.h"
#include "Command4.h"
#include "Command5.h"

class CLI{
    std::vector<std::vector<double>> Xexamples;
    std::vector<std::string> Yexamples;

    std::vector<std::vector<double>> XtoClassify;
    std::vector<std::string> Yresults;

    int k;
    int client_sock;
    std::string metric;

    DefaultIO* dio;

    Command* commands[5];

    public:

    void start();

    CLI(DefaultIO* dio,int client_sock);

    ~CLI();
};