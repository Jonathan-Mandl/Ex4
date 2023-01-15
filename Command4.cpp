
#include "Command4.h"


Command4::Command4(DefaultIO* dio,std::vector<std::string>& Yresults)
: Command("display results",dio), Yresults(Yresults)
{
    
}

void Command4::execute()
{
    string output;

    for(int i=0;i<Yresults.size(); i++)
    {
        output += to_string(i) + "\t" + Yresults[i]+ "\n";
    }
    
    output += "Done.\n";

    dio->write(output);

}