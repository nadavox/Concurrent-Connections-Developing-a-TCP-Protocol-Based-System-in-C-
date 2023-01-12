#ifndef ADVANCEDPROGRAMINGPART3_STANDARDIO_H
#define ADVANCEDPROGRAMINGPART3_STANDARDIO_H

#include "DefaultIO.h"

class StandardIO : public DefaultIO {
public:
    string readInput();
    void writeInput(string s);
    ~StandardIO() {}
};

#endif //ADVANCEDPROGRAMINGPART3_STANDARDIO_H
