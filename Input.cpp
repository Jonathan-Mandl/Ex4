#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <stdexcept> 
using namespace std;
#include "Input.h"
/*
this function reads feature vectors and labels from csv file.
it accepts file name and empty features and labels vectors as arguments.
*/
void Input::readVec(vector<vector<double>>& vectors, vector<string>& labels, const string file_name)
{
    fstream fin;
    //open csv file with specific path as file_name
    fin.open(file_name, ios::in);
    // returns error if file cannot be opened
    if (fin.fail())
    {
        throw invalid_argument("File does not exist");
    }

    string line;
    //reads every line of csv file
    while (getline(fin, line)) {
        stringstream lineStream(line);
    // create vector for specific features in the line
        vector<double> vector;
        //create string for labels
        string label;

        string value;
        //reads every character until next space
        while (getline(lineStream, value, ',')) {
            if (lineStream.eof()) {
                // This is the label value (since we are at the end of the line)
                label = value;
                labels.push_back(label);
            }
            else {
                // These are the vector values
                vector.push_back(stod(value));
            }
        }
        //adds the vector we just created into vector of vectors that contains features
        vectors.push_back(vector);
        
    }
    
}
/*
this function accepts vector from user.
recieves argument of vector size.
returns vector entered by user.
*/
vector<double> Input::inputVec(int size)
{

    vector<double> vec1;
    string rawInput;
    // recieve a line of input from user
    getline(cin, rawInput);
    
   
    stringstream s_stream(rawInput);
    // loop that that runs until all stream of input is processed.
    while (s_stream.good())
    {
        string sub_String;
        // gets all characters until next space and stores in substring string
        getline(s_stream, sub_String, ' ');
        double num = 0;
        try
        {
            // converts substring to double and stores in double num.
            num = stod(sub_String.c_str());
        }
        catch (exception& e)
        {
            // if substring is not a double, an exception is thrown and returns error.
            throw invalid_argument("Error: Invalid input vectors!");
        }
        // append num to vector
        vec1.push_back(num);
    }
 if (vec1.size()!=size)
 {
    //returns error if the size of vector user entered is not equal to the desired size.
    throw invalid_argument("Error: Invalid input vectors!");
 }
return vec1;
}

void Input::readTestVec(vector<vector<double>>& vectors, string test_file)
{
     fstream fin;
    //open csv file with specific path as file_name
    fin.open(test_file, ios::in);
    string line;

    // Read the CSV file line by line
    while (getline(fin, line)) {
        // Create a vector to store the values in the current line
        vector<double> values;

        // Use a stringstream to extract the values from the line
        stringstream ss(line);
        string value;
        while (getline(ss, value, ',')) {
            // Convert the value to a double and add it to the values vector
            values.push_back(stod(value));
        }

        // Add the values vector to the vectors vector
        vectors.push_back(values);
    }

}