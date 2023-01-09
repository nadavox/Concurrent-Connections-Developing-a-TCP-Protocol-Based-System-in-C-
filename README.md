# advancedProgramPart3
A project as part of an advanced programming course how to compile:

1. clone the project to your local path.
2. save datasets folder on your computer.
3. open terminal in the folder that you have cloned the project.
4. write make.
   1. In order to run the server, write the following steps in the terminal: ./server.out file port
      1. file - the path to the classified file in the datasets folder, you have 2 options:
         1. if the datasets located in your project folder, so you add the relative path to the file (without / at the start of the path).
         2. if the datasets is not located in your project folder, so add the full path to the file.
      2. port - the number that the server need to listen to.
      * for example: ./server.out iris_classified.csv 12345
   2. In order to run the client, write the following steps in the terminal: /.client.out ip port
      1. ip - the ip address of the sevrer
      2. port -  the number that the server listen to.
      * for example: ./client.out 127.0.0.1 12345
6. the client program will start and then you will have to insert a vector of numbers as you like in order to classified it, the name of the distance        function you would like to classify the vector according to and the k.

Invalid errors:

1. the k you have inserted is bigger than the amount of vectors in the classified file.
2.the k you have inserted is not a number or negative number.
3. the vectors in the classified file are not at the same size, or the vectors doesn't contain numbers, or the vectors doesn't contain a string that
   classified them.
4. the path you gave is not valid.
5. there is not a disatnce function with the name you gave.
6. the vector you have inserted is not valid, or not at the same size as the vectors in the classified file.
7. the vector you have inserted is bigger then the 4096 chars.
* in case of system errors, we print what caused the error and exit the program.

The implementation of the program:

We built the program according to a design pattern: strategy. That is, we created an abstract class called Distance and created a class for each distance function that inherits the abstract class. In addition, we created an IOclass that receives an input stream and an output stream so that we can read and write from any file to any file in a generic way.
We also created:
1. TCP client class that gets the input from the user and check if the input is valid. if valid, it send the information to the server that will            classified it and prints to the user the classification of the vector according to the information that the server send.
   the client will ask for vector from the user infinitaly and classified it, until the user will give -1 (closing the client).
2. TCP server class which get the input from the client and calculates the distance from it to all the tagged vectors from the given file, calculates the    K nearest neighbors in terms of distance and sends the input vector according to the classification of the K neighbors to the client.
   if one of the client sockets closed so the server willl countinue running and will wait for another client that will send him information.
