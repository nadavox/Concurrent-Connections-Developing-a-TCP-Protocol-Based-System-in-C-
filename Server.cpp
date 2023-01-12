#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <vector>
#include <fstream>
#include "Algorithms/Distance.h"
#include "Algorithms/EuclideanDistance.h"
#include "Algorithms/TaxicabGeometry.h"
#include "Algorithms/ChebyshevDistance.h"
#include "Algorithms/MinkowskiDistance.h"
#include "Algorithms/CanberraDistance.h"
#include "Algorithms/Knn.h"
#include "Command_pattern/CLI.h"
#include "Command_pattern/Command.h"
#include "Command_pattern/UploadCommand.h"
#include "Command_pattern/SettingsCommand.h"
#include "Command_pattern/ClassifyCommand.h"
#include "Command_pattern/DisplayCommand.h"
#include "Command_pattern/DownloadCommand.h"
#include "Command_pattern/ExitCommand.h"
#include <unistd.h>

#define TRUE 1
#define ERROR 1 // if the size of the vector is not good
#define MAX_CLIENTS 30 //max client for the server

using namespace std;

/**
 * this function classified the user vector.
 * @param kindDistance
 * @param k
 * @param userVector
 * @param vectorsList
 * @return the name of the classified vector
 */
string getKnnOutput(const string& kindDistance, int k, vector<double> userVector,
                    vector<pair<vector<double>, string> > *vectorsList) {
    string output;
    Distance *distanceAlgo;
    // we will calculate knn according to euclidean distance
    if (kindDistance == "AUC") {
        distanceAlgo = new EuclideanDistance;
    }
        // we will calculate knn according to taxicab geometry
    else if (kindDistance == "MAN") {
        distanceAlgo = new TaxicabGeometry;
    }
        // we will calculate knn according to chebyshev distance
    else if (kindDistance == "CHB") {
        distanceAlgo = new ChebyshevDistance;
    }
        // we will calculate knn according to canberra distance
    else if (kindDistance == "CAN") {
        distanceAlgo = new CanberraDistance;
    }
        // we will calculate knn according to minkowski distance
    else {
        distanceAlgo = new MinkowskiDistance;
    }
    // now we have the vector all what left is to calculate.
    Knn knnAlgo = Knn(distanceAlgo, k);
    // calculate knn
    output = knnAlgo.CalculateKNN(userVector, *vectorsList);
    free(distanceAlgo);
    return output;
}

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
 * the function classify the input from the user and send it to the client
 * @param vectorsList - the classified vectors from the file
 * @param new_socket - the socket that listens to the current client
 * @param buffer - the buffer that has the input from the user
 */
void classifyData(vector<pair<vector<double>, string> > *vectorsList, int new_socket, const char buffer[4096]) {
    int kFlag = 0, k;
    string output, kindDistance;
    double number;
    char data_error[] = "invalid input";
    int data_error_len = strlen(data_error);
    // Parse the received data
    stringstream ss(buffer);
    vector<string> userVectorDemo;
    vector<double> userVector;
    string value;
    while (ss >> value) {
        userVectorDemo.push_back(value);
    }
    // make the size of the user vector
    unsigned long sizeUserVector = userVectorDemo.size() - 2;
    // make the size of the server vector
    unsigned long sizeServerVector = vectorsList->at(0).first.size();
    // check if the user vector is in the right size of the vector list.
    if (sizeUserVector != sizeServerVector) {
        kFlag = ERROR; // the size of the vector is too big or too small
    } else {
        int i;
        //the size of the vector is good.
        for (i = 0; i < sizeUserVector; ++i) {
            try {
                number = stoi(userVectorDemo.at(i));
                userVector.push_back(number);
            } catch (const invalid_argument&) {
                cout << userVectorDemo.at(i)<< endl;
            }
        }
        kindDistance = userVectorDemo.at(sizeUserVector);
        try {
            k = stoi(userVectorDemo.at(sizeUserVector + 1));
        } catch (const invalid_argument&) {
            cout << userVectorDemo.at(sizeUserVector + 1)<< endl;
        }
        //check if k is valid
        if (k > vectorsList->size()) {
            // k is not valid
            kFlag = ERROR;
        }
    }
    // the string from the user is valid
    if (!kFlag) {
        output = getKnnOutput(kindDistance, k, userVector, vectorsList);
    }
    // Send the result back to the client
    if (kFlag) {
        // send the error message to the client
        send(new_socket, data_error, data_error_len, 0);
    }
    else {
        unsigned int data_len = output.length();
        char data_addr[data_len + 1];
        const char *str = output.c_str();
        // copy the data of the vector, distance function name and k to char array
        strcpy(data_addr, str);
        // send the full sentence to the client
        send(new_socket, data_addr, data_len, 0);
    }
    userVector.clear();
}

/**
 * the function gets data from the client and check if the number is valid
 * @param clientSock - the client socket number
 */
string receiveNumber(int clientSock, Values *value) {
    char buffer[4096];
    // make the array to zero.
    memset(buffer, 0, sizeof(buffer));
    int expected_data_len = sizeof(buffer);
    // read from the client
    int read_bytes = recv(clientSock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        // connection is closed
        perror("Error the connection with the client is closed");
        exit(1);
    }
    else if (read_bytes < 0) {
        perror("Error with reading the data from the client");
        exit(1);
    }
    string number(buffer);
    // the user want to activate option 1
    if (number == "1"){
        // execute UploadCommand
        Command *us = new UploadCommand(clientSock, value);
        us->execute();
        free(us);
    }
    // the user want to activate option 2
    else if (number == "2") {
        // execute SettingsCommand
        Command *sc = new SettingsCommand();
        sc->execute();
        free(sc);
    }
    // the user want to activate option 3
    else if (number == "3") {
        // execute ClassifyCommand
        Command *cc = new ClassifyCommand();
        cc->execute();
        free(cc);
    }
    // the user want to activate option 4
    else if (number == "4") {
        // execute DisplayCommand
        Command *dyc = new DisplayCommand();
        dyc->execute();
        free(dyc);
    }
    // the user want to activate option 5
    else if (number == "5") {
        // execute DownloadCommand
        Command *ddc = new DownloadCommand();
        ddc->execute();
        free(ddc);
    }
    // the user want to activate option 8
    else if (number == "8") {
        // execute ExitCommand
        Command *ec = new ExitCommand();
        ec->execute();
        free(ec);
    }
    // the user didn't inset valid value
    else {
        // invalid number
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
        // create CLI object that will send the menu
        Command *us = new UploadCommand(client_socket, values);
        Command *sc = new SettingsCommand();
        Command *cc = new ClassifyCommand();
        Command *dyc = new DisplayCommand();
        Command *ddc = new DownloadCommand();
        Command *ec = new ExitCommand();
        CLI *cli = new CLI(us, sc, cc, dyc, ddc, ec, client_socket);
        // create a function that receives the number of the function from the client
        while (number != "8") {
            cli->start();
            number = receiveNumber(client_socket, values);
            cout << "finish" << endl;
        }
        free(us);
        free(sc);
        free(cc);
        free(dyc);
        free(ddc);
        free(ec);
        free(cli);
        close(client_socket);
        number.clear();
    }
}