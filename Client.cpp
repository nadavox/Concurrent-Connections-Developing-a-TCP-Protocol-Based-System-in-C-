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
 * the function gets messages from the server and sends the lines from the files to the server
 * @param sock - the client socket
 * @param sdio - the StandardIO object
 */
void function1(int sock, DefaultIO* sdio) {
    // print the request from the server to the user
    sdio->writeInput(receiveData(sock));
    // get the path to the classified file from the user
    string readClassifiedFilePath = sdio->readInput();
    // create a fileIO object with the classified file path
    DefaultIO *fdio1 = new FileIO(readClassifiedFilePath, "");
    ifstream inputFile;
    // open the file, doesn't matter if it relative or not.
    inputFile.open(readClassifiedFilePath);
    string line = "";
    // could not open the file
    if (!inputFile)
    {
        perror("Error with opening the file");
        return;
    }
    // reading lines from the first file
    while(getline(inputFile, line)) {
        cout << line << endl;
        sendData(sock, line);
    }
    sendData(sock, "done");
    // print the request from the server to the user
    sdio->writeInput(receiveData(sock));
    // print the request from the server to the user
    sdio->writeInput(receiveData(sock));
    // get the path to the un classified file from the user
    string readUnClassifiedFilePath = sdio->readInput();
    // create a fileIO object with the classified file path
    DefaultIO *fdio2 = new FileIO(readUnClassifiedFilePath, "");
    // open the file, doesn't matter if it relative or not.
    inputFile.open(readUnClassifiedFilePath);
    // could not open the file
    if (!inputFile)
    {
        perror("Error with opening the file");
        return;
    }
    // reading lines from the first file
    while(getline(inputFile, line)) {
        sendData(sock, line);
    }
    sendData(sock, "done");
    // print the request from the server to the user
    sdio->writeInput(receiveData(sock));
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

    // the user want to activate option 1
    if (input == "1"){
        // call function1
        function1(sock, sdio);
    }
        // the user want to activate option 2
    else if (input == "2") {
        // call function2
    }
        // the user want to activate option 3
    else if (input == "3") {
        // call function3
    }
        // the user want to activate option 4
    else if (input == "4") {
        // call function4
    }
        // the user want to activate option 5
    else if (input == "5") {
        // call function5
    }
        // the user want to activate option 8
    else if (input == "8") {
        // call function8
    }
        // the user didn't inset valid value
    else {
        // invalid number
    }
    return 0;
}
