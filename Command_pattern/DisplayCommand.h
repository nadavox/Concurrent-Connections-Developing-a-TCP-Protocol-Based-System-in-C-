#ifndef ADVANCEDPROGRAMINGPART3_DISPLAYCOMMAND_H
#define ADVANCEDPROGRAMINGPART3_DISPLAYCOMMAND_H

#include "Command.h"

class DisplayCommand : public Command
{
public:
    explicit DisplayCommand(int socket, Values *value, DefaultIO *dio);
    string description();
    void execute();
};

#endif //ADVANCEDPROGRAMINGPART3_DISPLAYCOMMAND_H