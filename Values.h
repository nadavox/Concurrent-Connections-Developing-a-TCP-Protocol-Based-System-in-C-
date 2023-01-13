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
    int socket;
public:
    //constructor
    Values(int socket_val);

    //deconstruction
    ~Values();

    // Getters
    int getK() const;
    string getDistanceMetric() const;
    int getSocket() const;
    vector<pair< vector<double>, string > > *getClassifiedVectorList();
    vector<vector<double> > *getNotClassifiedVectorList();
    vector<pair< vector<double>, string > > *getAfterClassifingList();

    // Setters
    void setK(int val);
    void setDistanceMetric(string val);
    void setSocket(int val);
    void setClassifiedVectorList(pair<vector<double>, string> *v);
    void setNotClassifiedVectorList(vector<double> *v);
    void setAfterClassifing(pair<vector<double>, string> *v);
};

#endif //ADVANCEDPROGRAMINGPART3_VALUES_H
