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

void Command3::execute(){

    if (this->Xexamples.size()==0 || this->Yexamples.size()==0)
    {
        dio->write("please upload data");
        return;
    }

    for(int i=0; i<=this->XtoClassify.size(); i++){

        Knn knn=Knn(this->metric,this->k);

        knn.fit(this->Xexamples,this->Yexamples);

        string label=knn.predict(this->XtoClassify[i]);

        Yresults.push_back(label);
    }

    dio->write("classifying data complete");
    
}