#include <iostream>
#include "SettingsCommand.h"
#include <sys/socket.h>
#include <cstring>
#include <sstream>
#include <thread>

using namespace std;

/**
 * this function will send the client to current values of k and the distance function name, and will update
 * this values according to the user.
 * if the new values are not valid - will send following message to the client.
 */
void SettingsCommand::execute()
{
    //the client socket
    int clientSocket = values->getSocket();
    char buffer[256];
    string currentParametersString = "The current KNN parameters are: K = " + to_string(values->getK()) +
            ", distance metric = " + values->getDistanceMetric() + "\n";

    // send the train string to the client
    unsigned int data_len = currentParametersString.length();
    char data_addr[data_len + 1];
    const char* str = currentParametersString.c_str();
    // copy the data of the vector, distance function name and k to char array
    strcpy(data_addr, str);
    // send the full sentence to the server
    cout <<"sending the option to the user" << endl;
   long int sent_bytes = send(clientSocket, data_addr, data_len, 0);
   cout << "send successfully" << endl;
    if (sent_bytes < 0) {
        perror("Error sending the data to the client");
        exit(1);
    }

    int expected_data_len = sizeof(buffer);
    // clean the buffer
    memset(buffer, 0, sizeof(buffer));
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

    string s(buffer);
    string s1, s2;
    if (s != "done") {
        // the user want to update the parameters
        istringstream iss(s);
        // the k
        iss >> s1;
        // the distance metric
        iss >> s2;
        // check if s1 is valid int
        try {
            // s1 is an integer number
            int k = stoi(s1);
            // k is negative integer
            if (k <= 0) {
                // check if s2 is valid
                if (s2 != "AUC" && s2 != "MAN" && s2 != "CHB" && s2 != "CAN" && s2 != "MIN") {
                    // send message that k and the metric is not valid to the client
                    string kAndMetricNotValidString = "invalid value for K\ninvalid value for metric\n";
                    // send message that one parameter is not valid to the client
                    data_len = kAndMetricNotValidString.length();
                    data_addr[data_len + 1];
                    str = kAndMetricNotValidString.c_str();
                    // copy the data of the vector, distance function name and k to char array
                    strcpy(data_addr, str);
                    // send the full sentence to the server
                    sent_bytes = send(clientSocket, data_addr, data_len, 0);
                    if (sent_bytes < 0) {
                        perror("Error sending the data to the client");
                        exit(1);
                    }
                }
                // only k is not valid
                else {
                    // send message that k is not valid to the client
                    string kNotValidString = "invalid value for K\n";
                    // send message that one parameter is not valid to the client
                    data_len = kNotValidString.length();
                    data_addr[data_len + 1];
                    str = kNotValidString.c_str();
                    // copy the data of the vector, distance function name and k to char array
                    strcpy(data_addr, str);
                    // send the full sentence to the server
                    sent_bytes = send(clientSocket, data_addr, data_len, 0);
                    if (sent_bytes < 0) {
                        perror("Error sending the data to the client");
                        exit(1);
                    }
                }
            }
            // k is a positive integer
            else {
                // check if s2 is valid
                if (s2 != "AUC" && s2 != "MAN" && s2 != "CHB" && s2 != "CAN" && s2 != "MIN") {
                    // send message that the distance metric is not valid to the client
                    string metricNotValidString = "invalid value for metric\n";
                    // send message that one parameter is not valid to the client
                    data_len = metricNotValidString.length();
                    data_addr[data_len + 1];
                    str = metricNotValidString.c_str();
                    // copy the data of the vector, distance function name and k to char array
                    strcpy(data_addr, str);
                    // send the full sentence to the server
                    sent_bytes = send(clientSocket, data_addr, data_len, 0);
                    if (sent_bytes < 0) {
                        perror("Error sending the data to the client");
                        exit(1);
                    }
                }
                // update distance metric
                else {
                    // update k
                    values->setK(k);
                    // update the distance metric
                    values->setDistanceMetric(s2);
                    // send message that everything okay
                    string valid = "input is valid";
                    // send message that one parameter is not valid to the client
                    data_len = valid.length();
                    data_addr[data_len + 1];
                    str = valid.c_str();
                    // copy the data of the vector, distance function name and k to char array
                    strcpy(data_addr, str);
                    // send the full sentence to the server
                    sent_bytes = send(clientSocket, data_addr, data_len, 0);
                    if (sent_bytes < 0) {
                        perror("Error sending the data to the client");
                        exit(1);
                    }
                    this_thread::sleep_for(chrono::milliseconds(50));
                }
            }
        }
        // s1 is not valid k
        catch (invalid_argument) {
            // check if s2 is valid
            if (s2 != "AUC" && s2 != "MAN" && s2 != "CHB" && s2 != "CAN" && s2 != "MIN") {
                // send message that k and the metric is not valid to the client
                string kAndMetricNotValidString = "invalid value for K\ninvalid value for metric\n";
                // send message that one parameter is not valid to the client
                data_len = kAndMetricNotValidString.length();
                data_addr[data_len + 1];
                str = kAndMetricNotValidString.c_str();
                // copy the data of the vector, distance function name and k to char array
                strcpy(data_addr, str);
                // send the full sentence to the server
                sent_bytes = send(clientSocket, data_addr, data_len, 0);
                if (sent_bytes < 0) {
                    perror("Error sending the data to the client");
                    exit(1);
                }
            }
            // the distance metric is valid
            else {
                // send message that k is not valid to the client
                string kNotValidString = "invalid value for K\n";
                // send message that one parameter is not valid to the client
                data_len = kNotValidString.length();
                data_addr[data_len + 1];
                str = kNotValidString.c_str();
                // copy the data of the vector, distance function name and k to char array
                strcpy(data_addr, str);
                // send the full sentence to the server
                sent_bytes = send(clientSocket, data_addr, data_len, 0);
                if (sent_bytes < 0) {
                    perror("Error sending the data to the client");
                    exit(1);
                }
            }
        }
    }
}

/**
 * the function returns it's description in the menu
 * @return it's description in the menu
 */
string SettingsCommand::description() {
    return "2. algorithm settings\n";
}

/**
 * the constructor of UploadCommand
 * @param socket - the socket of the client
 * @param valuesCopy - values object
 */
SettingsCommand::SettingsCommand(int socket, Values *valuesCopy) {
    values = valuesCopy;
    valuesCopy->setSocket(socket);
}
