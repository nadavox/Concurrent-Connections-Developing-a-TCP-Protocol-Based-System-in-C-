#include <iostream>
#include "ClassifyCommand.h"

using namespace std;

void ClassifyCommand::execute()
{
    cout << "Classifying data..." << endl;
}

string ClassifyCommand::description() {
    return "3. classify data\n";
}
