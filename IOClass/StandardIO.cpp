#include "StandardIO.h"

/**
 * this function reads from cin
 */
string StandardIO::readInput() {
    string s;
    cin >> s;
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
    return s;
}

/**
 * this function writes to cout
 * @param s - the string
 */
void StandardIO::writeInput(std::string s) {
    cout << s;
}