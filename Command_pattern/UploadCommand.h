#ifndef ADVANCEDPROGRAMINGPART3_UPLOADCOMMAND_H
#define ADVANCEDPROGRAMINGPART3_UPLOADCOMMAND_H

#include "Command.h"

class UploadCommand : public Command
{
public:
    UploadCommand(int socket) : Command(socket) {
    }
    string description() override;
    void execute() override;
};

#endif //ADVANCEDPROGRAMINGPART3_UPLOADCOMMAND_H