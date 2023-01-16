#include <iostream>
#include "SettingsCommand.h"
#include <cstring>
#include <thread>

using namespace std;

/**
 * this function will send the client to current values of k and the distance function name, and will update
 * this values according to the user.
 * if the new values are not valid - will send following message to the client.
 */
void SettingsCommand::execute()
{
    char buffer[256];
    // clean the buffer
    memset(buffer, 0, sizeof(buffer));
    string currentParametersString = "The current KNN parameters are: K = " + to_string(values->getK()) +
            ", distance metric = " + values->getDistanceMetric() + "\n";

    this->dio->writeInput(currentParametersString);


    string input;
    //read what the client response
    input = this->dio->readInput();
    // exit the function. the client lost connection
    if (input == "Error") {
        return;
    }
    strcpy(buffer, input.c_str());

    string s(buffer);
    string s1, s2;
    // the user want to update the parameters
    if (s != "done") {
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
                    this->dio->writeInput(kAndMetricNotValidString);
                    // read message that the user get the message
                    input = this->dio->readInput();
                    // exit the function. the client lost connection
                    if (input == "Error") {
                        return;
                    }
                }
                // only k is not valid
                else {
                    // send message that k is not valid to the client
                    string kNotValidString = "invalid value for K\n";
                    this->dio->writeInput(kNotValidString);
                    // read message that the user get the message
                    input = this->dio->readInput();
                    // exit the function. the client lost connection
                    if (input == "Error") {
                        return;
                    }
                }
            }
            // k is a positive integer
            else {
                // check if s2 is valid
                if (s2 != "AUC" && s2 != "MAN" && s2 != "CHB" && s2 != "CAN" && s2 != "MIN") {
                    // send message that the distance metric is not valid to the client
                    string metricNotValidString = "invalid value for metric\n";
                    this->dio->writeInput(metricNotValidString);
                    // read message that the user get the message
                    input = this->dio->readInput();
                    // exit the function. the client lost connection
                    if (input == "Error") {
                        return;
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
                    this->dio->writeInput(valid);
                }
            }
        }
        // s1 is not valid k
        catch (invalid_argument) {
            // check if s2 is valid
            if (s2 != "AUC" && s2 != "MAN" && s2 != "CHB" && s2 != "CAN" && s2 != "MIN") {
                // send message that k and the metric is not valid to the client
                string kAndMetricNotValidString = "invalid value for K\ninvalid value for metric\n";
                this->dio->writeInput(kAndMetricNotValidString);
                // read message that the user get the message
                input = this->dio->readInput();
                // exit the function. the client lost connection
                if (input == "Error") {
                    return;
                }
            }
            // the distance metric is valid
            else {
                // send message that k is not valid to the client
                string kNotValidString = "invalid value for K\n";
                this->dio->writeInput(kNotValidString);
                // read message that the user get the message
                input = this->dio->readInput();
                // exit the function. the client lost connection
                if (input == "Error") {
                    return;
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
 * @param dio - pointer to DefaultIO object
 */
SettingsCommand::SettingsCommand(int socket, Values *valuesCopy, DefaultIO *dio) {
    values = valuesCopy;
    valuesCopy->setClientSocket(socket);
    this->dio = dio;
}