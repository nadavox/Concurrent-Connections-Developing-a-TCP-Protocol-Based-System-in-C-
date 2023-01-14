#include "SocketIO.h"
#include <unistd.h>
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
    memset(buffer, 0, sizeof(buffer));
    long int n = recv(sockNumber, buffer, sizeof(buffer), 0);
    if (n < 0){
        perror("Error reading from the socket");
    }
    return buffer;
}


/**
 * this function writes to the socket
 * @param s - the string
 */
void SocketIO::writeInput(string s) {
    unsigned int data_len = s.length();
    char data_addr[data_len + 1];
    const char* str = s.c_str();
    // copy the data of the vector, distance function name and k to char array
    strcpy(data_addr, str);
    long int n;
    n = send(sockNumber, data_addr, data_len, 0);
    if (n < 0) {
        perror("Error writing to the socket");
    }
}