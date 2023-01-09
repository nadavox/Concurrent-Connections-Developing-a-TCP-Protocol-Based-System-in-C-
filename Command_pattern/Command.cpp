// Command.cpp
#include "Command.h"

Command::Command(int num)
        : k(5), distance_metric("EUC"),
        classfiedVectorList(),
        notClassfiedVectorList(),
        tempBuffer(), socket(num)
{
}

string Command::description()
{
    return "This is a command abstract class.";
}

void Command::execute()
{
    // Default implementation of the execute function
}
