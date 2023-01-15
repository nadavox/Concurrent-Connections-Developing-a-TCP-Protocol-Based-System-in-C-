#ifndef ADVANCEDPROGRAMINGPART3_VALUES_H
#define ADVANCEDPROGRAMINGPART3_VALUES_H

#include <string>
#include <vector>

using namespace std;

class Values {
private:
    int k;
    string distance_metric;
    vector<pair< vector<double>, string > > *classifiedVectorList;
    vector<vector<double> > *notClassifiedVectorList;
    vector<pair< vector<double>, string > > *afterClassifing;
    int clientSocket;
    int masterSocket;
public:
    //constructor
    Values(int clientSocket, int masterSocket);

    //deconstruction
    ~Values();

    // Getters
    int getK() const;
    string getDistanceMetric() const;
    int getClientSocket() const;
    int getMasterSocket() const;
    vector<pair< vector<double>, string > > *getClassifiedVectorList();
    vector<vector<double> > *getNotClassifiedVectorList();
    vector<pair< vector<double>, string > > *getAfterClassifingList();

    // Setters
    void setK(int val);
    void setDistanceMetric(string val);
    void setClientSocket(int val);
    void setMasterSocket(int val);
    void setClassifiedVectorList(pair<vector<double>, string> *v);
    void setNotClassifiedVectorList(vector<double> *v);
    void setAfterClassifing(pair<vector<double>, string> *v);
};

#endif //ADVANCEDPROGRAMINGPART3_VALUES_H
