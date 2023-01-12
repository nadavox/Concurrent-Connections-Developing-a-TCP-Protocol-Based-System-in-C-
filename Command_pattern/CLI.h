#ifndef ADVANCEDPROGRAMINGPART3_CLI_H
#define ADVANCEDPROGRAMINGPART3_CLI_H

#include <map>
#include "Command.h"
#include <cstring>
#include <sys/socket.h>
#include "UploadCommand.h"
#include "SettingsCommand.h"
#include "ClassifyCommand.h"
#include "DisplayCommand.h"
#include "DownloadCommand.h"
#include "ExitCommand.h"
#include "values.h"

class CLI
{
private:
    map<string, Command*> commands;
    int socketNumber;
public:
    CLI(int socketNumber, Values *v);
    void start();
    void executeCommand(string s);
    virtual ~CLI();
};

#endif //ADVANCEDPROGRAMINGPART3_CLI_H
