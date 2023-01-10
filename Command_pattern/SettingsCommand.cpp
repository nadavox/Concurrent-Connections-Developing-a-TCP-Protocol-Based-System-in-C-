#include <iostream>
#include "SettingsCommand.h"

using namespace std;

void SettingsCommand::execute()
{
    cout << "Setting algorithm parameters..." << endl;
}

string SettingsCommand::description() {
    return "2. algorithm settings\n";
}
