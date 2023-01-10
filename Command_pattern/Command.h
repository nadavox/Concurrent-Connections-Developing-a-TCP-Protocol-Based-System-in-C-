#ifndef ADVANCEDPROGRAMINGPART3_COMMAND_H
#define ADVANCEDPROGRAMINGPART3_COMMAND_H

#include <string>
#include <vector>

using namespace std;

// Command interface
class Command
{
protected:
    static int k;
    static string distance_metric;
    vector<pair< vector<double>, string > > *classfiedVectorList;
    vector<pair< vector<double>, string > > *notClassfiedVectorList;
    static int socket;
    static bool exist;
    void init(int number);
public:
    virtual string description() = 0;
    virtual void execute() = 0;
    static void makeFalse();
};


#endif //ADVANCEDPROGRAMINGPART3_COMMAND_H