#include "StandardIO.h"

string StandardIO::read(){
    string input;
    getline(cin, input);
    return input;
}

void StandardIO::write(string output)
{
    cout<<output<<endl;
}
