
#include "Command.h"
#include <vector>

class Command4 : public Command{

    std::vector<std::string>& Yresults;

    public:
    Command4(DefaultIO* dio,std::vector<std::string>& Yresults);
    void execute() override;

};