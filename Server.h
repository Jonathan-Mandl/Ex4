#include <string.h>
#include <iostream>
#include <vector>
using namespace std;

class Server{

 string file_name;
 int server_port;

public:

Server(const int server_port);

int createSock();

int acceptClient(int sock);


};
