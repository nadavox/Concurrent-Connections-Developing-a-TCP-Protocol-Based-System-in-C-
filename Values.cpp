#include "Values.h"

/**
 * the constructor of values
 * @param socket_val
 */
Values::Values(int clientSocket, int masterSocket) {
    k = 5;
    distance_metric = "AUC";
    classifiedVectorList = new vector<pair< vector<double>, string > >;
    notClassifiedVectorList = new vector<vector<double> >;
    afterClassifing = new vector<pair< vector<double>, string > >;
    this->clientSocket = clientSocket;
    this->masterSocket = masterSocket;
}

/**
 * the destructor of values
 */
Values::~Values() {
    delete notClassifiedVectorList;
    delete classifiedVectorList;
}

// Getters
int Values::getK() const {
    return k;
}
string Values::getDistanceMetric() const {
    return distance_metric;
}
int Values::getClientSocket() const {
    return clientSocket;
}
int Values::getMasterSocket() const {
    return masterSocket;
}
vector<pair< vector<double>, string > > *Values::getClassifiedVectorList() {
    return classifiedVectorList;
}
vector<vector<double> > *Values::getNotClassifiedVectorList() {
    return notClassifiedVectorList;
}
vector<pair<vector<double>, string> > *Values::getAfterClassifingList() {
    return afterClassifing;
}

// Setters
void Values::setK(int val) {
    k = val;
}
void Values::setDistanceMetric(string val) {
    distance_metric = val;
}
void Values::setClientSocket(int val) {
    clientSocket = val;
}
void Values::setMasterSocket(int val) {
    masterSocket = val;
}
void Values::setClassifiedVectorList(pair<vector<double>, string> *v) {
    this->classifiedVectorList->push_back(*v);
}

void Values::setNotClassifiedVectorList(vector<double> *v) {
    this->notClassifiedVectorList->push_back(*v);
}

void Values::setAfterClassifing(pair<vector<double>, string> *v) {
    this->afterClassifing->push_back(*v);
}
