#include "Command3.h"
#include <vector>
#include <fstream>
#include <sstream>
#include "Input.h"
#include "Knn.h"

Command3::Command3()
{
    this->description="classify data";
}

void Command3::execute(){
    string train_file;
    string test_file;

    vector<vector<double>> features;
    vector<string> labels;
    
    Input input=Input();
    input.readVec(features,labels,train_file);

    vector<vector<double>> test_vectors;
    vector<string> test_labels;
    input.readTestVec(test_vectors, test_file);


    for(int i=0; i<=test_vectors.size(); i++){
        Knn knn=Knn("AUC",5);

        knn.fit(features,labels);

        string label=knn.predict(test_vectors[i]);

        test_labels.push_back(label);
    }
    
}