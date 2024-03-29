#ifndef ADVANCEDPROGRAMINGPART3_CLASSIFYCOMMAND_H
#define ADVANCEDPROGRAMINGPART3_CLASSIFYCOMMAND_H

#include "Command.h"

class ClassifyCommand : public Command {
public:
    string description();
    void execute();
    ClassifyCommand(int socket, Values *valuesCopy, DefaultIO *dio);
    string getKnnOutput(const string& kindDistance, int k, vector<double> userVector,
                        vector<pair<vector<double>, string> > *vectorsList);
};

#endif //ADVANCEDPROGRAMINGPART3_CLASSIFYCOMMAND_H