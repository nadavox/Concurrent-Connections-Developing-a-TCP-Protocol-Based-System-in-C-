#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <vector>
#include "Algorithms/Knn.h"
#include "Command_pattern/CLI.h"
#include "Command_pattern/Command.h"
#include <unistd.h>
#include <thread>
#include "IOClass/DefaultIO.h"
#include "IOClass/SocketIO.h"

#define TRUE 1
#define MAX_CLIENTS 30 //max client for the server

using namespace std;

/**
 * the function creates the master socket
 * @return the number of the socket
 */
int createSocket() {
    int opt = TRUE;
    int master_socket, client_sockets[30], i;
    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < MAX_CLIENTS; i++) {
        client_sockets[i] = 0;
    }
    master_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (master_socket < 0) {
        perror("Error while trying to create the server socket");
        exit(1);
    }
    //set master socket to allow multiple connections
    int setSocketOpt = setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &opt, sizeof(opt));
    if (setSocketOpt < 0) {
        perror("Error while trying to allow multiple connections");
        exit(1);
    }
    return master_socket;
}

/**
 * the function gets data from the client and check if the number is valid
 * @param clientSock - the client socket number
 */
string receiveNumber(int clientSock, CLI *c) {
    char buffer[4096];
    // make the array to zero.
    memset(buffer, 0, sizeof(buffer));
    int expected_data_len = sizeof(buffer);
    // read from the client
    long int read_bytes = recv(clientSock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        // connection is closed
        perror("Error the connection with the client is closed");
        //exit(1);
        return "8";
    }
    else if (read_bytes < 0) {
        perror("Error with reading the data from the client");
        //exit(1);
        return "8";
    }

    string number(buffer);
    // the user want to activate option 1
    if (number == "1"){
        // execute UploadCommand
        c->executeCommand("1");
    }
    // the user want to activate option 2
    else if (number == "2") {
        // execute SettingsCommand
        c->executeCommand("2");
    }
    // the user want to activate option 3
    else if (number == "3") {
        // execute ClassifyCommand
        c->executeCommand("3");
    }
    // the user want to activate option 4
    else if (number == "4") {
        // execute DisplayCommand
        c->executeCommand("4");
    }
    // the user want to activate option 5
    else if (number == "5") {
        // execute DownloadCommand
        c->executeCommand("5");
    }
    // the user want to activate option 8
    else if (number == "8") {
        // execute ExitCommand
        c->executeCommand("8");
    }
    // the user didn't inset valid value
    else {
        // error
    }
    return number;
}

/**
 * the function that handles the server
 * @param argc
 * @param argv
 * @return 0 if everything okay and 1 if there is errors
 */
int main(int argc, char *argv[]) {
    //  create the server socket
    int master_socket = createSocket();
    struct sockaddr_in serverAddr = {};
    //type of socket created
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    // check if port number is a number
    try {
        // port number is okay
        int port_no = stoi(argv[1]);
        serverAddr.sin_port = htons(port_no);
    }
        // port number is not a number
    catch (const invalid_argument &) {
        perror("Invalid port number");
        return 1;
    }
    // bind the server
    if (bind(master_socket, (sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error while trying to bind");
        return 1;
    }
    //try to specify maximum of 5 pending connections for the master socket
    if (listen(master_socket, 5) < 0) {
        perror("Error while trying to listen");
        return 1;
    }
    string number;
    while (true) {
        // create a socket for the client
        int client_socket;
        struct sockaddr_in client_sin = {};
        unsigned int addr_len = sizeof(client_sin);
        // accept connection
        if ((client_socket = accept(master_socket, (struct sockaddr *) &client_sin, &addr_len)) < 0) {
            perror("Error while trying to accept the new client");
            return 1;
        }
        //create value object.
        Values *values = new Values(client_socket);
        DefaultIO *dio = new SocketIO(client_socket);
        CLI *cli = new CLI(client_socket, values, dio);
        // create a function that receives the number of the function from the client
        while (number != "8") {
            this_thread::sleep_for(chrono::milliseconds(10));
            cli->start();
            number = receiveNumber(client_socket, cli);
        }
        delete(values);
        delete(cli);
        close(client_socket);
        number.clear();
    }
}