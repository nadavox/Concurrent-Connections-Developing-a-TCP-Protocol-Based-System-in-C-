#include <iostream>
#include "ExitCommand.h"

using namespace std;

void ExitCommand::execute()
{
    cout << "Exiting the program..." << endl;
}

string ExitCommand::description() {
    return "8. exit\n";
}
