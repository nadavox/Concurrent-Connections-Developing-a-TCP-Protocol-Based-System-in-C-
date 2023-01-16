#include "SocketIO.h"
#include <string.h>

/**
 * the constructor of SocketIO
 * @param sockNumber - the socket number of whom we want connection
 */
SocketIO::SocketIO(int sockNumber) {
    this->sockNumber = sockNumber;
}


// converts character array
// to string and returns it
string convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}


/**
 * this function reads from the socket
 */
string SocketIO::readInput() {
    string input;
    char buffer[1024];
    memset(buffer, 0, 1024);
    long int read_bytes = recv(sockNumber, buffer, sizeof(buffer), 0);
    if (read_bytes == 0) {
        // connection is closed
        perror("Error the connection with the server is closed");
        input = "Error";
    }
    else if (read_bytes < 0) {
        perror("Error with reading the data from the server");
        input = "Error";
    } else {
        input = convertToString(buffer, read_bytes);
    }
    return input;
}


/**
 * this function writes to the socket
 * @param s - the string
 */
void SocketIO::writeInput(string s) {
    if (s.empty()) {
        char data_addr[1] = {'\n'};
        long int n = send(sockNumber, data_addr, 1, 0);
        if (n < 0) {
            perror("Error sending the data to the socket");
        }
    } else {
        unsigned int data_len = s.length();
        char data_addr[data_len + 1];
        const char* str = s.c_str();
        // copy the data of the string
        strcpy(data_addr, str);
        long int n = send(sockNumber, data_addr, data_len, 0);
        if (n < 0) {
            perror("Error sending the data to the socket");
        }
    }
}