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

The CLI.cpp class is the program that manage the menue. It use commands array that contain command objects sutable to the menue options. that mean for option 1 the commans contain object type command1, for option 2 the commans contain object type command2, ect..
In total the commands array contain 5 object of the 5 option manue (except the exit option). In the start of the function the class print to the user a message : "Welcome to the KNN Classifier Server. Please choose an option:" and print below the all options in the manue. The printing of every option is made by get_descriptio() fuction that defined to every command class. After the user enter his choise (number between 1-5 or 8) we check which option is sutable to the user input and active the rellevant command class. if the user input is not a number or its number but not between 1-5 or 8, we send to the client "continue" and then the client continu in loop and printing the manue again. The constructor deletes every command in the commands array.

The Command1.cpp class is the option if the user enter 1 to upload unclssified csv file. In this case the client wait for the user to enter the the CSV file with X,Y examples and thire classifications.
