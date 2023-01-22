all: server.out client.out

server.out: Server.o Input.o Distance.o Knn.o CLI.o Command.o Command1.o Command2.o Command3.o Command4.o Command5.o SocketIO.o
	g++ -pthread -std=c++11 Input.o Distance.o Knn.o CLI.o Command.o Command1.o Command2.o Command3.o Command4.o Command5.o SocketIO.o Server.o -o server.out

client.out: Client.o
	g++ -pthread -std=c++11 Client.o -o client.out

Input.o: Input.cpp Input.h
	g++ -pthread -std=c++11 -c Input.cpp

Knn.o: Knn.cpp Knn.h
	g++ -pthread -std=c++11 -c Knn.cpp

CLI.o: CLI.cpp CLI.h
	g++ -pthread -std=c++11 -c CLI.cpp

Command.o: Command.cpp Command.h
	g++ -pthread -std=c++11 -c Command.cpp

Command1.o: Command1.cpp Command1.h
	g++ -pthread -std=c++11 -c Command1.cpp

Command2.o: Command2.cpp Command2.h
	g++ -pthread -std=c++11 -c Command2.cpp

Command3.o: Command3.cpp Command3.h
	g++ -pthread -std=c++11 -c Command3.cpp

Command4.o: Command4.cpp Command4.h
	g++ -pthread -std=c++11 -c Command4.cpp

Command5.o: Command5.cpp Command5.h
	g++ -pthread -std=c++11 -c Command5.cpp

SocketIo.o: SocketIO.cpp SocketIO.h
	g++ -pthread -std=c++11 -c SocketIO.cpp

Distance.o: Distance.cpp Distance.h
	g++ -pthread -std=c++11 -c Distance.cpp

Server.o: Server.cpp Server.h
	g++ -pthread -std=c++11 -c Server.cpp

Client.o: Client.cpp Client.h
	g++ -pthread -std=c++11 -c Client.cpp
	
clean:
	rm *.o
