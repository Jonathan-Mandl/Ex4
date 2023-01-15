#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "Client.h"

/*
The Client class initialized by char* ip_address, int port_number.
the cleint use the port number and ip address to connect the server and send him the buffer.
*/

Client::Client(char* ip_address, int port_number)
{
    this->ip_address=ip_address;
    this->port_number=port_number;
}

/*
The serverConnect() function creat socket to connect the sever, and return the sock number.
*/

int Client::serverConnect()
{
int sock= socket(AF_INET, SOCK_STREAM,0);
if (sock<0){
    perror("error creating socket");
    exit(1);
}
struct sockaddr_in sin;
memset(&sin, 0, sizeof(sin));
sin.sin_family = AF_INET;
sin.sin_addr.s_addr = inet_addr(this->ip_address);;
sin.sin_port = htons(this->port_number);
if (connect(sock,(struct sockaddr*)&sin, sizeof(sin))<0){
    perror("error connecting to server");
    exit(1);
}

return sock;
}


/*
The serverSend function get as inputs: the socket number, double vector, string metric functiomn, and int k.
In the funcion we creat buffer to insert it the user inputs. we use for that in serialize function.
after that the function send the buffer to server by the socket number.
*/

void Client::serverSend(int sock,string input)
{
int sent_bytes= send(sock, input.c_str(), input.size(),0);
if (sent_bytes<0)
{
perror("error sending information to server.");
exit(1);
}

}

/*
The printLabel function get as input the socket number and use it to recive from the server the lable from the knn compute.
after the function connect to the server and recive the lable we print it.
*/

string Client::receive(int sock)
{
string output;
char buffer[4096];
int expected_data_len= sizeof(buffer);
int read_bytes = recv(sock, buffer, expected_data_len, 0);
return output;
}



/*
The main function get as inputs: int argc, char* argv[], while int argc is the number of parameters in argv[],
and char* argv[] is the array with the parameters of ip_address and port_number. 
the parameter in argv[] is:
argv[1] - is the ip_address.
argv[2] - is the port_number. 
with the port number and ip address the client connect to the server and send to server the buffer with the user input.
*/


int main(int argc, char* argv[])
{
char* ip_address= argv[1];
int port_number=stoi(argv[2]);

struct in_addr addr;
  // Convert the IP address
  int result = inet_pton(AF_INET, ip_address, &addr);
  // check if ip adress can be converted. if not, return error
  if (!result) {
    cout << "Error: invalid IP address" << std::endl;
    exit(1);
  }

  if (!(port_number>=1024 && port_number<=65535))
  {
    cout << "Error: invalid port_number" << std::endl;
    exit(1);

  }



Client client=Client(ip_address,port_number);

int sock=client.serverConnect();


while(true)
{


}
}
