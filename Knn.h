#include <vector>
#include <iostream>
#include<string>

using namespace std;

class Distance;

class Knn{

    vector<vector<double>> features;

    vector<string> labels;

    int k;
    
    string metric;

public:

    Knn(string metric,int k);

    void fit(vector<vector<double>> features, vector<string> labels);

    string predict(vector<double> input);


} ;
