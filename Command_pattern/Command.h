#ifndef ADVANCEDPROGRAMINGPART3_COMMAND_H
#define ADVANCEDPROGRAMINGPART3_COMMAND_H

#include <string>
#include <vector>

using namespace std;

// Command interface
class Command
{
protected:
    int k;
    string distance_metric;
    vector<pair<double, string >> classfiedVectorList;
    vector<pair<double, string >> notClassfiedVectorList;
    vector<string> tempBuffer;
    int socket;
public:
    Command(int num);
    virtual string description() = 0;
    virtual void execute() = 0;
};


#endif //ADVANCEDPROGRAMINGPART3_COMMAND_H