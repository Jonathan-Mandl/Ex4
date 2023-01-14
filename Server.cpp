#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <cmath>
#include <thread>

#include "Input.h"
#include "Knn.h"
#include "Server.h"

#include "DefaultIO.h"
#include  "SocketIO.h"
#include "CLI.h"

using namespace std;

// this is called from a new thread, so it's run in parallel
void handleClient(int client_sock) {
    SocketIO sio(client_sock);
    CLI cli(&sio);
    cli.start();
}

/*
The Server class initialized by string file name, const int server port. 
The file_name is the csv file with the labaled vector that the knn model train on them,
and the server_port is the port number of the server.
*/

Server::Server(string file_name, const int server_port)
{
    this->file_name=file_name;
    this->server_port=server_port;
}

/*
The deserialize function get as inputs const char* buffer ,vector<double>& vec, string& metric, int& k.
the buffer contain the user input that the client send, and we insert them to variables.
As like serialize function, befor the active of the function we initialize buffer and passed it by refference to the fuction so we just update the buffer.
*/

void Server::deserialize(const char* buffer, vector<double>& vec, string& metric, int& k) {
  const char* ptr = buffer;

  // Read the size of the vector
  int vec_size;
  memcpy(&vec_size, ptr, sizeof(int));
  ptr += sizeof(int);

  // Read the vector data
  vec.resize(vec_size);
  memcpy(vec.data(), ptr, vec_size * sizeof(double));
  ptr += vec_size * sizeof(double);

  // Read the distance metric name
  int metric_size;
  memcpy(&metric_size, ptr, sizeof(int));
  ptr += sizeof(int);
  metric.resize(metric_size);
  memcpy(&metric[0], ptr, metric_size);
  ptr += metric_size;

  // Read the int k
  memcpy(&k, ptr, sizeof(int));
}

/*
The createSock function creat sock number to send the cleint the result lable from the knn compute.
The function return a socket number.
*/

int Server::createSock()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
    perror("error creating socket");
    exit(1);
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(this->server_port);
    if (bind(sock, (struct sockaddr*) &sin, sizeof(sin))<0){
        perror("error binding socket");
        exit(1);
    }
    if(listen(sock,5)<0){
        perror("Error listening to socket");
        exit(1);
    }
    return sock;
}

/*
The acceptClient function get as input socket number and creat the clint socket.
the function return the cleint socket.
*/

int Server::acceptClient(int sock)
{
    struct sockaddr_in client_sin;
    unsigned int addr_len= sizeof(client_sin);
    int client_sock=accept(sock, (struct sockaddr*) &client_sin, &addr_len);
    if (client_sock<0){
        perror("error accepting client");
        exit(1);
    }
    return client_sock;
}

/*
The clientRequest function get as input the cleint socket number.
the function use knn to comput the lable and send it to the cleint socket.
*/

void Server::clientRequest(int client_sock)
{
    while (true){
    char buffer[4096];
    int expected_data_len= sizeof(buffer);
    int read_bytes= recv(client_sock, buffer, expected_data_len,0 );
    if (read_bytes ==0)
    {
    //connection is closed.
    close(client_sock);
    break;
    }
    else if (read_bytes<0)
    {
    perror("error receiving information");
    exit(1);
    }   
    //else if information is received successfuly
    else
    {
    vector<double> vec;
    string metric;
    int k;
    deserialize(buffer, vec, metric, k);

    vector<vector<double>> features;
    vector<string> labels;
    
    Input input=Input();
    input.readVec(features,labels,file_name);
    //in case of invalid input for vector or k
    if (vec.size()!=features[0].size() || !(k<=features.size() && k>0))
    {
    //send invalid input string to client which is flag for invalid input
    string label="Invalid Input";
    int sent_bytes= send(client_sock, label.c_str(), label.length(), 0);
    if (sent_bytes<0)
    {
    perror("error sending to client");
    exit(1);
    }
    continue;
    }

    Knn knn=Knn(metric,k);
    knn.fit(features,labels);
    string label=knn.predict(vec);

    int sent_bytes= send(client_sock, label.c_str(), label.length(), 0);
    if (sent_bytes<0)
    {
    perror("error sending to client");
    exit(1);
    }
    }
    }

}

/*
The main function get as an input two arguments: int argc, char* argv[].
The 'int argc' is the size of the array argv, and char* argv[] is the array with the parameters.
The parameters of argv[] is:
argv[1] - file_name.
argv[2] - server_port.
The file name is the csv file with the labaled vector that the knn model train on them. 
The server port is the port number that through him the client send the buffer with the user inputs.
the main function get the client buffer and implement knn algorithem on the input vector from the user.
after we have the predict of the user vector so we send it back to the cleint.
*/


int main(int argc, char* argv[])
{
    string file_name=argv[1];
    fstream fin;
    //tries to open csv file with specific path as file_name
    fin.open(file_name, ios::in);
    // returns error if file cannot be opened
    if (fin.fail())
    {
        cout<<"Error: file does not exist"<<endl;
        exit(1);
    }

    const int server_port=stoi(argv[2]);

     if (!(server_port>=1024 && server_port<=65535))
    {
    cout << "Error: invalid port_number" << endl;
    exit(1);
    }



    Server server=Server(file_name,server_port);

    int sock=server.createSock();

    while (true)
    {
        int client_sock=server.acceptClient(sock);

        //server.clientRequest(client_sock);

        thread t(handleClient, client_sock);
        t.detach();
    }


}
