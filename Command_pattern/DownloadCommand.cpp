#include <iostream>
#include "DownloadCommand.h"

using namespace std;

/**
 * this function will send to the client the classified results.
 * if there are no files, or the vectors has not been classified, will send following message.
 */
void DownloadCommand::execute()
{
    int sizeOfClassified = values->getAfterClassifingList()->size();
    if (values->getNotClassifiedVectorList()->empty()) {
        // send to the server that the user haven't uploaded the files yet
        this->dio->writeInput("please upload data\n");
        return;
    }
    if (sizeOfClassified == 0) {
        // send to the server that the user haven't classified the vectors yet
        this->dio->writeInput("please classify the data\n");
        return;
    }
    string s;
    for (int i = 0; i < sizeOfClassified; ++i) {
        s = to_string((i + 1)) + "\t" + values->getAfterClassifingList()->at(i).second + "\n";
        // send the classification of every vector
        this->dio->writeInput(s);
    }
    // send to the server we are done
    this->dio->writeInput("Done.\n");
}

/**
 * the function returns it's description in the menu
 * @return it's description in the menu
 */
string DownloadCommand::description() {
    return "5. download results\n";
}

/**
 * the constructor of DownloadCommand
 * @param socket - the socket of the client
 * @param valuesCopy - values object
 * @param dio - pointer to DefaultIO object
 */
DownloadCommand::DownloadCommand(int socket, Values *value, DefaultIO *dio) {
    values = value;
    value->setSocket(socket);
    this->dio = dio;
}
