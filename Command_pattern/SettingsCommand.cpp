#include <iostream>
#include "SettingsCommand.h"

using namespace std;

/**
 * this function will send the client to current values of k and the distance function name, and will update
 * this values according to the user.
 * if the new values are not valid - will send following message to the client.
 */
void SettingsCommand::execute()
{
    cout << "Setting algorithm parameters..." << endl;
}

/**
 * the function returns it's description in the menu
 * @return it's description in the menu
 */
string SettingsCommand::description() {
    return "2. algorithm settings\n";
}
