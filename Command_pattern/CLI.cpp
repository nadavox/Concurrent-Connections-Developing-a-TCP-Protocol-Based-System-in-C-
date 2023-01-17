#include "CLI.h"

/**
 * this function creates the menu and sends it to the client socket
 */
void CLI::start() {
    string menu;
    menu = "Welcome to the KNN Classifier server. Please choose an option:\n";
    // appending the strings of every command to the menu
    for (const auto& value : this->commands) {
        menu += value.second->description();
    }
    menu += "8. exit\n";
    // sends the menu to the client
    this->dio->writeInput(menu);
}

/**
 * the constructor of CLI
 * @param socketNumber - the client socket number
 * @param v - pointer to values object
 * @param dio - pointer to DefaultIO object
 */
CLI::CLI(int socketNumber, Values *v, DefaultIO *dio) {
    Command *uc = new UploadCommand(socketNumber, v, dio);
    Command *sc = new SettingsCommand(socketNumber, v, dio);
    Command *cc = new ClassifyCommand(socketNumber, v, dio);
    Command *dyc = new DisplayCommand(socketNumber, v, dio);
    Command *ddc = new DownloadCommand(socketNumber, v, dio);
    this->commands.insert(make_pair("1", uc));
    this->commands.insert(make_pair("2", sc));
    this->commands.insert(make_pair("3", cc));
    this->commands.insert(make_pair("4", dyc));
    this->commands.insert(make_pair("5", ddc));
    this->socketNumber = socketNumber;
    this->dio = dio;
}

/**
 * this function executes the wanted command
 * @param s - the command number
 */
void CLI::executeCommand(string s) {
    commands[s]->execute();
}

/**
 * destructor for CLI
 */
CLI::~CLI() {
    for (auto it = commands.rbegin(); it != commands.rend(); ++it) {
        delete it->second;
        commands.erase(it->first);
    }
}
