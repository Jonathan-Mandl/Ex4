
#include "CLI.h"
#include <unistd.h>

CLI::CLI(DefaultIO* dio) : dio(dio) 
{
    this->k=5;
    this->metric="AUC";
    commands[0] = new Command1(dio, Xexamples, Yexamples, XtoClassify);
    commands[1]= new Command2(dio,k,metric,Xexamples);
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
        try{
        while (1) {
            string menu="Welcome to the KNN Classifier Server. Please choose an option:\n";
            for(int i=0; i<5; i++)
            {
                menu += to_string(i+1) +". " + commands[i]->getDescription() + "\n";
            }
            dio->write(menu);     
             // todo show menu
            string input = dio->read();

            int command;

            try
            {
            command=stoi(input);
            }
            catch(exception&)
            {
                dio->write("continue");
                dio->read();
                continue;
            }

            if(command==8)
            {   
                break;
            }

            if(command>=1 && command<=5)
            {
            commands[command-1]->execute();
            }
            else{
                dio->write("continue");
                dio->read();
            }

        }
        }
        catch(exception&)
        {
            
        }

}