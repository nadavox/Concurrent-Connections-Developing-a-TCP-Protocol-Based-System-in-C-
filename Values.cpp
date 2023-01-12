#include "Values.h"

Values::Values(int socket_val) {
    k = 5;
    distance_metric = "EUC";
    classifiedVectorList = new vector<pair< vector<double>, string > >;
    notClassifiedVectorList = new vector<vector<double>>;
}

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
vector<pair< vector<double>, string > > *Values::getClassifiedVectorList() {
    return classifiedVectorList;
}
vector<vector<double>> *Values::getNotClassifiedVectorList() {
    return notClassifiedVectorList;
}
int Values::getSocket() const {
    return socket;
}
vector<pair<vector<double>, string>> *Values::getAfterClassifing() {
    return afterClassifing;
}

// Setters
void Values::setK(int val) {
    k = val;
}
void Values::setDistanceMetric(string val) {
    distance_metric = val;
}
void Values::setClassifiedVectorList(vector<pair< vector<double>, string > > *val) {
    classifiedVectorList = val;
}

void Values::setNotClassifiedVectorList(vector<vector<double> > *val) {
    notClassifiedVectorList = val;
}
void Values::setSocket(int val) {
    socket = val;
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

void Values::setAfterClassifing(vector<pair<vector<double>, string>> *val) {
    this->afterClassifing = val;
}
