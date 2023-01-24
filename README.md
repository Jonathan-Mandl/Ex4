# Ex4

In this project we implement manue options for the user that use the server-clint connection and compute knn algorithem. The menue allow to choose one of 6 options:

 1) upload unclssified csv file.
 2) algorithem settings.
 3) classify data.
 4) display result.
 5) download result.
 6) exit.

## implementation

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

The Command.cpp class is an abstractic class that all of the other commands classes inherited from her. The getDescription() function reurn string that descript the command. The init function Command() get as arguments: DefaultIO *dio, vector<vector<double>> &Xexamples, vector<string> &Yexamples, vector<vector<double>> &XtoClassify, and super class command initiation.
   

The Command1.cpp class is the option if the user enter 1 to upload unclssified csv file. In this case the client wait for the user to enter CSV file with X,Y examples and thire classifications. The init function Command1() get as argument: DefaultIO *dio, vector<vector<double>> &Xexamples, vector<string> &Yexamples, vector<vector<double>> &XtoClassify, and super class command initiation. The execute() function get from the user local path to csv file to upload in the server. The readExample() function get as inputs line from the csv, and 2 double vector for X,Y featurs. the function enter to the vector the featurs. it also save the lable of these featurs. The readTest() function read from the test csv points for the test to classify. 


The Command2.cpp class is the option if the user enter 2 to define algorithem settings.  The execute() function read from the server the current parameters of K and metric function and print them to the user. after that if the user press enter we stay the parameters and not change it. else if the user enter valid K value and valid metric function, the programe update the paramters and send them ro the server. if one of the parameters or both are invalid, the programe print to the user error message. The init fuction Command2() get as arguments: DefaultIO *dio, int &k, string &metric,vector<vector<double>>& Xexamples), and super class command initiation.
    
 
The Command3.cpp class is the option if the user enter 3 to classify data. The execute() function active the knn algorithem on the data from the csv file that the user upload. if the user didnt upload csv file the programe ask from the user to upload them. The init function Command3() get as argument: DefaultIO* dio,vector<vector<double>>& Xexamples, vector<string>& Yexamples, vector<vector<double>>& XtoClassify, vector<string>& Yresults, string& metric, int& k, and super class command initiation.
 
The Command4.cpp class is the option if the user enter 4 to display results. The execute() function print the results of the knn algorithem from the data to classify. The init function Command5() get as argument : DefaultIO *dio, vector<vector<double>> &Xexamples, vector<vector<double>> &Yexamples , vector<vector<double>> &XtoClassify, vector<string> &Yresults, and super class command initiation.

The Command5.cpp class is the option if the user enter 5 to download results to local path. The execute() function get from the user local path to creat file with the results of the knn algorithem on the classify data. The init function Command5() get as argument : DefaultIO *dio, vector<vector<double>> &Xexamples, vector<vector<double>> &Yexamples , vector<vector<double>> &XtoClassify, vector<string> &Yresults, and super class command initiation.

 The DefaultIO.h is an abstract class that contain read() and write() fuctions to read and write data.
 
 The StandardIO.cpp class is to define that the data read() with cin and write() with cout as the commend line.
 
 The SocketIO.cpp class is define that we read from the socket and write to the socket of the server.

 ## Valid user input
 In the code we check that the inputs and parameters are vailds:
  - In command1.cpp if the user enter invalid path, the program print "invalid input" and return to the main manue.
  - In command2.cpp if the user enter invalid metrik function or k value not in the range or both the program print "invalid value for metric" and " invalid value for K" and return to the main manue.
  - In command3.cpp if the user try to active the knn algorithem befor the upload of csv file, the program print "data upload please" and return to the main manue.
  - In command4.cpp if the user try to get the clssify of the data befor active the knn algorithem or befor the upload of csv file, the program print "data upload please" or "please classify the data" in suit.
 
 ## Compliation Instructions
