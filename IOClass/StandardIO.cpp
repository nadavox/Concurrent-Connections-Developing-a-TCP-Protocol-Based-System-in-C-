#include "StandardIO.h"

/**
 * this function reads from cin
 */
string StandardIO::readInput() {
    string s, newString = "";
    getline(cin, s);
    int i;
    bool seenFirstWord = false;
    // ignore unnecessary spaces
    for (i = 0; i < s.size(); i++) {
        if (!seenFirstWord && s[i] == ' ') {
            continue;
        }
        if ((i == s.size() - 1) && s[i] == ' ') {
            continue;
        }
        if (seenFirstWord && s[i] == ' ') {
            if (s[i + 1] == ' ') {
                continue;
            } else {
                s += s[i];
            }
        }
        seenFirstWord = true;
        newString += s[i];
    }
    return newString;
}

/**
 * this function writes to cout
 * @param s - the string
 */
void StandardIO::writeInput(std::string s) {
    cout << s;
}