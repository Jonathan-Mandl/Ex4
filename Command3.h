
#include "Command.h"
#include <vector>

class Command3 : public Command{
    int& k;
    std::string& metric;
    std::vector<std::vector<double>>& Xexamples;
    std::vector<std::string>& Yexamples;
    std::vector<std::vector<double>>& XtoClassify;
    std::vector<std::string>& Yresults;

    public:
    Command3(DefaultIO* dio, 
            std::vector<std::vector<double>>& Xexamples,
            std::vector<std::string>& Yexamples,
            std::vector<std::vector<double>>& XtoClassify, 
            std::vector<std::string>& Yresults,
            std::string& metric, int& k);
    void execute() override;
};