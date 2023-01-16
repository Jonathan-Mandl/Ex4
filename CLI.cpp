
#include "CLI.h"
#include "Command1.h"
#include "Command2.h"
#include "Command3.h"
#include "Command4.h"
#include "Command5.h"

CLI::CLI(DefaultIO* dio) : dio(dio) 
{
    commands[0] = new Command1(dio, Xexamples, Yexamples, XtoClassify);
    commands[1]= new Command2(dio,k,metric);
    commands[2]= new Command3(dio, Xexamples,Yexamples,XtoClassify,Yresults,metric,k);
    commands[3]= new Command4(dio,Yresults);
}

CLI::~CLI() 
{
    for (size_t i = 0; i < 4; i++)
    {
        delete commands[i];
    }
    
}

void CLI::start()
{

    try {
        while (1) {
            string menu="welcome to the KNN Classifier Server. Please choose an option:\n";
            for(int i=0; i<4; i++)
            {
                menu += to_string(i) +". " + commands[i]->getDescription() + "\n";
            }
            dio->write(menu);   
             // todo show menu
            string input = dio->read();

            dio->write(input);
            // todo make sure it's valid number in range...
            commands[stoi(input)]->execute();
        }
    }
    catch (exception&) {

    }
}