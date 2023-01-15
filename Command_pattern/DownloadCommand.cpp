#include <iostream>
#include <netinet/in.h>
#include <thread>
#include "DownloadCommand.h"
#include "../IOClass/SocketIO.h"

using namespace std;


void writeToFile(int thread_socket, Values *values) {
    int sizeOfClassified = values->getAfterClassifingList()->size();
    string s;
    //create value object.
    DefaultIO *dio = new SocketIO(thread_socket);
    // send the classification of every vector
    dio->writeInput("please upload a path to a file we could write to\n");
    // wait until the client done with reading
    dio->readInput();
    for (int i = 0; i < sizeOfClassified; ++i) {
        cout << "end"<< endl;
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
    ///-------------------------------------------------------------------------
    // create a socket for the client
    struct sockaddr_in client_sin{};
    unsigned int addr_len = sizeof(client_sin);
    // accept a client connection
    int thread_socket = accept(values->getSocket(), (struct sockaddr *) &client_sin, &addr_len);
    if (thread_socket < 0) {
        perror("Error while trying to accept a new client connection");
        exit(1);
    }
    thread t(writeToFile, thread_socket, values);
    t.detach();
    ///--------------------------------------------------------------------------------
//    string s;
//    // send the classification of every vector
//    this->dio->writeInput("please upload a path to a file we could write to\n");
//    // wait until the client done with reading
//    this->dio->readInput();
//    for (int i = 0; i < sizeOfClassified; ++i) {
//        cout << "end"<< endl;
//        s = to_string((i + 1)) + "\t" + values->getAfterClassifingList()->at(i).second + "\n";
//        // send the classification of every vector
//        this->dio->writeInput(s);
//        // wait until the client done with reading
//        this->dio->readInput();
//    }
//    // send to the server we are done
//    this->dio->writeInput("Done.\n");
//    // wait until the client done with reading
//    this->dio->readInput();
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
