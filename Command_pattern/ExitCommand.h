#ifndef ADVANCEDPROGRAMINGPART3_EXITCOMMAND_H
#define ADVANCEDPROGRAMINGPART3_EXITCOMMAND_H

#include "Command.h"

class ExitCommand : public Command
{
public:
    explicit ExitCommand(int socket, Values *value, DefaultIO *dio);
    string description();
    void execute();
};

#endif //ADVANCEDPROGRAMINGPART3_EXITCOMMAND_H