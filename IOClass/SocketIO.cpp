#include "SocketIO.h"
#include <string.h>

/**
 * the constructor of SocketIO
 * @param sockNumber - the socket number of whom we want connection
 */
SocketIO::SocketIO(int sockNumber) {
    this->sockNumber = sockNumber;
}

/**
 * this function reads from the socket
 */
string SocketIO::readInput() {
    char buffer[1024];
    memset(buffer, 0, 1024);
    long int read_bytes = recv(sockNumber, buffer, sizeof(buffer), 0);
    if (read_bytes == 0) {
        // connection is closed
        perror("Error the connection with the server is closed");
    }
    else if (read_bytes < 0) {
        perror("Error with reading the data from the server");
    }
    string input;
    input.assign(buffer);
    return input;
}


/**
 * this function writes to the socket
 * @param s - the string
 */
void SocketIO::writeInput(string s) {
    unsigned int data_len = s.length();
    char data_addr[data_len + 1];
    const char* str = s.c_str();
    // copy the data of the string
    strcpy(data_addr, str);
    long int n;
    n = send(sockNumber, data_addr, data_len, 0);
    if (n < 0) {
        perror("Error sending the data to the socket");
    }
}