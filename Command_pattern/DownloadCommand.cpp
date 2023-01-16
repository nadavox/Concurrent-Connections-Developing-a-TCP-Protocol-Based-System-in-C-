#include <iostream>
#include <thread>
#include <netinet/in.h>
#include "DownloadCommand.h"
#include "../IOClass/SocketIO.h"
#include <unistd.h>
#include "mutex"

using namespace std;

mutex mx;

void DownloadCommand::writeToFile() {

    mx.lock();
    int sizeOfClassified = values->getAfterClassifingList()->size();
    string s;
    // sends the classifications to the server
    for (int i = 0; i < sizeOfClassified; ++i) {
        s = to_string((i + 1)) + "\t" + values->getAfterClassifingList()->at(i).second + "\n";
        // send the classification of every vector
        dio->writeInput(s);
        // wait until the client done with reading
        dio->readInput();
    }
    // send to the server we are done
    dio->writeInput("Done.\n");
    // wait until the client done with reading
    dio->readInput();
    mx.unlock();
}

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
        // wait until the client done with reading
        this->dio->readInput();
        return;
    }
    if (sizeOfClassified == 0) {
        // send to the server that the user haven't classified the vectors yet
        this->dio->writeInput("please classify the data\n");
        // wait until the client done with reading
        this->dio->readInput();
        return;
    }
    // send the classification of every vector
    this->dio->writeInput("please upload a path to a file we could write to\n");
    // wait until the client done with reading
    this->dio->readInput();

    // create a new thread that will send the classification to the client
    thread t([&](){
        writeToFile();
    });
    t.detach();
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
    value->setClientSocket(socket);
    this->dio = dio;
}
