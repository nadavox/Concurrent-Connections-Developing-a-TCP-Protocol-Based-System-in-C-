#ifndef ADVANCEDPROGRAMINGPART3_DOWNLOADCOMMAND_H
#define ADVANCEDPROGRAMINGPART3_DOWNLOADCOMMAND_H

#include "Command.h"

class DownloadCommand : public Command
{
public:
    string description();
    void execute();
};

#endif //ADVANCEDPROGRAMINGPART3_DOWNLOADCOMMAND_H