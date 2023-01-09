#ifndef ADVANCEDPROGRAMINGPART3_SOCKETIO_H
#define ADVANCEDPROGRAMINGPART3_SOCKETIO_H

#include "DefaultIO.h"

class SocketIO : public DefaultIO {
private:
    int sockNumber;
public:
    SocketIO(int sockNumber);
    string readInput();
    void writeInput(string s);
};

#endif //ADVANCEDPROGRAMINGPART3_SOCKETIO_H
