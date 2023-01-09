#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "vector"
#include "IOClass.h"

using namespace std;

/**
 * the function check if string is a double number
 * @param s - the string
 * @return true is the string is double number, false if the string is not a double number
 */
bool isDoubleNumber(const string& s) {
    // the user didn't insert anything
    if (s.empty()) {
        return false;
    }

    // Check for a negative sign at the beginning of the string
    bool negative = false;
    if (s[0] == '-') {
        negative = true;
    }

    // Check for a decimal point
    bool decimal = false;
    int numDigits = 0;
    for (int i = (negative ? 1 : 0); i < s.size(); i++) {
        if (s[i] == '.') {
            if (decimal || numDigits == 0) {
                // There can only be one decimal point, and it must not be the first character
                return false;
            }
            decimal = true;
        } else if (s[i] == 'e' || s[i] == 'E') {
            // Check for scientific notation
            if (i == s.size() - 1) {
                // The 'e' must not be the last character
                return false;
            }
            if (s[i + 1] == '+' || s[i + 1] == '-') {
                // The 'e' must be followed by a sign
                i++;
            }
            numDigits = 0;
        } else if (!isdigit(s[i])) {
            // Any character that is not a digit, decimal point, or 'e' is invalid
            return false;
        } else {
            numDigits++;
        }
    }

    // A number must have at least one digit
    return numDigits > 0;
}

/**
 * the function check if string is an unsigned integer number
 * @param s - the string
 * @return true if the string is an unsigned integer number or false if the string is not unsigned integer number
 */
bool isUnsignedIntegerNumber(const string& s) {
    // the user didn't insert anything
    if (s.empty()) {
        return false;
    }
    int sLength = s.length();
    for (int i = 0; i < sLength; ++i) {
        // check is the char is digital number
        if(!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

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
void receiveData(int sock) {
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
    else {
        //create ioClass for input and output.
        IOClass io(cin, cout);
        io.write(buffer);
    }
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
    vector<double> userVector;
    // get input from the user infinitely
    while (true) {
        string distanceName, fullSentence;
        long k = -1;
        while (cin) {
            // if the input has space in it so ignore
            while (cin.peek() == ' ') {
                cin.ignore();
            }
            // if the input has enter key in it so ignore
            if (cin.peek() == '\n') {
                break;
            }
            // get the distance function name and the k from the user
            if (isalpha(cin.peek())) {
                // get the distance function name
                cin >> distanceName;
                fullSentence.append(distanceName);
                fullSentence.append(" ");
                // remove spaces from cin
                while (cin.peek() == ' ') {
                    cin.ignore();
                }
                // there is a string after the distance function name
                if (cin.peek() != '\n') {
                    // get the k
                    string s;
                    cin >> s;
                    // check if k is an unsigned number
                    if (isUnsignedIntegerNumber(s)) {
                        k = stoi(s);
                        fullSentence.append(to_string(k));
                    }
                    //  k is not an unsigned number
                    else {
                        break;
                    }
                }
                break;
            }
            // puts the number in the first vector
            else {
                string number;
                cin >> number;
                // check if the string is a number
                if (isDoubleNumber(number)) {
                    // it is a number
                    userVector.push_back(stod(number));
                    fullSentence.append(number);
                    fullSentence.append(" ");
                }
                // check if the string is not a number
                else {
                    userVector.clear();
                    break;
                }
            }
        }
        // remove spaces from cin
        while (cin.peek() == ' ') {
            cin.ignore();
        }
        if (userVector.empty()) {
            cout << "invalid input" << endl;
            clearCin();
            cin.ignore();
            userVector.clear();
            continue;
        }
        // the user want to close the connection to the server
        else if (distanceName.empty() && k == -1 && userVector.at(0) == -1 && userVector.size() == 1) {
            // close connection
            close(sock);
            break;
        }
        // invalid input
        if (cin.peek() != '\n' || (distanceName != "AUC" && distanceName != "MAN" &&
                distanceName != "CHB" && distanceName != "CAN" && distanceName != "MIN") || k <= 0) {
            cout << "invalid input" << endl;
            clearCin();
            cin.ignore();
            userVector.clear();
            continue;
        }

        cin.ignore();
        // if the string is bigger than buffer. invalid input.
        if (fullSentence.size() < 4096) {
            // send the vector, distance function name and k to the server
            sendData(sock, fullSentence);
            // get data from the server and write it to the output stream
            receiveData(sock);
        } else {
            cout << "invalid input" << endl;
        }
        userVector.clear();
    }
    return 0;
}
