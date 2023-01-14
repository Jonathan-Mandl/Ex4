
#include "Command1.h"
#include "StandardIO.h"
#include <fstream>

Command1::Command1(DefaultIO* dio, 
            std::vector<std::vector<double>>& Xexamples,
            std::vector<std::string>& Yexamples,
            std::vector<std::vector<double>>& XtoClassify) 
            : Command("upload an unclassified csv data file", dio),
            Xexamples(Xexamples), Yexamples(Yexamples), XtoClassify(XtoClassify)
{
    this->test_file="";
    this->train_file="";
}

void Command1::execute()
{
    
    this->dio.write("Please upload your local train CSV file.");
    string file=this->dio.read();

    fstream fin;
    //tries to open csv file with specific path as file_name
    fin.open(file, ios::in);
    // returns error if file cannot be opened
    if (fin.fail())
    {
        this->dio.write("invalid input");
        return;
    }
    else
    {
        this->dio.write("Upload complete.");
        this->train_file=file;
    }

    this->dio.write("Please upload your local test CSV file.");
    string file=this->dio.read();

    fstream fin;
    //tries to open csv file with specific path as file_name
    fin.open(file, ios::in);
    // returns error if file cannot be opened
    if (fin.fail())
    {
        this->dio.write("invalid input");
        return;
    }
    else
    {
        this->test_file=file;
        this->dio.write("Upload complete.");
    }

}

string Command1::get_train(){
    return this->train_file;
}
string Command1::get_test(){
    return this->test_file;
}
