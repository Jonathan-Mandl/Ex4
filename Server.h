#include <string.h>
#include <iostream>
#include <vector>
using namespace std;

class Server{

 string file_name;
 int server_port;

public:

Server(string file_name, const int server_port);

void deserialize(const char* buffer, vector<double>& vec, string& metric, int& k);

int createSock();

int acceptClient(int sock);

void clientRequest(int client_sock);


};
