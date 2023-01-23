#include "SocketIO.h"
using namespace std;

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

SocketIO::SocketIO(int client_sock) : client_sock(client_sock)
{
    
}

string SocketIO::read(){
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    int expected_data_len= sizeof(buffer);
    int read_bytes= recv(client_sock, buffer, expected_data_len,0 );
    if (read_bytes ==0)
    {
        close(client_sock);
        throw std::exception();
    }
    else if (read_bytes<0)
    {
        perror("error receiving information");
        exit(1);
    } 
    else{ 
    buffer[read_bytes]='\0';
    return buffer;
    }
}

void SocketIO::write(string output)
{
    int sent_bytes= send(client_sock, output.c_str(), output.length(), 0);
    if (sent_bytes<0)
    {
        perror("error sending to client");
        exit(1);
    }
}



