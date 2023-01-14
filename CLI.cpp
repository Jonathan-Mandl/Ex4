
#include "CLI.h"
#include "Command1.h"

CLI::CLI(DefaultIO* dio) : dio(dio) 
{
    commands[0] = new Command1(dio, Xexamples, Yexamples, XtoClassify);
    //.. todo 4 more
}

CLI::~CLI() 
{
    for (size_t i = 0; i < 5; i++)
    {
        delete commands[i];
    }
    
}

void CLI::start()
{

    try {
        while (1) {
            dio->write("welcome to the knn...");
            // todo show menu
            string input = dio->read();
            // todo make sure it's valid number in range...
            commands[stoi(input)]->execute();
        }
    }
    catch (exception&) {

    }
}