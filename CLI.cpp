
#include "CLI.h"
#include <unistd.h>

CLI::CLI(DefaultIO* dio) : dio(dio) 
{
    this->k=5;
    this->metric="AUC";
    commands[0] = new Command1(dio, Xexamples, Yexamples, XtoClassify);
    commands[1]= new Command2(dio,k,metric);
    commands[2]= new Command3(dio, Xexamples,Yexamples,XtoClassify,Yresults,metric,k);
    commands[3]= new Command4(dio,Xexamples,Yexamples,XtoClassify,Yresults);
    commands[4]= new Command5(dio,Xexamples,Yexamples,XtoClassify,Yresults);
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

        while (1) {
            string menu="Welcome to the KNN Classifier Server. Please choose an option:\n";
            for(int i=0; i<5; i++)
            {
                menu += to_string(i+1) +". " + commands[i]->getDescription() + "\n";
            }
            dio->write(menu);     
             // todo show menu
            string input = dio->read();

            if(stoi(input)==8)
            {
                break;
            }
            // todo make sure it's valid number in range...
            commands[stoi(input)-1]->execute();
            sleep(0.1);
        }
}