# Ex4

In this project we implement manue options for the user that use the server-clint connection and compute knn algorithem. The menue allow to choose one of 6 options:

 1) upload unclssified csv file.
 2) algorithem settings.
 3) classify data.
 4) display result.
 5) download result.
 6) exit.


In the project we use the functions and classes from the last exercise, and add new classes to manege the manue options. The new classes is:
 - CLI.cpp
 - Command.cpp
 - Command1.cpp
 - Command2.cpp
 - Command3.cpp
 - Command4.cpp
 - Command5.cpp
 - StandardIO.cpp
 - SocketIO.cpp
 - DefaultIO.h

The CLI.cpp class is the program that manage the menue. It use commands array that contain command objects sutable to the menue optins. that mean for option 1 the commans contain object type command1, for option 2 the commans contain object type command2, ect..
