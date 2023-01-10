#include "StandardIO.h"

/**
 * this function reads from cin
 */
string StandardIO::readInput() {
    string s;
    cin >> s;
    cin.clear();
    return s;
}

/**
 * this function writes to cout
 * @param s - the string
 */
void StandardIO::writeInput(std::string s) {
    cout << s;
}