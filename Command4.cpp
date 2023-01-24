
#include "Command4.h"
#include <iostream>
#include <unistd.h>

Command4::Command4(DefaultIO *dio, std::vector<std::vector<double>> &Xexamples,
                   std::vector<std::string> &Yexamples, std::vector<std::vector<double>> &XtoClassify,
                   std::vector<std::string> &Yresults)
    : Command("display results", dio), Yresults(Yresults), Xexamples(Xexamples),
      Yexamples(Yexamples), XtoClassify(XtoClassify)
{
}
/*
this method sends labels of test file vectors to client with line number (tab separated).
it send each line separately. in case the files are not uploaded or classified it sends message to client.
*/
void Command4::execute()
{
    dio->write("***display");
    dio->read();

    if (Xexamples.size() == 0 || Yexamples.size() == 0 || XtoClassify.size() == 0)
    {
        dio->write("please upload data");
        dio->read();
    }
    else if (Yresults.size() == 0)
    {
        dio->write("please classify the data");
        dio->read();
    }
    else
    {

        dio->write("send");
        dio->read();
        //sends to client line of line number and label in test file separated by tabs
        for (int i = 0; i < Yresults.size(); i++)
        {
            sleep(0.01);
            dio->write(to_string(i + 1) + "\t" + Yresults[i]);
            dio->read();
        }

        dio->write("Done.\n");
    }
}