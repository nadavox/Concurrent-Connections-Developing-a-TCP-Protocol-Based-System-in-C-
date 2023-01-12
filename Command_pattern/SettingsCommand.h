#ifndef ADVANCEDPROGRAMINGPART3_SETTINGSCOMMAND_H
#define ADVANCEDPROGRAMINGPART3_SETTINGSCOMMAND_H

#include "Command.h"

class SettingsCommand : public Command
{
public:
    explicit SettingsCommand(int socket, Values *value);
    string description();
    void execute();
};

#endif //ADVANCEDPROGRAMINGPART3_SETTINGSCOMMAND_H