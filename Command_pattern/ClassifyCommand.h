#ifndef ADVANCEDPROGRAMINGPART3_CLASSIFYCOMMAND_H
#define ADVANCEDPROGRAMINGPART3_CLASSIFYCOMMAND_H

#include "Command.h"

class ClassifyCommand : public Command {
public:
    string description();
    void execute();
    ClassifyCommand(int socket, Values *valuesCopy, DefaultIO *dio);
};

#endif //ADVANCEDPROGRAMINGPART3_CLASSIFYCOMMAND_H