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
The serialize function get as input char* buffer, the user inputs, and write them to the buffer.
Befor the active of the serialize() function we initialize the buffer and passed it by refference to the fuction,
so we just update the buffer but not return it.
*/

void Client::serialize(char* buffer, const vector<double>& vec, const string& metric, int& k) {
  char* ptr = buffer;

  // Write the size of the vector
  int vec_size = vec.size();
  memcpy(ptr, &vec_size, sizeof(int));
  ptr += sizeof(int);

  // Write the vector data
  memcpy(ptr, vec.data(), vec_size * sizeof(double));
  ptr += vec_size * sizeof(double);

  // Write the distance metric name
  int metric_size = metric.size();
  memcpy(ptr, &metric_size, sizeof(int));
  ptr += sizeof(int);
  memcpy(ptr, metric.data(), metric_size);
  ptr += metric_size;

  // Write the int k
  memcpy(ptr, &k, sizeof(int));
}

/*
The input function get the socket number, and the user inputs and enter them to varibles and cheak if the parameters that given are valid.
the function return 0 if there are valid input, else return 1.
*/

bool Client::input(int sock,vector<double>& vec,string& metric,int& k ){

string rawInput;
getline(cin, rawInput);
if (rawInput=="-1")
{
    close(sock);
    exit(1);
}

    stringstream s_stream(rawInput);
    string sub_String;
    // loop that that runs until all stream of input is processed.
    while (s_stream.good())
    {
        // gets all characters until next space and stores in substring string
        getline(s_stream, sub_String, ' ');
        double num = 0;
        try
        {
            // converts substring to double and stores in double num.
            num = stod(sub_String);
        }
        catch (exception& e)
        {
            break;
        }
        // append num to vector
        vec.push_back(num);
    }

    metric=sub_String;
    if (!(metric == "AUC" || metric == "MAN" || metric == "CHB" || metric == "CAN" || metric == "MIN"))
    {
        cout<< "Invalid Input"<<endl;
        return 0;
    }

     getline(s_stream, sub_String, ' ');
     try
        {
            // converts substring to double and stores in double num.
            k= stoi(sub_String);
        }
        catch (exception& e)
        {
            cout<< "Invalid Input"<<endl;
            return 0;
        }
if (s_stream.peek() != EOF) {
    cout<< "Invalid Input"<<endl;
    return 0;
}
return 1;

}

/*
The serverSend function get as inputs: the socket number, double vector, string metric functiomn, and int k.
In the funcion we creat buffer to insert it the user inputs. we use for that in serialize function.
after that the function send the buffer to server by the socket number.
*/

void Client::serverSend(int sock,vector<double>& vec,string& metric,int& k)
{
char buffer[4096];

this->serialize(buffer,vec,metric,k);
  
int buffer_size= sizeof(buffer);
int sent_bytes= send(sock, buffer, buffer_size,0);
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

void Client::printLabel(int sock)
{
string label;
char* buf = &label[0];
int read_bytes = recv(sock, buf, 30, 0);
label[read_bytes]='\0';

if (read_bytes ==0)
{
perror("connection closed"); 
exit(1);
}
else if (read_bytes<0)
{
    perror("no information recieved from server");
    exit(1);
}
else{

if (buf=="Invalid Input")
{
    cout<<"Invalid Input"<<endl;
}
else{
cout<<buf<<endl;
}
}
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
vector<double> vec;
string metric;
int k;


if (client.input(sock,vec,metric,k))
{
client.serverSend(sock,vec,metric,k);
client.printLabel(sock);
}

}
}
