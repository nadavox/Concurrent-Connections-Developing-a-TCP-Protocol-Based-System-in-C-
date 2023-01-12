#include "StandardIO.h"

/**
 * this function reads from cin
 */
string StandardIO::readInput() {
    string s;
    cin >> s;
    // clean the buffer
    cin.ignore();
    return s;
}

/**
 * this function writes to cout
 * @param s - the string
 */
void StandardIO::writeInput(std::string s) {
    cout << s;
}