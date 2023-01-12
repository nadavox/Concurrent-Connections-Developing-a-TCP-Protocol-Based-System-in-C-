#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <thread>
#include "IOClass/DefaultIO.h"
#include "IOClass/StandardIO.h"
#include "IOClass/SocketIO.h"
#include "IOClass/FileIO.h"

using namespace std;

/**
 * the function create a TCP client socket
 * @param portNumber - the port number that the server socket listens to.
 * @param ipAddress - the ip address of the server.
 * @return the socket number
 */
int createSocket(int portNumber, char* ipAddress) {
    int sock = socket(AF_INET, SOCK_STREAM,0);
    // there is an error
    if (sock < 0) {
        perror("Error while trying to create the client socket");
        exit(1);
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ipAddress);
    sin.sin_port = htons(portNumber);
    // there is an error in connecting to the server socket
    if (connect(sock, (struct sockaddr*) &sin, sizeof(sin)) < 0) {
        perror("Error connecting to server");
        exit(1);
    }
    return sock;
}

/**
 * the function gets messages from the server and sends the lines from the files to the server
 * @param sdio - the StandardIO object
 * @param stdio - the SocketIO object
 */
void function1(DefaultIO* sdio, DefaultIO* stdio) {
    // print the request from the server to the user
    sdio->writeInput(stdio->readInput());
    // get the path to the classified file from the user
    string readClassifiedFilePath = sdio->readInput();
    ifstream inputFileOne;
    // open the file, doesn't matter if it relative or not.
    inputFileOne.open(readClassifiedFilePath);
    string line = "";
    // could not open the file
    if (!inputFileOne)
    {
        perror("Error with opening the file");
        return;
    }

    // reading lines from the first file
    while(getline(inputFileOne, line)) {
        stdio->writeInput(line);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    // let the server now we are done
    stdio->writeInput("done");
    // print the message from the server to the user
    sdio->writeInput(stdio->readInput());
    // get the path to the un classified file from the user
    string readUnClassifiedFilePath = sdio->readInput();
    ifstream inputFileTwo;
    // open the file, doesn't matter if it relative or not.
    inputFileTwo.open(readUnClassifiedFilePath);
    // could not open the file
    if (!inputFileTwo)
    {
        perror("Error with opening the file");
        return;
    }
    // reading lines from the first file
    while(getline(inputFileTwo, line)) {
        stdio->writeInput(line);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    stdio->writeInput("done");
    // print the request from the server to the user
    sdio->writeInput(stdio->readInput());
}

/**
 * this function get messages from the server and sends the input from the user about the parameters
 * @param sdio - the StandardIO object
 * @param stdio - the SocketIO object
 */
void function2(DefaultIO* sdio, DefaultIO* stdio) {
    // print the information from the server
    sdio->writeInput(stdio->readInput());
    // get the user response
    string userUpdate = sdio->readInput();
    // send the server the input from the user
    stdio->writeInput(userUpdate);
    string isNotOkay = stdio->readInput();
    if (isNotOkay == "1") {
        // print the information from the server
        sdio->writeInput(stdio->readInput());
    }
    // both parameters are not valid
    else if(isNotOkay == "2") {
        // print the information from the server
        sdio->writeInput(stdio->readInput());
        // print the information from the server
        sdio->writeInput(stdio->readInput());
    }
}

/**
 * this function prints to the user the classification of the vectors
 * @param sdio - the StandardIO object
 * @param stdio - the SocketIO object
 */
void function4(DefaultIO* sdio, DefaultIO* stdio) {
    string s;
    // print the classification to the user from the server until there are no more
    while (true) {
        s = stdio->readInput();
        // print the information from the server
        sdio->writeInput(s);
        // there are no more classification or the user need to make some other function before this one
        if (s == "Done." || s == "please upload data" || s == "please classify the data") {
            break;
        }
    }
}

/**
 * this function writes the classification of the vectors to a file
 * @param sdio - the StandardIO object
 * @param stdio - the SocketIO object
 */
void function5(DefaultIO* sdio, DefaultIO* stdio) {
    // get a path to a file which we will write the results to
    string writeFilePath = sdio->readInput();
    DefaultIO* fdio = new FileIO("", writeFilePath);
    string s;
    // print the classification to the user from the server until there are no more
    while (true) {
        s = stdio->readInput();
        // there are no more classification
        if (s == "Done.") {
            break;
        }
        // the user need to make some other function before this one
        else if (s == "please upload data" || s == "please classify the data") {
            // print the information from the server
            sdio->writeInput(s);
            break;
        }
        // the string from the server is a classification of a vector
        else {
            // write the result to the file
            fdio->writeInput(s);
        }
    }
    // delete the allocation of fdio
    delete(fdio);
}


/**
 * the function that handles the client
 * @param argc
 * @param argv
 * @return 0 if everything okay and 1 if there is errors
 */
int main(int argc, char *argv[]) {
    int port_no;
    // check if port number is a number
    try {
        // port number is okay
        port_no = stoi(argv[2]);
    }
    // port number is not a number
    catch (const invalid_argument&) {
        perror("Invalid port number");
        return 1;
    }
    // get ip address
    char* ip_address = argv[1];
    // create a socket
    int sock = createSocket(port_no, ip_address);
    // create StandardIO object
    DefaultIO *sdio = new StandardIO;
    // create SocketIO object
    DefaultIO *stdio = new SocketIO(sock);
    // get the program to run until the user press 8
    while(true) {
        // print the menu to the user
        sdio->writeInput(stdio->readInput());
        // get number from the user
        string input = sdio->readInput();
        // send the number to the server
        stdio->writeInput(input);

        // the user want to activate option 1
        if (input == "1"){
            // call function1
            function1(sdio, stdio);
        }
        // the user want to activate option 2
        else if (input == "2") {
            // call function2
            function2(sdio, stdio);
        }
        // the user want to activate option 3
        else if (input == "3") {
            // print the information from the server
            sdio->writeInput(stdio->readInput());
        }
        // the user want to activate option 4
        else if (input == "4") {
            // call function4
            function4(sdio, stdio);
        }
        // the user want to activate option 5
        else if (input == "5") {
            // call function5
            function5(sdio, stdio);
        }
        // the user want to activate option 8
        else if (input == "8") {
            // delete the allocation of sdio
            delete(sdio);
            delete(stdio);
            // close the client socket
            close(sock);
            break;
        }
        // the user didn't inset valid value
        else {
            // invalid number
        }
    }
    return 0;
}
