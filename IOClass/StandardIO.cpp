#include "StandardIO.h"

/**
 * this function reads from cin
 */
string StandardIO::readInput() {
    cout << "in readInput" << endl;
    string s;
    cin >> s;
    cout << "after cin" << endl;
    string trash;
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