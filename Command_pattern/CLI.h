#ifndef ADVANCEDPROGRAMINGPART3_CLI_H
#define ADVANCEDPROGRAMINGPART3_CLI_H

#include <map>
#include "Command.h"
#include <cstring>
#include <sys/socket.h>

class CLI
{
private:
    map<string, Command*> commands;
    int socketNumber;
public:

    CLI(Command* uc, Command* sc, Command* cc, Command* dyc, Command* ddc, Command* ec, int socketNumber);
    void start();
};

#endif //ADVANCEDPROGRAMINGPART3_CLI_H
