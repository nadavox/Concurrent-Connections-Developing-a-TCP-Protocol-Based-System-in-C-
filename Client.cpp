#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include "IOClass/DefaultIO.h"
#include "IOClass/StandardIO.h"
#include "IOClass/SocketIO.h"
#include "fstream"

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
 * the function gets messages string and check if valid or not
 * @param output - the string we check
 * @param sdio - the StandardIO object
 * @param stdio - the SocketIO object
 */
bool check_valid(const string& output, DefaultIO *sdio,DefaultIO *stdio) {
    if (output == "invalid input")
    {
        // sending to the server that exit the function and get back to the main menu.
        sdio->writeInput("invalid input\n");
        stdio->writeInput("Error");
        return false;
    }
    return true;
}

/**
 * the function check if we can open file or not
 * @param inputFileOne - the file we check
 * @param sdio - the StandardIO object
 * @param stdio - the SocketIO object
 */
bool check_file(ifstream& inputFileOne, DefaultIO *sdio,DefaultIO *stdio, string path) {
    // open the file, doesn't matter if it relative or not.
    inputFileOne.open(path);
    if (!inputFileOne)
    {
        // sending to the server that exit the function and get back to the main menu.
        stdio->writeInput("Error");
        sdio->writeInput("invalid input\n");
        return false;
    }
    return true;
}

/**
 * the function read the context from the file
 * @param inputFileOne - the file string we check
 * @param stdio - the SocketIO object
 */
void reading_from_file(ifstream& inputFileOne, DefaultIO* stdio) {
    char buffer[1024];
    // clean the buffer
    memset(buffer, 0, 1024);
    // reading chunks of data from the file
    while(inputFileOne.read(buffer, 1023) || inputFileOne.gcount() > 0) {
        // converting char array to string
        string input(buffer, sizeof(buffer) / sizeof(buffer[0]));
        // sending the string to the server
        stdio->writeInput(input);
        // clean the buffer
        memset(buffer, 0, 1024);
    }
    // let the server now we are done
    stdio->writeInput("done");
}

/**
 * the function gets messages from the server and sends the lines from the files to the server
 * @param sdio - the StandardIO object
 * @param stdio - the SocketIO object
 */
void function1(DefaultIO* sdio, DefaultIO* stdio) {
    // get the message from the server
    string messageFromServer = stdio->readInput();
    // print the request from the server to the user
    sdio->writeInput(messageFromServer);
    // get the path to the classified file from the user
    string readClassifiedFilePath = sdio->readInput();
    // create fstream object to read from it.
    ifstream inputFile;
    // check if we can open the file
    if (!check_file(inputFile, sdio, stdio, readClassifiedFilePath)) {
        return;
    }
    // reading the input from the file into the server.
    reading_from_file(inputFile, stdio);
    // print the message from the server to the user
    string output = stdio->readInput();
    // check if the ouptput is valid or not
    if (!check_valid(output, sdio, stdio)) {
        return;
    }
    // write the message from the server
    sdio->writeInput(output);
    // get the path to the un classified file from the user
    string readUnClassifiedFilePath = sdio->readInput();
    //open the new file and close the old one
    inputFile.close();
    if (!check_file(inputFile, sdio, stdio, readUnClassifiedFilePath)) {
        return;
    }
    // reading the input from the file into the server.
    reading_from_file(inputFile, stdio);
    // print the request from the server to the user
    output = stdio->readInput();
    if (!check_valid(output, sdio, stdio)) {
        return;
    }
    //print the output complete from the server.
    sdio->writeInput(output);
    // tell the server client finish print the message ready for the next one.
    stdio ->writeInput(output);
}

/**
 * this function get messages from the server and sends the input from the user about the parameters
 * @param sdio - the StandardIO object
 * @param stdio - the SocketIO object
 */
void function2(DefaultIO* sdio, DefaultIO* stdio) {
    //read the information from the server
    string information = stdio->readInput();
    // print the information from the server
    sdio->writeInput(information);
    // get the user response
    string userUpdate = sdio->readInput();
    // the user want to update the parameters
    if (!userUpdate.empty()) {
        // send the server the input from the user
        stdio->writeInput(userUpdate);
        // the anser from the server
        string answer = stdio->readInput();
        // send message to the server that finished read the message
        stdio->writeInput("finish");
        // one of the parameters the user have inserted is not valid
        if (answer != "input is valid\n") {
            // print in the terminal the information from the server
            sdio->writeInput(answer);
            // send message that the user ready for the next message
            stdio->writeInput("continue");
        }
    }
    // the user don't want to update the parameters
    else {
        // send the server that the user don't want to update the parameters
        stdio->writeInput("done");
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
        // let the server know we are done reading
        stdio->writeInput("finish read");
        // print the information from the server
        sdio->writeInput(s);
        // there are no more classification or the user need to make some other function before this one
        if (s == "Done.\n" || s == "please upload data\n" || s == "please classify the data\n") {
            break;
        }
    }
}

/**
 * this function writes in classification of the vectors to the given file
 * @param s - the classification
 * @param path - the path to the file
 */
void writeClassified(string s, string path) {
    ofstream writeToFile;
    writeToFile.open(path);
    writeToFile << s;
    writeToFile.close();
}

/**
 * this function writes to a file the classification of the vectors
 * @param sdio - the StandardIO object
 * @param stdio - the SocketIO object
 */
void function5(DefaultIO* sdio, DefaultIO* stdio) {
    ofstream outfile; //outfile is the file we write
    string s = stdio->readInput();
    // let the server know we are done reading
    stdio->writeInput("finish read");
    // print the information from the server
    sdio->writeInput(s);
    // the user don't need to make some other function before this one
    if (s != "please upload data\n" && s != "please classify the data\n") {
        // get a path to a file which we will write the results to
        string writeFilePath = sdio->readInput();
        // check if the string is valid to open the file
        outfile.open(writeFilePath);
        if (!outfile.is_open()) {
            writeFilePath = "Error";
            sdio->writeInput("invalid input\n");
            stdio->writeInput(writeFilePath);
            return;
        } else {
            outfile.close();
        }
        //send the server if the file is good to open or not
        stdio->writeInput(writeFilePath);
        string message;
        //receive all the file from the server
        string temp; // temp string to hold the rows.
        // print the classification to the user from the server until there are no more
        while (true) {
            temp = stdio->readInput();
            if (temp != "Done.\n") {
                message += temp;
                // let the server know we are done reading
                stdio->writeInput("finish read");

            } else {
                // let the server know we are done reading
                stdio->writeInput("finish read");
                break;
            }
        }
        // crate a new thread that will write the classification to the file
        thread t(writeClassified, message, writeFilePath);
        t.detach();
    }
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
        // get the menu to the server
        string menu = stdio->readInput();
        // print the menu to the user
        sdio->writeInput(menu);
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
            // let the server now we are done
            stdio->writeInput("done");
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
            delete sdio;
            delete stdio;
            // close the client socket
            close(sock);
            break;
        }
        // the user insert invalid number
        else {
            // print the invalid input to the user
            string invalid_input = stdio->readInput();
            sdio->writeInput(invalid_input);
            stdio->writeInput("done reading");
        }
    }
    return 0;
}
