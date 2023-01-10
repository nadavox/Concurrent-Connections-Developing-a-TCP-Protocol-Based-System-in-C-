#include "CLI.h"

/**
 * the constructor of CLI
 * @param uc - the UploadCommand object
 * @param sc - the SettingsCommand object
 * @param cc - the ClassifyCommand object
 * @param dyc - the DisplayCommand object
 * @param ddc - the DownloadCommand object
 * @param ec - the ExitCommand object
 * @param socketNumber - the socket number to which we will send the menu to
 */
CLI::CLI(Command* uc, Command* sc, Command* cc, Command* dyc, Command* ddc, Command* ec, int socketNumber) {
    this->commands.insert(make_pair("1", uc));
    this->commands.insert(make_pair("2", sc));
    this->commands.insert(make_pair("3", cc));
    this->commands.insert(make_pair("4", dyc));
    this->commands.insert(make_pair("5", ddc));
    this->commands.insert(make_pair("8", ec));
    this->socketNumber = socketNumber;
}

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
