#include <iostream>
#include <string.h>
#include <netinet/in.h>
#include <vector>
#include <fstream>
#include "Algorithms/Distance.h"
#include "IOClass/IOClass.h"
#include "Algorithms/EuclideanDistance.h"
#include "Algorithms/TaxicabGeometry.h"
#include "Algorithms/ChebyshevDistance.h"
#include "Algorithms/MinkowskiDistance.h"
#include "Algorithms/CanberraDistance.h"
#include "Algorithms/Knn.h"
#include <unistd.h>

#define TRUE 1
#define ERROR 1 // if the size of the vector is not good
#define MAX_CLIENTS 30 //max client for the server

using namespace std;

/**
 * the function creates the vector that contains all the vectors in the file
 * @param vectorsList
 * @param io
 * @return vector that contains all the vectors in the file
 */
vector<pair<vector<double>, string> >* readfile(vector<pair<vector<double>, string> >* vectorsList, IOClass io) {
    //read the file inside to our vector list.
    vectorsList = io.readInput();
    //there is a not valid vector in the classified file, so end the program
    return vectorsList;
}

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
 * the function that handles the server
 * @param argc
 * @param argv
 * @return 0 if everything okay and 1 if there is errors
 */
int main(int argc, char *argv[]) {
    //flag for k not valid, and string for the output.
    string output;
    ifstream inputFile;
    // open the file, doesn't matter if it relative or not.
    inputFile.open(argv[1]);
    // could not open the file
    if (!inputFile) {
        cout << "Could not open file: '" << argv[2] << "'\n";
        return 1;
    }

    //pointer to a vector object will be the list of pairs of vectors (vector , string).
    vector<pair<vector<double>, string> > *vectorsList = nullptr;
    //create ioClass for input and output.
    IOClass io(inputFile, cout);
    //read the file and create the vector list.
    vectorsList = readfile(vectorsList, io);
    //there is a not valid vector in the classified file, so end the program
    if (vectorsList == nullptr) {
        io.write("Error, the vectors in the classified file is not valid");
        return 1;
    }

    int master_socket = createSocket();

    struct sockaddr_in serverAddr = {};
    //type of socket created
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    // check if port number is a number
    try {
        // port number is okay
        int port_no = stoi(argv[2]);
        serverAddr.sin_port = htons(port_no);
    }
    // port number is not a number
    catch (const invalid_argument&) {
        perror("Invalid port number");
        return 1;
    }
    if (::bind(master_socket, (sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error while trying to bind");
        return 1;
    }
    //try to specify maximum of 5 pending connections for the master socket
    if (listen(master_socket, 5) < 0) {
        perror("Error while trying to listen");
        return 1;
    }

    int new_socket;
    vector<double> userVector;
    while (true) {
        char buffer[4096]; // data buffer
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        if ((new_socket = accept(master_socket, (struct sockaddr *) &client_sin, &addr_len)) < 0) {
            perror("Error while trying to accept the new client");
            return 1;
        }
        long bytes = recv(new_socket, buffer, sizeof(buffer), 0);
        while (bytes > 0) {
            classifyData(vectorsList, new_socket, buffer);
            memset(buffer, '\0', 4096);
            bytes = recv(new_socket, buffer, sizeof(buffer), 0);
        }
        close(new_socket);
    }
}