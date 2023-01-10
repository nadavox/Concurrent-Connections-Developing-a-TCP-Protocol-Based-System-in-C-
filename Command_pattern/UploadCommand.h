#ifndef ADVANCEDPROGRAMINGPART3_UPLOADCOMMAND_H
#define ADVANCEDPROGRAMINGPART3_UPLOADCOMMAND_H

#include "Command.h"

class UploadCommand : public Command
{
public:
    explicit UploadCommand(int socket);
    string description();
    void execute();
};

#endif //ADVANCEDPROGRAMINGPART3_UPLOADCOMMAND_H