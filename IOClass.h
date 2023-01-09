#ifndef ADVANCEDPROGRAMINGPART2_IOCLASS_H
#define ADVANCEDPROGRAMINGPART2_IOCLASS_H
#include "iostream"
#include <vector>
#include <sstream>
#include <regex>

using namespace std;

class IOClass {
public:
    istream &input;
    ostream &output;
    IOClass(istream &in, ostream &out) : input(in), output(out) {};
    vector<pair<vector<double>, string> >* readInput();
    void write(string s);
};
#endif //ADVANCEDPROGRAMINGPART2_IOCLASS_H