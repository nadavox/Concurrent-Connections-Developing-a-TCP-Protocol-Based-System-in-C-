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
    int socket = values->getSocket();
    char buffer[4096]; string dataVector;
    string firstMessage = "Please upload your local train CSV file.\n";
    string Upload_Complete = "Upload complete.\n";
    //send function: classfiedVector
    strcpy(buffer, firstMessage.c_str());
    int bytes_sent = send(socket, buffer, strlen(buffer), 0);
    if (bytes_sent < 0) {
        ///error
    }
    memset(buffer, 0, sizeof(buffer));
    //receive function in a while until no more data
    while (true) {
        //TODO: if we get line by line from the client i want to put it inside the vector.
        int bytes_received = recv(socket, buffer, strlen(buffer), 0);
        if (bytes_received <= 0) break;
        //if we get line by line.
        dataVector = buffer; // convert the vector/data from the client to string.
        // save the data vector inside the data structure. classfiedVectorList.
        classfiedVector(dataVector, values->getClassfiedVectorList());
    }
    //saved it in data structure classfiedVectorList.
    //send : Upload complete.
    strcpy(buffer, Upload_Complete.c_str());
    bytes_sent = send(socket, buffer, Upload_Complete.size(), 0);
    if (bytes_sent < 0) {
        ///error
    }
    memset(buffer, 0, sizeof(buffer));
    string secondMessage = "Please upload your local test CSV file.\n";
    //send function: notclassfiedVector
    strcpy(buffer, secondMessage.c_str());
    bytes_sent = send(socket, buffer, strlen(buffer), 0);
    if (bytes_sent < 0) {
        ///error
    }
    memset(buffer, 0, sizeof(buffer));
    //receive function in a while until no more data
    while (true) {
        //TODO: if we get line by line from the client i want to put it inside the vector.
        int bytes_received = recv(socket, buffer, strlen(buffer), 0);
        if (bytes_received <= 0) break;
        //if we get line by line.
        dataVector = buffer; // convert the vector/data from the client to string.
        // save the data vector inside the data structure. notClassfiedVectorList.
        notclassfiedVector(dataVector, values->getNotClassfiedVectorList());
    }
    //save it in data structure notClassfiedVectorList.
    //send : Upload complete.
    strcpy(buffer, Upload_Complete.c_str());
    bytes_sent = send(socket, buffer, Upload_Complete.size(), 0);
    if (bytes_sent < 0) {
        ///error
    }
    memset(buffer, 0, sizeof(buffer));
}

string UploadCommand::description() {
    return "1. upload an unclassified csv data file\n";

}

UploadCommand::UploadCommand(int socket, Values *valuesCopy) {
    values = valuesCopy;
    valuesCopy->setSocket(socket);
}
