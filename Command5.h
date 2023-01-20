

#include "Command.h"
#include <vector>

class Command5 : public Command{
    std::vector<std::string>& Yresults;
    std::vector<std::vector<double>>& Xexamples;
    std::vector<std::string>& Yexamples;
    std::vector<std::vector<double>>& XtoClassify;

    public:
    Command5(DefaultIO* dio,std::vector<std::vector<double>>& Xexamples,
    std::vector<std::string>& Yexamples,std::vector<std::vector<double>>& XtoClassify,
    std::vector<std::string>& Yresults);
    void execute() override;
    
};


