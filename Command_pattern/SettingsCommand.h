#ifndef ADVANCEDPROGRAMINGPART3_SETTINGSCOMMAND_H
#define ADVANCEDPROGRAMINGPART3_SETTINGSCOMMAND_H

#include "Command.h"

class SettingsCommand : public Command
{
public:
    string description();
    void execute();
};

#endif //ADVANCEDPROGRAMINGPART3_SETTINGSCOMMAND_H