
#include "Command1.h"
#include <vector>
#include <sstream>
#include <unistd.h>
#include <fstream>
#include <iostream>

Command1::Command1(DefaultIO *dio,
                   std::vector<std::vector<double>> &Xexamples,
                   std::vector<std::string> &Yexamples,
                   std::vector<std::vector<double>> &XtoClassify)
    : Command("upload an unclassified csv data file", dio),
      Xexamples(Xexamples), Yexamples(Yexamples), XtoClassify(XtoClassify)
{
}

bool Command1::readExample(string line, std::vector<std::vector<double>> &Xexamples,
                           std::vector<std::string> &Yexamples)
{
    stringstream lineStream(line);
    // create vector for specific features in the line
    std::vector<double> vector;
    // create string for labels
    string label;
    bool isOk = true;
    string value;
    // reads every character until next space
    while (getline(lineStream, value, ','))
    {
        if (lineStream.eof())
        {
            // This is the label value (since we are at the end of the line)
            label = value;
            Yexamples.push_back(label);
        }
        else
        {
            try
            {
                stod(value);
            }
            catch (std::exception &)
            {
                isOk = false;
                continue;
            }
            // These are the vector values
            vector.push_back(stod(value));
        }
    }
    // adds the vector we just created into vector of vectors that contains features
    Xexamples.push_back(vector);

    return isOk;
}

bool Command1::readTest(string line, std::vector<std::vector<double>> &XtoClassify)
{
    stringstream lineStream(line);
    // create vector for specific features in the line
    std::vector<double> vector;
    // create string for labels
    string value;
    bool isOk = true;
    // reads every character until next space
    while (getline(lineStream, value, ','))
    {
        try
        {
            stod(value);
        }
        catch (std::exception &)
        {
            isOk = false;
            continue;
        }

        vector.push_back(stod(value));
    }
    // adds the vector we just created into vector of vectors that contains features
    XtoClassify.push_back(vector);

    return isOk;
}
/*
this method asks client to upload train file and test file.
checks for file validity by making sure all vector are number and
are in the same length.
*/
void Command1::execute()
{
    Xexamples.clear();
    Yexamples.clear();
    XtoClassify.clear();
    
    dio->write("***upload_file");
    dio->read();
    dio->write("Please upload your local train CSV file.");
    string valid = dio->read();

    if (valid == "***invalid_file")
    {
        dio->write("invalid input");
        dio->read();
        return;
    }
    bool allLinesAreGood = true;
    while (true)
    {
        sleep(0.01);
        string line = dio->read();
        if (line == "***done")
        {
            break;
        }
        bool lineIsGood = this->readExample(line, this->Xexamples, this->Yexamples);
        if (!lineIsGood)
        {
            allLinesAreGood = false;
        }
        dio->write("read");
    }
    //checks vectors are valid.
    if (Xexamples.size() == 0)
        allLinesAreGood = false;
    if (allLinesAreGood)
    {
        for (const std::vector<double> &vec : Xexamples)
        {
            if (vec.size() != Xexamples[0].size())
            {
                allLinesAreGood = false;
                break;
            }
        }
    }

    if (!allLinesAreGood)
    {
        dio->write("***invalid file");
        dio->read();
        Xexamples.clear();
        Yexamples.clear();
        return;
    }

    dio->write("Upload complete.\n"
               "Please upload your local test CSV file.");
    valid = dio->read();

    if (valid == "***invalid_file")
    {
        Xexamples.clear();
        Yexamples.clear();
        dio->write("invalid input");
        dio->read();
        return;
    }

    allLinesAreGood = true;

    while (true)
    {
        sleep(0.01);
        string line = dio->read();
        if (line == "***done")
        {
            break;
        }
        bool lineIsGood = this->readTest(line, XtoClassify);

        if (!lineIsGood)
        {
            allLinesAreGood = false;
        }

        dio->write("read");
    }
    if (XtoClassify.size() == 0)
        allLinesAreGood = false;

    if (allLinesAreGood)
    {
        for (const std::vector<double> &vec : XtoClassify)
        {
            if (vec.size() != Xexamples[0].size())
            {
                allLinesAreGood = false;
                break;
            }
        }
    }

    if (!allLinesAreGood)
    {
        dio->write("***invalid file");
        dio->read();
        Xexamples.clear();
        Yexamples.clear();
        XtoClassify.clear();
        return;
    }

    dio->write("Upload complete.");
    dio->read();
}
