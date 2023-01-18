
#include "Command4.h"
#include <iostream>
#include <unistd.h>

Command4::Command4(DefaultIO* dio,std::vector<std::string>& Yresults)
: Command("display results",dio), Yresults(Yresults)
{
    
}

void Command4::execute()
{
    dio->write("***display");
    dio->read();

    string output;

    for(int i=0;i<Yresults.size(); i++)
    {
        sleep(0.01);
        dio->write(to_string(i+1) + "\t" + Yresults[i]);
        dio->read();
    }
    
    dio->write("Done.");

}