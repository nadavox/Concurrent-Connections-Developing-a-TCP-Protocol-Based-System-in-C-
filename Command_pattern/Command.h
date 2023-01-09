#ifndef ADVANCEDPROGRAMINGPART3_COMMAND_H
#define ADVANCEDPROGRAMINGPART3_COMMAND_H

#include <string>

using namespace std;

// Command interface
class Command
{
public:
    virtual void execute() = 0;
};


#endif //ADVANCEDPROGRAMINGPART3_COMMAND_H