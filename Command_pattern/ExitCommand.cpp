#include <iostream>
#include "ExitCommand.h"

using namespace std;

/**
 * this function will end the connection between the client and the server
 */
void ExitCommand::execute(){
    cout << "Exiting the program..." << endl;
}

/**
 * the function returns it's description in the menu
 * @return it's description in the menu
 */
string ExitCommand::description() {
    return "8. exit\n";
}

/**
 * the constructor of ExitCommand
 * @param socket - the socket of the client
 * @param valuesCopy - values object
 * @param dio - pointer to DefaultIO object
 */
ExitCommand::ExitCommand(int socket, Values *value, DefaultIO *dio) {
    values = value;
    value->setClientSocket(socket);
    this->dio = dio;
}