#include <vector>
#include <iostream>
#include<string>
#include <algorithm>
#include <map>
using namespace std;

#include "Knn.h"
#include "Distance.h"


//constructor for Knn class
Knn::Knn(string metric, int k)
{
    this->k = k;
    this->metric = metric;
}
/* the fit method recieves vectors of features and labels and stores them
in the specific features and vectors fields in knn class*/
void Knn::fit(vector<vector<double>> features, vector<string> labels)
{
    this->features = features;
    this->labels = labels;
}
/*The predict method implements knn algorithm. It recieves input vector
and return predicted label of the input vector based on its k closet neighbors */
string Knn::predict(vector<double> input)
{
    // creates vector pairs for distances and labels
    vector<pair<double, string>> distances;
// for every features calculates distance based of distance metric.
    for (int i = 0; i < features.size(); i++)
    {
        double distance = 0;
        Distance dis;
        if (this->metric == "AUC") { distance = dis.euclidian(this->features[i], input); };
        if (this->metric == "MAN") { distance = dis.manhatten(this->features[i], input); };
        if (this->metric == "CHB") { distance = dis.chevichav(this->features[i], input); };
        if (this->metric == "CAN") { distance = dis.canabra(this->features[i], input); };
        if (this->metric == "MIN") { distance = dis.minkovsky(this->features[i], input); };
        // insert ditance and specific label into vector of ditance, label pairs
        distances.push_back(make_pair(distance, labels[i]));
    }
    //sorts distances in ascending order
    sort(distances.begin(), distances.end());
    //creates map of counts for each label
    map<string, int> labelVotes;

    for (int i = 0; i < this->k; i++)
    {
        string label = distances[i].second;
        //if label is not in labelVotes map create new entry for label in the map and enter count as 1.
        if (labelVotes.find(label) == labelVotes.end())
        {
            labelVotes[label] = 1;
        }
        else
        {
            // add one to count of specific label
            labelVotes[label] += 1;
        }

    }

    string prediction;
    int max_votes = 0;
    // find label with heighest amount of votes
    for (auto it = labelVotes.begin(); it != labelVotes.end(); it++) {
        if (it->second > max_votes) {
            max_votes = it->second;
            prediction = it->first;
        }
    }

    return prediction;


}
