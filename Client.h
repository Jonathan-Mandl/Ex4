#include <vector>
#include <string.h>
#include <iostream>
using namespace std;

class Client{
char* ip_address;
int port_number;

public:

Client(char* ip_address,int port_number);

int serverConnect();

string receive(int sock);

void serverSend(int sock, string input);





};
