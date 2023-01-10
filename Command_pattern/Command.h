#ifndef ADVANCEDPROGRAMINGPART3_COMMAND_H
#define ADVANCEDPROGRAMINGPART3_COMMAND_H

#include <string>
#include <vector>
#include "../Values.h"

using namespace std;

// Command interface
class Command
{
protected:
    Values *values;
public:
    virtual string description() = 0;
    virtual void execute() = 0;
};


#endif //ADVANCEDPROGRAMINGPART3_COMMAND_H