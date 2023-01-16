#include <thread>
#include "DownloadCommand.h"
#include "mutex"
#include "../ThreadSync.h"
using namespace std;


void writeToFile(int sock, Values *values, DefaultIO *dio, string s) {
    std::unique_lock<std::mutex> lock(ThreadSync::mtx);
    // send the classification of every vector
    dio->writeInput(s);
    // wait until the client done with reading
    dio->readInput();
    //tell the main keep runing.
    lock.unlock();
    ThreadSync::thread_created = true;
    ThreadSync::cv.notify_one();
    cout << "line 17 in DOwnload commend: ThreadSync::thread_created: " <<  ThreadSync::thread_created<< endl;
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
    string s;
    // sends the classifications to the server
    for (int i = 0; i < sizeOfClassified; ++i) {
        s += to_string((i + 1)) + "\t" + values->getAfterClassifingList()->at(i).second + "\n";
    }
    // create a new thread that will send the classification to the client
    thread t(writeToFile, this->sock, values, this->dio, s);
    t.detach();
    ThreadSync::thread_created = false;
    ThreadSync::cv.notify_one();
    cout << "line 54" << endl;
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
