# advancedProgramPart4
A project as part of an advanced programming course how to compile:

How to start the program:

1. clone the project to your local path.
2. save datasets folder on your computer.
3. open terminal in the folder that you have cloned the project.
4. write make.
   1. In order to run the server, write the following steps in the terminal: ./server.out port
      1. port - the number that the server need to listen to.
   * for example: ./server.out 12345
   2. In order to run the client, write the following steps in the terminal: /.client.out ip port
      1. ip - the ip address of the sevrer
      2. port -  the number that the server listen to.
   * for example: ./client.out 127.0.0.1 12345
      
The program:

When the client program will start and a menu will show up like this:
   Welcome to the KNN Classifier server. Please choose an option:
   1. upload an unclassified csv data file
   2. algorithm settings
   3. classify data
   4. display results
   5. download results
   8. exit
   
The options:
1. You will be asked to insert a path to a trained file which contains the classified vectors, and after that you will be asked to insert a path to a    test file which contains the un classified vectors.
2. The program will show tou the current k and disatance metric. the default k is 5 and distance metric is AUC.
* if you want to keep this values - press ENTER.
* if you want to change the values - enter the new k and distance metric as you like.
3. The program will classify the vectors of the un classified vectors you gave in option 1.
* if you haven't gave the files yet (didn't finish option 1), you will get a message that asks you to upload the data first.
4. The program will display for you the results of the classification of the data, it will show you the row number in which the vector showed in the un classified file you gave and it's classification.
* if you haven't gave the files yet (didn't finish option 1), you will get a message that asks you to upload the data first.
* if you haven't classify the data yet (didn't finish option 3), you will get a message that asks you to classify the data first.
5. You will be asked to insert a path to a file that you want the classification of the vectors to be saved in, after you will insert the path, the program will write the classification of the data to this file, it will write the row number in which the vector showed in the un classified file you gave and it's classification.
* if you haven't gave the files yet (didn't finish option 1), you will get a message that asks you to upload the data first.
* if you haven't classify the data yet (didn't finish option 3), you will get a message that asks you to classify the data first.
8. You will exit the program.
* the menu will repeat itself every time the option you wanted finished, until you will press 8.

Invalid errors:

1. you entered a number that is not from one of the options in the menu, or didn't inserted a number.
2. the path to the train file you gave is not valid.
3. the path to the test file you gave is not valid.
4. the vectors in the classified file/ un classified file are not at the same size, or the vectors doesn't contain numbers, or the vectors doesn't contain a string that classified them, or the vectors in the classified file are not at the same size as the vectors in the un classified file.
5. the k you have inserted is bigger than the amount of vectors in the classified file.
6. the k you have inserted is not an integer number or negative number.
7. there is not a disatnce function with the name you gave.
8. you gave more than just k and distance metric, or you gave only k or only distance metric in option 2.
9. you gave k and distance metric in option 2 before inserting the data, and the k is bigger that the classified data, you will get invalid value for k in option 3.
10. the path to the file you gave in option 5 is not valid.
* in case of system errors, we print what caused the error and exit the program.

The implementation of the program:

We built the program according to a design patterns: strategy and command. That is, we created an abstract class called Distance and created a class for each distance function that inherits the abstract class. In addition, we created an abstract class called Command and created a class for each commands option that inherits the abstract class. We also created another abstract class called DefaultIO and created a class sockets communication and standard communication that inherits the abstract class. More over, we created a CLI class that handles the execution of the commands.
We also created:
1. TCP client class that handles the communication with the user and sends the data to the server.
   if the user press 8, the program closes the client.
2. TCP server class which get the input from the client and handles it according to the option the user want to activate.
   if one of the client sockets closed so the server willl countinue running and will wait for another client that will send him information.
