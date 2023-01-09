#include <iostream>
#include "UploadCommand.h"
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
using namespace std;

void UploadCommand::execute()
{
    char buffer[4096];
    string firstMessage = "Please upload your local train CSV file.\n";
    string Upload_Complete = "Upload complete.\n";
    //send function
    strcpy(buffer, firstMessage.c_str());
    int bytes_sent = send(socket, buffer, strlen(buffer), 0);
    if (bytes_sent < 0) {
        ///error
    }
    memset(buffer, 0, sizeof(buffer));
    //receive function in a while until no more data
    //save it in data structure classfiedVectorList.
    //send : Upload complete.
    strcpy(buffer, Upload_Complete.c_str());
    bytes_sent = send(socket, buffer, Upload_Complete.size(), 0);
    if (bytes_sent < 0) {
        ///error
    }
    memset(buffer, 0, sizeof(buffer));
    string secondMessage = "Please upload your local test CSV file.\n";
    //send function
    strcpy(buffer, secondMessage.c_str());
    bytes_sent = send(socket, buffer, strlen(buffer), 0);
    if (bytes_sent < 0) {
        ///error
    }
    memset(buffer, 0, sizeof(buffer));
    //receive function in a while until no more data
    //save it in data structure notClassfiedVectorList.
    //send : Upload complete.
    strcpy(buffer, Upload_Complete.c_str());
    bytes_sent = send(socket, buffer, Upload_Complete.size(), 0);
    if (bytes_sent < 0) {
        ///error
    }
    memset(buffer, 0, sizeof(buffer));

}

string UploadCommand::description() {
    return "1. upload an unclassified csv data file\n";

}
