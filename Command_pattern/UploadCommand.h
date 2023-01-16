#ifndef ADVANCEDPROGRAMINGPART3_UPLOADCOMMAND_H
#define ADVANCEDPROGRAMINGPART3_UPLOADCOMMAND_H

#include "Command.h"

class UploadCommand : public Command
{
public:
    explicit UploadCommand(int socket, Values *value, DefaultIO *dio);
    string description();
    void execute();
    string classifiedVector(const vector<char>& dataVector);
    string notClassifiedVector(const vector<char>& dataVector);
    bool check_input_is_invalid(const string &output, Values *values);
};

#endif //ADVANCEDPROGRAMINGPART3_UPLOADCOMMAND_H