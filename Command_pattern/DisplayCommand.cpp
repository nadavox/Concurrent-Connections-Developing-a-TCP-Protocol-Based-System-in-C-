#include <iostream>
#include "DisplayCommand.h"

using namespace std;

/**
 * this function will send to the client the classified results.
 * if there are no files, or the vectors has not been classified, will send following message.
 */
void DisplayCommand::execute()
{
    cout << "Displaying results..." << endl;
}

/**
 * the function returns it's description in the menu
 * @return it's description in the menu
 */
string DisplayCommand::description() {
    return "4. display results\n";
}
