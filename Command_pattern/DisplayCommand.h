#ifndef ADVANCEDPROGRAMINGPART3_DISPLAYCOMMAND_H
#define ADVANCEDPROGRAMINGPART3_DISPLAYCOMMAND_H

#include "Command.h"

class DisplayCommand : public Command
{
public:
    string description();
    void execute();
};

#endif //ADVANCEDPROGRAMINGPART3_DISPLAYCOMMAND_H