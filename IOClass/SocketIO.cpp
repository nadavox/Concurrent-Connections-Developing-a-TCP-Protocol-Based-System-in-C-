#include "SocketIO.h"
#include <string.h>


void printStringWithSpecialChars(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '\0') {
            cout << "\\0";
        } else if (s[i] == '\n') {
            cout << "\\n";
        } else {
            cout << s[i];
        }
    }
    cout << endl;
}

/**
 * the constructor of SocketIO
 * @param sockNumber - the socket number of whom we want connection
 */
SocketIO::SocketIO(int sockNumber) {
    this->sockNumber = sockNumber;
}

/**
 * this function converts character array to string
 * @param a - the character array
 * @param size - the size of the array
 * @return the string
 */
string convertToString(char* a, int size)
{
    int i;
    string s = "";
    bool seenFirstWord = false;
    // ignore unnecessary spaces
    for (i = 0; i < size; i++) {
        if (a[i] == '\0') {
            continue;
        }
        if (!isascii(a[i])) {
            continue;
        }
        if (!seenFirstWord && a[i] == ' ') {
            continue;
        }
        if ((i == size - 1) && a[i] == ' ') {
            continue;
        }
        seenFirstWord = true;
        s += a[i];
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
    long int read_bytes = recv(sockNumber, buffer, 1024, 0);
    //cout << read_bytes << endl;
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
        unsigned int data_len = s.size();
        char data_addr[data_len + 1];
        memset(data_addr, 0, sizeof(data_addr));
        const char* str = s.c_str();
        // copy the data of the string
        strcpy(data_addr, str);
        cout << "data_addr: " << data_addr << endl;
        long int n = send(sockNumber, data_addr, data_len, 0);
        if (n < 0) {
            perror("Error sending the data to the socket");
        }
    }
}