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

/**
 * the constructor of DisplayCommand
 * @param socket - the socket of the client
 * @param valuesCopy - values object
 * @param dio - pointer to DefaultIO object
 */
DisplayCommand::DisplayCommand(int socket, Values *value, DefaultIO *dio) {
    values = value;
    value->setSocket(socket);
    this->dio = dio;
}
