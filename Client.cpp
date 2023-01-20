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
#include <fstream>
#include <sstream>
#include <cstdio>
using namespace std;

#include "Client.h"

/*
The Client class initialized by char* ip_address, int port_number.
the cleint use the port number and ip address to connect the server and send him the buffer.
*/

Client::Client(const char *ip_address, const int port_number)
{
  this->ip_address = ip_address;
  this->port_number = port_number;
}

/*
The serverConnect() function creat socket to connect the sever, and return the sock number.
*/

int Client::serverConnect()
{
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
  {
    perror("error creating socket");
    exit(1);
  }
  struct sockaddr_in sin;
  memset(&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = inet_addr(this->ip_address);
  ;
  sin.sin_port = htons(this->port_number);
  if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
  {
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

void Client::serverSend(int sock, string input)
{
  int sent_bytes = send(sock, input.c_str(), input.size(), 0);
  if (sent_bytes < 0)
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
  char buffer[4096];
  memset(buffer, 0, sizeof(buffer));
  int expected_data_len = sizeof(buffer);
  int read_bytes = recv(sock, buffer, expected_data_len, 0);
  if (read_bytes == 0)
  {
    // connection is closed.
    close(sock);
    throw std::exception();
  }
  else if (read_bytes < 0)
  {
    perror("error receiving information");
    exit(1);
  }
  else
  {
    buffer[read_bytes] = '\0';
    return buffer;
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

int main()
{
  // int argc, char* argv[]
  const char *ip_address = "127.0.0.1";
  const int port_number = 5555;
  /*
    struct in_addr addr;
    int result = inet_pton(AF_INET, ip_address, &addr);
    // check if ip adress can be converted. if not, return error
    if (!result) {
      cout << "Error: invalid IP address" << std::endl;
      exit(1);
    }
  */

  if (!(port_number >= 1024 && port_number <= 65535))
  {
    cout << "Error: invalid port_number" << std::endl;
    exit(1);
  }

  Client client = Client(ip_address, port_number);

  int sock = client.serverConnect();

  while (true)
  {
    string menu = client.receive(sock);
    cout << endl;
    cout << menu << endl;
    string command;
    cin >> command;
    client.serverSend(sock, command);

    string output = client.receive(sock);

    if (output == "***upload_file")
    {
      output = client.receive(sock);
      cout << output << endl;
      string train_file;
      cin >> train_file;
      // getline(cink, trainfile)
      fstream fin;
      // open csv file with specific path as file_name
      fin.open(train_file, ios::in);
      // returns error if file cannot be opened
      if (fin.fail())
      {
        client.serverSend(sock, "***invalid_file");
        cout << client.receive(sock) << endl;
        continue;
      }

      client.serverSend(sock, "***valid_file");
      string line;
      // reads every line of csv file
      while (getline(fin, line))
      {
        sleep(0.01);
        client.serverSend(sock, line);
        client.receive(sock);
        line.clear();
      }
      sleep(0.01);
      client.serverSend(sock, "***done");

      output = client.receive(sock);
      if (output == "***invalid file")
      {
        cout << "invalid input";
        continue;
      }
      cout << output << endl; // please upload next file msg

      string test_file;
      cin >> test_file;
      fstream fin2;
      // open csv file with specific path as file_name
      fin2.open(test_file, ios::in);
      // returns error if file cannot be opened
      if (fin2.fail())
      {
        client.serverSend(sock, "***invalid_file");
        cout << client.receive(sock) << endl;
        continue;
      }

      client.serverSend(sock, "***valid_file");
      line.clear();
      // reads every line of csv file
      while (getline(fin2, line))
      {
        sleep(0.01);
        client.serverSend(sock, line);
        client.receive(sock);
        line.clear();
      }
      sleep(0.01);
      client.serverSend(sock, "***done");

      output = client.receive(sock);
      if (output == "***invalid file")
      {
        cout << "invalid input";
        continue;
      }
      cout << output << endl;
    }
    else if (output == "***classify")
    {
      client.serverSend(sock, "ready");
      cout << client.receive(sock) << endl;
    }
    else if (output == "***display")
    {
      client.serverSend(sock, "ready");

      string message = client.receive(sock);

      if (message == "please upload data")
      {
        cout << message << endl;
        continue;
      }
      else if (message == "please classify the data")
      {
        cout << message << endl;
        continue;
      }
      else
      {
        client.serverSend(sock,"ready");

        while (true)
        {
          sleep(0.01);
          output = client.receive(sock);
          cout << output << endl;
          if (output == "Done.\n")
          {
            break;
          }
          client.serverSend(sock, "ready");
        }
      }
    }
    else if(output=="***download")
    {
      client.serverSend(sock, "ready");

      string message = client.receive(sock);

      if (message == "please upload data")
      {
        cout << message << endl;
        continue;
      }
      else if (message == "please classify the data")
      {
        cout << message << endl;
        continue;
      }
      else
      {

      }

    }
    else
    {
      cout << output << endl;
      string input;
      cin.ignore();
      getline(cin, input);
      client.serverSend(sock, input);
      output = client.receive(sock);
      cout << output << endl;
    }
  }
}
