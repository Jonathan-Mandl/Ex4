
#include "Command5.h"
#include <iostream>
#include <unistd.h>


Command5::Command5(DefaultIO *dio, std::vector<std::vector<double>> &Xexamples,
                   std::vector<std::string> &Yexamples, std::vector<std::vector<double>> &XtoClassify,
                   std::vector<std::string> &Yresults)
    : Command("download results", dio), Yresults(Yresults), Xexamples(Xexamples),
      Yexamples(Yexamples), XtoClassify(XtoClassify)
{
}

void Command5::execute()
{
    dio->write("***download");
    dio->read();

    if (Xexamples.size() == 0 || Yexamples.size() == 0 || XtoClassify.size() == 0)
    {
        dio->write("please upload data");
    }
    else if (Yresults.size() == 0)
    {
        dio->write("please classify the data");
    }
    else
    {

        dio->write("send");
        dio->read();

        string output;

        for (int i = 0; i < Yresults.size(); i++)
        {
            sleep(0.01);
            dio->write(to_string(i + 1) + "\t" + Yresults[i]);
            dio->read();
        }

        dio->write("Done.");
    }

}