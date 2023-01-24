
#include "Command2.h"
#include <sstream>
#include <string.h>
#include <cmath>
#include <iostream>
#include <unistd.h>

using namespace std;

Command2::Command2(DefaultIO *dio, int &k, string &metric,std::vector<std::vector<double>>& Xexamples)
    : Command("algorithm settings", dio),
      metric(metric), k(k), Xexamples(Xexamples)
{
}
/*
this method sends mesage with knn parameters to client. it then receives new knn parameters 
sent by the client and saves them in k and metric fields.
*/
void Command2::execute()
{
    dio->write("***algorithm");
    dio->read();
    dio->write("The current KNN parameters are: k= " + to_string(this->k) + ", distance metric = " + this->metric);
    // user should enter k, space and then distance metric name.
    string parameters = dio->read();

    if (parameters == "***end")
    {
        return;
    }
    else
    {
        stringstream s_stream(parameters);
        string sub_String1;
        getline(s_stream, sub_String1, ' ');
        double k_value;
        //makes sure k is a number. else send invalid value of k to client.
        try
        {
            k_value = stod(sub_String1);
        }
        catch (std::invalid_argument& e)
        {
            dio->write("***invalid");
            dio->read();
            dio->write("invalid value for K");
            dio->read();
            return;
        }

        string metric_value;
        getline(s_stream, metric_value, ' ');
        //makes sure k is integer and larger than 0 and smaller than number of vectors in train file.
        //also makes sure metric value is valid.
        if (ceil(k_value) == floor(k_value) && k_value > 0 && !(Xexamples.size()>0 && k_value>Xexamples.size()) &&
            (metric_value == "AUC" || metric_value == "MAN" || metric_value == "CHB" || metric_value == "CAN" || metric_value == "MIN"))
        {
            this->k = k_value;
            this->metric = metric_value;
            dio->write("***valid");
            dio->read();
            return;
        }
        else
        {
            //if k or metric aren't valid sends invalid value message to client.
            if (ceil(k_value) != floor(k_value) || k_value <= 0 || (Xexamples.size()>0 && k_value>Xexamples.size()))
            {
                dio->write("***invalid");
                dio->read();
                dio->write("invalid value for K");
                dio->read();
            }
            else
            {
                dio->write("***invalid");
                dio->read();
                dio->write("invalid value for metric");
                dio->read();
            }
        }
    }
}