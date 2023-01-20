
#include "Command.h"
#include <vector>

class Command4 : public Command{

    std::vector<std::string>& Yresults;
    std::vector<std::vector<double>>& Xexamples;
    std::vector<std::string>& Yexamples;
    std::vector<std::vector<double>>& XtoClassify;

    public:
    Command4(DefaultIO* dio,std::vector<std::vector<double>>& Xexamples,
    std::vector<std::string>& Yexamples,std::vector<std::vector<double>>& XtoClassify,
    std::vector<std::string>& Yresults);
    void execute() override;

};