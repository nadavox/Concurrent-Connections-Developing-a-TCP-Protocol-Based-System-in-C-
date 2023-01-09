#include "IOClass.h"

/**
 * this function reads from the input stream
 * @return vector the contains a pair of string and vector
 */
vector<pair<vector<double>, string> >* IOClass::readInput() {
    // read the lines from the file
    vector<pair<vector<double>, string> >* vectorsList = new vector<pair<vector<double>, string> >;
    vector<double> v;
    string tempString;
    // line will contain each line from the file
    string line = "";
    int size = 0;
    // gets lines from file
    while (getline(input, line)) {
        // insert the line to string stream
        stringstream inputString(line);
        // get words/numbers from the current line seperates by comma
        while (getline(inputString, tempString, ',')) {
            try {
                // Return false if the string is empty
                if (tempString.empty()) throw bool (false);
                // Keep track of whether we've seen a decimal point, sign or e/E
                bool decimal_point_seen = false;
                bool sign_seen = false;
                bool eE_seen = false;
                // Iterate through the characters in the string
                int i = 0;
                for (; i < tempString.length(); i++) {
                    // if the character is a digit so check the next character
                    if (isdigit(tempString[i])) continue;
                    // if the character is a decimal point so check the next character
                    if (tempString[i] == '.' && !decimal_point_seen) {
                        decimal_point_seen = true;
                        continue;
                    }
                    // if the character is a sign so check the next character
                    if ((tempString[i] == '+' || tempString[i] == '-') && !sign_seen) {
                        sign_seen = true;
                        continue;
                    }
                    // Check if the character is E or e
                    if ((tempString[i] == 'e' || tempString[i] == 'E') && !eE_seen) {
                        eE_seen = true;
                        // check if the E/e is representing a number or just a string
                        if (i < tempString.length() -2 ) {
                            i = i + 1;
                            // if what comes after the e/E is - or +
                            if ((tempString[i] == '+' || tempString[i] == '-')) {
                                i = i + 1;
                                // if what comes after the +/- is a number so it's okay
                                if (isdigit(tempString[i])) {
                                    continue;
                                }
                            }
                        }
                    }
                    // If none of the above conditions are true, the string is not a number
                    throw bool (false);
                }
                // If we've reached this point, the string is a number
                v.push_back(atof(tempString.c_str()));
            }
            catch (bool notNumber){
                // get the size of the first vector in the file
                if (vectorsList->empty()) {
                    size = v.size();
                }
                // if there is a vector in the file which is not valid so end the program
                if (v.size() != size) {
                    return vectorsList = nullptr;
                }
                //add the vector to vector list.
                vectorsList->push_back(make_pair(v, tempString.c_str()));
                // there are more input in the line
                if (getline(inputString, tempString, ',')) {
                    return vectorsList = nullptr;
                }
            }
        }
        //clear the vector for next vector.
        v.clear();
    }
    return vectorsList;
}

/**
 * this function writes to the output stream
 * @param s - the string
 */
void IOClass::write(string s) {
    output << s << endl;
}