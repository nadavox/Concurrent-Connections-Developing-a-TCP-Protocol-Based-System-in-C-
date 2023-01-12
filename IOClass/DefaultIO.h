#ifndef ADVANCEDPROGRAMINGPART3_DEFAULTIO_H
#define ADVANCEDPROGRAMINGPART3_DEFAULTIO_H

#include "iostream"
#include <sstream>
#include <string.h>
#include <sys/socket.h>

using namespace std;

class DefaultIO {
public:
    virtual string readInput() = 0;
    virtual void writeInput(string s) = 0;
    //virtual ~DefaultIO() = 0;
};

#endif //ADVANCEDPROGRAMINGPART3_DEFAULTIO_H
