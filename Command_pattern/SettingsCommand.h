#ifndef ADVANCEDPROGRAMINGPART3_SETTINGSCOMMAND_H
#define ADVANCEDPROGRAMINGPART3_SETTINGSCOMMAND_H

#include "Command.h"

class SettingsCommand : public Command
{
public:
    explicit SettingsCommand(int socket, Values *value);
    string description();
    void execute();
    void sendData(string s, int clientSock);
};

#endif //ADVANCEDPROGRAMINGPART3_SETTINGSCOMMAND_H