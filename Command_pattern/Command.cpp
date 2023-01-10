// Command.cpp
#include "Command.h"
bool Command::exist = false;
int Command::k;

string Command::description()
{
    return "This is a command abstract class.";
}

void Command::execute()
{
    // Default implementation of the execute function
}

void Command::makeFalse() {
    exist = false;
}

void Command::init(int number) {
    if (!exist) {
        k = 5;
        distance_metric = "EUC";
        classfiedVectorList = vector<pair< vector<double>, string > >();
        notClassfiedVectorList = vector<pair< vector<double>, string > >();
        socket = number;
        exist = true;
    }
}




