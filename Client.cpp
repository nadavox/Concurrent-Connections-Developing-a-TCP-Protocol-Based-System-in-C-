#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
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
 * the function sends data to the server.
 * @param sock - the client socket number
 * @param s - the data
 */
void sendData(int sock, const string& s) {
    unsigned int data_len = s.length();
    char data_addr[data_len + 1];
    const char* str = s.c_str();
    // copy the data of the vector, distance function name and k to char array
    strcpy(data_addr, str);
    // send the full sentence to the server
    int sent_bytes = send(sock, data_addr, data_len, 0);
    if (sent_bytes < 0) {
        perror("Error sending the data to the server");
        exit(1);
    }
}

/**
 * the function gets data from the server and write it to the output stream
 * @param sock - the client socket number
 */
string receiveData(int sock) {
    char buffer[4096];
    // make the array to zero.
    memset(buffer, 0, sizeof(buffer));
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(sock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        // connection is closed
        perror("Error the connection with the server is closed");
        exit(1);
    }
    else if (read_bytes < 0) {
        perror("Error with reading the data from the server");
        exit(1);
    }
    string s;
    s = buffer;
    return s;
}

/**
 * the function clear the cin.
 */
void clearCin() {
    string trash;
    // clean the buffer
    while(cin) {
        while (cin.peek() == ' ') {
            cin.ignore();
        }
        // if the input has enter key in it so ignore
        if (cin.peek() == '\n') {
            break;
        }
        cin >> trash;
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
    // get menu from the server
    DefaultIO *sdio = new StandardIO;
    // print the menu to the user
    sdio->writeInput(receiveData(sock));
    // get number from the user
    string input = sdio->readInput();
    // send the number to the server
    sendData(sock, input);

    // print the request from the server to the user
    sdio->writeInput(receiveData(sock));
    // get the path to the classified file from the user
    string readClassifiedFilePath = sdio->readInput();
    // create a fileIO object with the classified file path
    DefaultIO *fdio1 = new FileIO(readClassifiedFilePath, "");
    // read lines from the classified file
    string line = fdio1->readInput();
    // there is an error with opening the file
    if (line == "Error with opening the file") {
        // error
    }
    // we got to the end of the file
    else if (line.empty()){
        //empty
    }
    // send the line to the server
    else {
        sendData(sock, line);
        // print the message from the server to the user
        sdio->writeInput(receiveData(sock));

        // print the request from the server to the user
        sdio->writeInput(receiveData(sock));
        // get the path to the un classified file from the user
        string readUnClassifiedFilePath = sdio->readInput();
        // create a fileIO object with the un classified file path
        DefaultIO *fdio2 = new FileIO(readUnClassifiedFilePath, "");
        // read lines from the un classified file
        line = fdio2->readInput();
        // there is an error with opening the file
        if (line == "Error with opening the file") {
            // error
        }
            // we got to the end of the file
        else if (line.empty()){
            //empty
        }
            // send the line to the server
        else {
            sendData(sock, line);
            // print the message from the server to the user
            sdio->writeInput(receiveData(sock));
        }
    }
    return 0;
}
