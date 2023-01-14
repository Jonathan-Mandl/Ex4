#include <vector>
#include <iostream>
#include <iostream>
using namespace std;

class Input{
public:

void readVec(vector<vector<double>>& vectors, vector<string>& labels, const string file_name);

vector<double> inputVec(int size);

void readTestVec(vector<vector<double>>& vectors, string file_name);


};