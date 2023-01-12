
#include "Command1.h"
#include <fstream>

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
    }



}
