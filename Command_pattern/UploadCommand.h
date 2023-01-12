#ifndef ADVANCEDPROGRAMINGPART3_UPLOADCOMMAND_H
#define ADVANCEDPROGRAMINGPART3_UPLOADCOMMAND_H

#include "Command.h"

class UploadCommand : public Command
{
public:
    explicit UploadCommand(int socket, Values *value);
    string description();
    void execute();
    void classifiedVector(const string& dataVector);
    void notClassifiedVector(const string &dataVector);
};

#endif //ADVANCEDPROGRAMINGPART3_UPLOADCOMMAND_H