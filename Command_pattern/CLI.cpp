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
    unsigned int data_len = menu.length();
    char data_addr[data_len + 1];
    const char* str = menu.c_str();
    // copy the data of the vector, distance function name and k to char array
    strcpy(data_addr, str);
    // send the full sentence to the server
    int sent_bytes = send(socketNumber, data_addr, data_len, 0);
    if (sent_bytes < 0) {
        perror("Error sending the data to the server");
    }
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
    Command *ec = new ExitCommand(socketNumber, v, dio);
    this->commands.insert(make_pair("1", uc));
    this->commands.insert(make_pair("2", sc));
    this->commands.insert(make_pair("3", cc));
    this->commands.insert(make_pair("4", dyc));
    this->commands.insert(make_pair("5", ddc));
    this->commands.insert(make_pair("8", ec));
    this->socketNumber = socketNumber;
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
