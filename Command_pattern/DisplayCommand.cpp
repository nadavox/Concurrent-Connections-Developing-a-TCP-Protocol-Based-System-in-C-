#include <iostream>
#include "DisplayCommand.h"

using namespace std;

void DisplayCommand::execute()
{
    cout << "Displaying results..." << endl;
}

string DisplayCommand::description() {
    return "4. display results\n";
}
