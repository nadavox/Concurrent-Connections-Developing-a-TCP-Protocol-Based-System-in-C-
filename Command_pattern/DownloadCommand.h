#ifndef ADVANCEDPROGRAMINGPART3_DOWNLOADCOMMAND_H
#define ADVANCEDPROGRAMINGPART3_DOWNLOADCOMMAND_H

#include "Command.h"

class DownloadCommand : public Command
{
private:
    int sock;
public:
    explicit DownloadCommand(int socket, Values *value, DefaultIO *dio);
    string description();
    void execute();
};

#endif //ADVANCEDPROGRAMINGPART3_DOWNLOADCOMMAND_H