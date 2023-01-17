#ifndef ADVANCEDPROGRAMINGPART3_COMMAND_H
#define ADVANCEDPROGRAMINGPART3_COMMAND_H

#include <string>
#include <vector>
#include "../Values.h"
#include "../IOClass/DefaultIO.h"

using namespace std;

// Command interface
class Command
{
protected:
    Values *values;
    DefaultIO *dio;
public:
    virtual string description() = 0;
    virtual void execute() = 0;
    virtual ~Command();
};

#endif //ADVANCEDPROGRAMINGPART3_COMMAND_H