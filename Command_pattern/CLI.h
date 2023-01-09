#ifndef ADVANCEDPROGRAMINGPART3_CLI_H
#define ADVANCEDPROGRAMINGPART3_CLI_H

#include <unordered_map>
#include "Command.h"

class CLI
{
private:
    unordered_map<string, Command*> commands;

public:
    CLI();
    void execute_command(string command_name);
};

#endif //ADVANCEDPROGRAMINGPART3_CLI_H
