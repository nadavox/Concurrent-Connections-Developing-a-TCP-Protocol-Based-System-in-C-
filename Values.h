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
    vector<pair< vector<double>, string > > *notClassifiedVectorList;
    int socket;
public:
    //constructor
    Values(int socket_val);
    //deconstruction
    ~Values();
    // Getters
    int getK() const;
    string getDistanceMetric() const;
    vector<pair< vector<double>, string > > *getClassifiedVectorList();
    vector<pair< vector<double>, string > > *getNotClassifiedVectorList();
    int getSocket() const;
    // Setters
    void setK(int val);
    void setDistanceMetric(string val);
    void setClassifiedVectorList(vector<pair< vector<double>, string > > *val);
    void setClassifiedVectorList(pair<vector<double>, string> *v);
    void setNotClassifiedVectorList(pair<vector<double>, string> *v);
    void setNotClassifiedVectorList(vector<pair< vector<double>, string > > *val);
    void setSocket(int val);
};

#endif //ADVANCEDPROGRAMINGPART3_VALUES_H
