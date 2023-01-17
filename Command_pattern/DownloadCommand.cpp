#include <thread>
#include "DownloadCommand.h"
#include "mutex"
#include "../ThreadSync.h"
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
    //check the client enter file path
    string output = this->dio->readInput();
    // save all the file to string
    if (output != "Error") {
        string s;
        int i = 0;
        while (i < sizeOfClassified) {
            unsigned long chunk =0;
            // sends the classifications to the server
            for (; i < sizeOfClassified; ++i) {
                if (chunk < 750) {
                    s += to_string((i + 1)) + "\t" + values->getAfterClassifingList()->at(i).second + "\n";
                    chunk += s.size();
                } else {
                    break;
                }
            }
            // send the classification of every vector
            dio->writeInput(s);
            // wait until the client done with reading
            dio->readInput();
            s.clear();
        }
        // send done
        dio->writeInput("Done.\n");
        // wait until the client done with reading
        string done = dio->readInput();
    }

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
    this->sock = socket;
}
