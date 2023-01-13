#include <iostream>
#include "UploadCommand.h"
#include <sys/socket.h>
#include <cstring>
#include <sstream>
#include <string>
#include <string.h>

using namespace std;

bool check_done(char* file_data, long int file_size) {
    if (file_size < 4) {
        return false;
    }
    return file_data[file_size - 4] == 'd' && file_data[file_size - 3] == 'o' && file_data[file_size - 2] == 'n' && file_data[file_size - 1] == 'e';
}

/**
 * this function checks if a string is double.
 * @param s - the string
 * @return true if the string is double, false if not
 */
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

/**
 * this function save the classified vector in the classifiedVectorList
 * @param dataVector - the string
 */
void UploadCommand::classifiedVector(const vector<char>& dataVector) {
    string line;
    vector<std::string> lines;
    for (auto c : dataVector) {
        if (c == '\n' || c == '\r') {
            lines.push_back(line);
            line.clear();
        } else {
            line += c;
        }
    }
    // add the last line if there's no newline at the end of the file
    if (!line.empty()) {
        lines.push_back(line);
    }
    for (auto l : lines) {
        vector<double> numbers;
        istringstream iss(l);
        string word, typeVector;
        char *charWord;
        // while loop that each iteration will take one word separate by space.
        while (getline(iss, word, ',')) {
            // there is more than one string for the vector
            if (!typeVector.empty()) {
                // error
            }
            // char word point to the start of the word.
            charWord = &word[0];
            //check if the word is number.
            if (isNumber(charWord)) {
                //it is number
                numbers.push_back(stod(word));
            } else {
                //the string
                typeVector = word;
            }
        }
        // there is no classified string
        if (typeVector.empty()) {
            // error
        }
        pair<vector<double>, string> tempPair;
        tempPair.first = numbers;
        tempPair.second = typeVector;
        values->setClassifiedVectorList(&tempPair);
    }
}

/**
 * this function save the un classified vector in the unClassifiedVectorList
 * @param dataVector - the string
 */
void UploadCommand::notClassifiedVector(const vector<char>& dataVector) {
    string line;
    vector<std::string> lines;
    for (auto c : dataVector) {
        if (c == '\n' || c == '\r') {
            lines.push_back(line);
            line.clear();
        } else {
            line += c;
        }
    }
    // add the last line if there's no newline at the end of the file
    if (!line.empty()) {
        lines.push_back(line);
    }
    for (auto l : lines) {
        vector<double> numbers;
        istringstream iss(l);
        string word, typeVector;
        char *charWord;
        // while loop that each iteration will take one word separate by space.
        while (getline(iss, word, ',')) {
            // char word point to the start of the word.
            charWord = &word[0];
            //check if the word is number.
            if (isNumber(charWord)) {
                //it is number
                numbers.push_back(stod(word));
            } else {
                //the string
                typeVector = word;
                // error
            }
        }
        if (!numbers.empty()) {
            values->setNotClassifiedVectorList(&numbers);
        }
    }

}

/**
 * this function sends and receives message from the client.
 * every vector we get, we save.
 */
void UploadCommand::execute() {
    //the client socket
    int clientSocket = values->getSocket();
    char buffer[1028];
    // clean the buffer
    memset(buffer, 0, sizeof(buffer));
    string trainString = "Please upload your local train CSV file.\n";
    string uploadComplete1String = "Upload complete.\nPlease upload your local test CSV file.\n";
    string uploadComplete2String = "Upload complete.\n";
    vector<string> classifiedStrings;
    vector<string> unclassifiedStrings;

    // send the train string to the client
    unsigned int data_len = trainString.length();
    char data_addr[data_len + 1];
    const char* str = trainString.c_str();
    // copy the data to the char array
    strcpy(data_addr, str);
    // send the string to the server
    long int sent_bytes = send(clientSocket, data_addr, data_len, 0);
    if (sent_bytes < 0) {
        perror("Error sending the data to the client");
        exit(1);
    }
    int expected_data_len = sizeof(buffer);
    vector<char> file_data;
    while (true) {
        //Nadav -------------------------------------------------------
        long int read_bytes = recv(clientSocket, buffer, expected_data_len, 0);
        if (read_bytes == 0) {
            // connection is closed
            perror("Error the connection with the server is closed");
            exit(1);
        }
        else if (read_bytes < 0) {
            perror("Error with reading the data from the server");
            exit(1);
        }
        if (check_done(buffer, read_bytes)) {
            // clean the buffer
            memset(buffer, 0, read_bytes);
            break;
        } else {
            //copy the buffer to the vector
            file_data.insert(file_data.end(), buffer, buffer + read_bytes);
            memset(buffer, 0, read_bytes);
        }
    }
    //classfied the vector.
    classifiedVector(file_data);
    //TODO: print the values of values->classifiedVector to see if it works.


    // send the upload complete and the test string to the client
    data_len = uploadComplete1String.length() + 1;
    char data_addrTwo[data_len];
    str = uploadComplete1String.c_str();
    // copy the data to the char array
    strcpy(data_addrTwo, str);
    // send the string to the server
    sent_bytes = send(clientSocket, data_addrTwo, data_len, 0);
    if (sent_bytes < 0) {
        perror("Error sending the data to the client");
        exit(1);
    }

    file_data.clear();
    while (true) {
        long int read_bytes = recv(clientSocket, buffer, expected_data_len, 0);
        if (read_bytes == 0) {
            // connection is closed
            perror("Error the connection with the server is closed");
            exit(1);
        }
        else if (read_bytes < 0) {
            perror("Error with reading the data from the server");
            exit(1);
        }
        if (check_done(buffer, read_bytes)) {
            // clean the buffer
            memset(buffer, 0, read_bytes);
            break;
        } else {
            //copy the buffer to the vector
            file_data.insert(file_data.end(), buffer, buffer + read_bytes);
            memset(buffer, 0, read_bytes);
        }
    }
    //put the vectors in the Unclassfied vector of values.
    notClassifiedVector(file_data);
    //TODO: print the values of values->notclassifiedVector to see if it works.

    // send the upload complete string to the client
    data_len = uploadComplete2String.length() + 1;
    char data_addrThree[data_len];
    str = uploadComplete2String.c_str();
    // copy the data to the char array
    strcpy(data_addrThree, str);
    // send the string to the server
    sent_bytes = send(clientSocket, data_addrThree, data_len, 0);
    if (sent_bytes < 0) {
        perror("Error sending the data to the client");
        exit(1);
    }
}

/**
 * this function returns the description of this command in the menu
 * @return the description of this command in the menu
 */
string UploadCommand::description() {
    return "1. upload an unclassified csv data file\n";
}

/**
 * the constructor of UploadCommand
 * @param socket - the socket of the client
 * @param valuesCopy - values object
 */
UploadCommand::UploadCommand(int socket, Values *valuesCopy) {
    values = valuesCopy;
    valuesCopy->setSocket(socket);
}