
#include "Command2.h"
#include <sstream>
#include <string.h>
#include <cmath>


using namespace std;

Command2::Command2(DefaultIO* dio,int& k,string& metric)
: Command("algorithm settings", dio),
metric(metric), k(k)
{

}

void Command2::execute()
{
    this->dio->write("The current KNN parameters are: k= "+ to_string(this->k) + ", distance metric = "+ this->distance_metric);
    //user should enter k, space and then distance metric name.
    string parameters = this->dio->read();
    if (parameters==""){
        return;
    }
    
    else{
    stringstream s_stream(parameters);
    string sub_String1;   
    getline(s_stream, sub_String1, ' ');
    double k_value=stod(sub_String1);
    string metric;
    getline(s_stream, metric, ' ');
    if (ceil(k_value)==floor(k_value) && (metric == "AUC" || metric == "MAN" || metric == "CHB" || metric == "CAN" || metric == "MIN"))
    {
        this->k=k_value;
        this->metric=metric;
    }
    else
    {
        if(!(ceil(k_value)==floor(k_value))){
            this->dio->write("invalid value for K");
        }
        else{
            this->dio->write("invalid value for metric");
        }
    }
    }
}