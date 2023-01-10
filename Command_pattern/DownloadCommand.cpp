#include <iostream>
#include "DownloadCommand.h"

using namespace std;

void DownloadCommand::execute()
{
    cout << "Downloading results..." << endl;
}

string DownloadCommand::description() {
    return "5. download results\n";
}
