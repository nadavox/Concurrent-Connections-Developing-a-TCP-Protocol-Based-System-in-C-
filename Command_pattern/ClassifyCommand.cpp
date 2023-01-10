#include <iostream>
#include "ClassifyCommand.h"

using namespace std;

/**
 * the function classify the vectors according to the classified vectors the user gave.
 */
void ClassifyCommand::execute()
{
    cout << "Classifying data..." << endl;
}

/**
 * the function returns it's description in the menu
 * @return it's description in the menu
 */
string ClassifyCommand::description() {
    return "3. classify data\n";
}
