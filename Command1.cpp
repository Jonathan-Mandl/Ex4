
#include "Command1.h"
#include <vector>
#include <sstream>
#include <unistd.h>
#include <fstream>
#include <iostream>

Command1::Command1(DefaultIO* dio, 
            std::vector<std::vector<double>>& Xexamples,
            std::vector<std::string>& Yexamples,
            std::vector<std::vector<double>>& XtoClassify)
            : Command("upload an unclassified csv data file", dio),
            Xexamples(Xexamples), Yexamples(Yexamples), XtoClassify(XtoClassify)
{
  
}

void Command1::readExample(string line, std::vector<std::vector<double>>& Xexamples,
    std::vector<std::string>& Yexamples)
    {
        stringstream lineStream(line);
    // create vector for specific features in the line
        std::vector<double> vector;
        //create string for labels
        string label;

        string value;
        //reads every character until next space
        while (getline(lineStream, value, ',')) {
            if (lineStream.eof()) {
                // This is the label value (since we are at the end of the line)
                label = value;
                Yexamples.push_back(label);
            }
            else {
                // These are the vector values
                vector.push_back(stod(value));
            }
        }
        //adds the vector we just created into vector of vectors that contains features
        Xexamples.push_back(vector);
    }


    void Command1::readTest(string line,std::vector<std::vector<double>>& XtoClassify)
    {
        stringstream lineStream(line);
    // create vector for specific features in the line
        std::vector<double> vector;
        //create string for labels
        string value;
        //reads every character until next space
        while (getline(lineStream, value, ',')) {
            vector.push_back(stod(value));
        }
        //adds the vector we just created into vector of vectors that contains features
        XtoClassify.push_back(vector);

    }



void Command1::execute()
{
    dio->write("***upload_file");
    sleep(1);
    dio->write("Please upload your local train CSV file.");
    string valid=dio->read();
    sleep(0.05);
    if (valid=="***invalid_file")
    {
        dio->write("invalid input");
        return;
    }
    else{
        while(true)
        {
            sleep(0.01);
            string line=dio->read();
            if (line=="***done")
            {
                break;
            }
            this->readExample(line,this->Xexamples,this->Yexamples);
            dio->write("read");
        }   
    }
    dio->write("Upload complete.");
    dio->write("Please upload your local test CSV file.");
    valid=dio->read();
    if (valid=="***invalid_file")
    {
        Xexamples.clear();
        Yexamples.clear();
        sleep(0.01);
        dio->write("invalid input");
    }
    else{
        while(true)
        {
            sleep(0.01);
            string line=dio->read();
            if (line=="***done")
            {
                break;
            }
            this->readTest(line,XtoClassify);
            dio->write("read");
        } 
        dio->write("Upload complete.");  
    }   
    
}

