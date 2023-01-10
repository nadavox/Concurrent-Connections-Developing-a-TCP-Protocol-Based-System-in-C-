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
    // first element is: vector of the numbers.
    // second element is pair: the first element is the name/type of the vector
    //                        the second element is the size of the vector.
    static vector<pair< vector<double>, string > > classfiedVectorList;
    static vector<pair< vector<double>, string > > notClassfiedVectorList;
    static vector<string> tempBuffer;
    static int socket;
public:
    Command(int num);
    virtual string description() = 0;
    virtual void execute() = 0;
};


#endif //ADVANCEDPROGRAMINGPART3_COMMAND_H