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
    memset(buffer, 0, 1024);
    long int n = recv(sockNumber, buffer, sizeof(buffer), 0);
    //cout << "n read: " << n << endl;
    if (n < 0){
        perror("Error reading from the socket");
    }
    string input(buffer, n);
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
    // copy the data of the vector, distance function name and k to char array
    strcpy(data_addr, str);
    long int n;
    n = send(sockNumber, data_addr, data_len, 0);
    //cout << "n write: " << n << endl;
    if (n < 0) {
        perror("Error writing to the socket");
    }
}