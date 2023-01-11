#include <iostream>
#include "UploadCommand.h"
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <string>

using namespace std;

bool isNumber(const string& s)
{
    bool hasDigit = false;
    bool hasE = false;
    bool hasPoint = false;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            hasDigit = true;
        } else if (s[i] == 'e' || s[i] == 'E') {
            if (hasE || !hasDigit || i + 1 == s.size()) {
                return false;
            }
            hasE = true;
        } else if (s[i] == '.') {
            if (hasE || hasPoint) {
                return false;
            }
            hasPoint = true;
        } else if (s[i] == '+' || s[i] == '-') {
            if (i != 0 && s[i-1] != 'e' && s[i-1] != 'E') {
                return false;
            }
        } else {
            return false;
        }
    }
    return hasDigit;
}

void classfiedVector(const string& dataVector,  vector<pair<vector<double>, string> >*classfiedVectorList) {
    vector<double> numbers;
    istringstream iss(dataVector);
    string word; string typeVector;
    char * charWord;
    // while loop that each iteration will take one word sepreate by space.
    while (iss >> word) {
        if (!typeVector.empty()) {
            //not good there is more than one string.
            //if not empty there is more string.
        }
        //word is one word of the string
        charWord = &word[0]; // char word point to the start of the word.
        //check if the word is number.
        if (isNumber(charWord)) {
            //it is number
            numbers.push_back(stod(word));
            //TODO: try and catch.
        } else {
            //the string
            typeVector = word;
        }
    }
    if (typeVector.empty()) {
        //there is no classified string.
        //the file is not good.
    }
    pair<vector<double>, string> temppair;
    temppair.first = numbers;
    temppair.second = typeVector;
    classfiedVectorList->push_back(temppair);
}

void notclassfiedVector(string dataVector,  vector<pair<vector<double>, string> > *notClassfiedVectorList) {
    vector<double> numbers;
    istringstream iss(dataVector);
    string word; string typeVector;
    char * charWord;
    // while loop that each iteration will take one word sepreate by space.
    while (iss >> word) {
        //word is one word of the string
        charWord = &word[0]; // char word point to the start of the word.
        //check if the word is number.
        if (isNumber(charWord)) {
            //it is number
            numbers.push_back(stod(word));
            //TODO: try and catch.
        } else {
            //TODO: not good supposed to be only numbers.
            //the string
            typeVector = word;
            //need to check if the string is valid ?
        }
    }
    pair<vector<double>, string> temppair;
    temppair.first = numbers;
    temppair.second = typeVector;
    notClassfiedVectorList->push_back(temppair);
}

void UploadCommand::execute()
{
    //the socket.
    int clientSocket = values->getSocket();
    char buffer[4096];
    string trainString = "Please upload your local train CSV file.\n";
    string testString = "Please upload your local test CSV file.\n";
    string uploadCompleteString = "Upload complete.\n";

    // send the train string to the client
    unsigned int data_len = trainString.length();
    char data_addr[data_len + 1];
    const char* str = trainString.c_str();
    // copy the data of the vector, distance function name and k to char array
    strcpy(data_addr, str);
    // send the full sentence to the server
    int sent_bytes = send(clientSocket, data_addr, data_len, 0);
    if (sent_bytes < 0) {
        perror("Error sending the data to the client");
        exit(1);
    }

    // clean the buffer
    memset(buffer, 0, sizeof(buffer));
    int expected_data_len = sizeof(buffer);
    // get the lines from the client
    int read_bytes = recv(clientSocket, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        // connection is closed
        perror("Error the connection with the server is closed");
        exit(1);
    }
    else if (read_bytes < 0) {
        perror("Error with reading the data from the server");
        exit(1);
    }

    // send the upload complete string to the client
    data_len = uploadCompleteString.length();
    data_addr[data_len + 1];
    str = uploadCompleteString.c_str();
    // copy the data of the vector, distance function name and k to char array
    strcpy(data_addr, str);
    // send the full sentence to the server
    sent_bytes = send(clientSocket, data_addr, data_len, 0);
    if (sent_bytes < 0) {
        perror("Error sending the data to the client");
        exit(1);
    }

    // send the test string to the client
    data_len = testString.length();
    data_addr[data_len + 1];
    str = testString.c_str();
    // copy the data of the vector, distance function name and k to char array
    strcpy(data_addr, str);
    // send the full sentence to the server
    sent_bytes = send(clientSocket, data_addr, data_len, 0);
    if (sent_bytes < 0) {
        perror("Error sending the data to the client");
        exit(1);
    }

    // clean the buffer
    memset(buffer, 0, sizeof(buffer));
    expected_data_len = sizeof(buffer);
    cout << "before receive" << endl;
    // get the lines from the client
    read_bytes = recv(clientSocket, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        // connection is closed
        perror("Error the connection with the server is closed");
        exit(1);
    }
    else if (read_bytes < 0) {
        perror("Error with reading the data from the server");
        exit(1);
    }

    // send the upload complete string to the client
    data_len = uploadCompleteString.length();
    data_addr[data_len + 1];
    str = uploadCompleteString.c_str();
    // copy the data of the vector, distance function name and k to char array
    strcpy(data_addr, str);
    // send the full sentence to the server
    sent_bytes = send(clientSocket, data_addr, data_len, 0);
    if (sent_bytes < 0) {
        perror("Error sending the data to the client");
        exit(1);
    }
}

string UploadCommand::description() {
    return "1. upload an unclassified csv data file\n";

}

UploadCommand::UploadCommand(int socket, Values *valuesCopy) {
    values = valuesCopy;
    valuesCopy->setSocket(socket);
}
