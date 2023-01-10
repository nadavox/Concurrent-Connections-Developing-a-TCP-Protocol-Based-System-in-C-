#ifndef ADVANCEDPROGRAMINGPART3_VALUES_H
#define ADVANCEDPROGRAMINGPART3_VALUES_H
#include <string>
#include <vector>
using namespace std;

class Values {
private:
    int k;
    string distance_metric;
    vector<pair< vector<double>, string > > *classfiedVectorList;
    vector<pair< vector<double>, string > > *notClassfiedVectorList;
    int socket;
public:
    //constructor
    Values(int socket_val);
    //deconstruction
    ~Values();
    // Getters
    int getK() const;
    string getDistanceMetric() const;
    vector<pair< vector<double>, string > > *getClassfiedVectorList();
    vector<pair< vector<double>, string > > *getNotClassfiedVectorList();
    int getSocket() const;
    // Setters
    void setK(int val);
    void setDistanceMetric(string val);
    void setClassfiedVectorList(vector<pair< vector<double>, string > > *val);
    void setNotClassfiedVectorList(vector<pair< vector<double>, string > > *val);
    void setSocket(int val);
};

#endif //ADVANCEDPROGRAMINGPART3_VALUES_H
