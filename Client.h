#include <vector>
#include <string.h>
#include <iostream>
using namespace std;

class Client{
char* ip_address;
int port_number;

public:

Client(char* ip_address, int port_number);

int serverConnect();

void serialize(char* buffer, const vector<double>& vec, const string& metric, int& k);

bool input(int sock,vector<double>& vec,string& metric,int& k );

void printLabel(int sock);

void serverSend(int sock,vector<double>& vec,string& metric,int& k);



};
