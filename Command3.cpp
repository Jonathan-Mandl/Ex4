#include "Command3.h"
#include <vector>
#include <fstream>
#include <sstream>
#include "Input.h"
#include "Knn.h"

Command3::Command3(DefaultIO* dio, 
            std::vector<std::vector<double>>& Xexamples,
            std::vector<std::string>& Yexamples,
            std::vector<std::vector<double>>& XtoClassify,
            std::vector<std::string>& Yresults,
            std::string& metric, int& k)
            : Command("classify data", dio),
            Xexamples(Xexamples), Yexamples(Yexamples), XtoClassify(XtoClassify),Yresults(Yresults),
            metric(metric), k(k)
{
    
}
/*
this method classifies vectors by calling knn predict fuction in knn class
*/
void Command3::execute(){

    dio->write("***classify");
    dio->read();
    //make sure data is uploaded.
    if (this->Xexamples.size()==0 || this->Yexamples.size()==0 || XtoClassify.size()==0)
    {
        dio->write("please upload data");
        dio->read();
        return;
    }
    //if k is greater than total number of examples send message to client.
    if(this->k>this->Xexamples.size())
    {
        dio->write("invalid input for k: k is larger than the number of examples");
        dio->read();
        return;
    }
    //initialize knn object.
    Knn knn(this->metric,this->k);

    knn.fit(this->Xexamples,this->Yexamples);
    //makes sure Yresults vector of labels is empty before classification.
    if(Yresults.size()>0)
    {
        Yresults.clear();
    }
    //calls knn predict function for every vector in test file (XToClassify vector) to return predicted label.
    //saves label in Yresults vector
    for(int i=0; i<this->XtoClassify.size(); i++){

        string label=knn.predict(this->XtoClassify[i]);

        Yresults.push_back(label);
    }

    dio->write("classifying data complete");
    dio->read();
    
}