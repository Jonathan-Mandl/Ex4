
#include "Command1.h"

#include <fstream>

Command1::Command1(DefaultIO* dio, 
            std::vector<std::vector<double>>& Xexamples,
            std::vector<std::string>& Yexamples,
            std::vector<std::vector<double>>& XtoClassify)
            : Command("upload an unclassified csv data file", dio),
            Xexamples(Xexamples), Yexamples(Yexamples), XtoClassify(XtoClassify)
{
  
}

void Command1::execute()
{
    
    this->dio->write("Please upload your local train CSV file.");
    string file=this->dio->read();

    this->dio->write("Upload complete.");
    


    this->dio->write("Please upload your local test CSV file.");
    string file=this->dio->read();

    
    this->dio->write("Upload complete.");

}

