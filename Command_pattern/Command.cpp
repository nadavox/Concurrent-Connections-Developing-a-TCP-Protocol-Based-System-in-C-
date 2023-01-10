// Command.cpp
#include "Command.h"
int Command::k = 5;
string Command::distance_metric = "EUC";
int Command::socket = 0;
bool Command::exist = false;


string Command::description()
{
    return "This is a command abstract class.";
}

void Command::execute()
{
    // Default implementation of the execute function
}

void Command::makeFalse() {
    printf("%d", exist);
    exist = false;
}

void Command::init(int number) {
    if (!exist) {
        classfiedVectorList = new vector<pair< vector<double>, string > >;
        notClassfiedVectorList = new vector<pair< vector<double>, string > >;
        socket = number;
        exist = true;
    }
}




