#include "Values.h"

// Getters
int Values::getK() const {
    return k;
}
string Values::getDistanceMetric() const {
    return distance_metric;
}
vector<pair< vector<double>, string > > *Values::getClassfiedVectorList() {
    return classfiedVectorList;
}
vector<pair< vector<double>, string > > *Values::getNotClassfiedVectorList() {
    return notClassfiedVectorList;
}
int Values::getSocket() const {
    return socket;
}


// Setters
void Values::setK(int val) {
    k = val;
}
void Values::setDistanceMetric(string val) {
    distance_metric = val;
}
void Values::setClassfiedVectorList(vector<pair< vector<double>, string > > *val) {
    classfiedVectorList = val;
}
void Values::setNotClassfiedVectorList(vector<pair< vector<double>, string > > *val) {
    notClassfiedVectorList = val;
}
void Values::setSocket(int val) {
    socket = val;
}

Values::Values(int socket_val) {
    k = 5;
    distance_metric = "EUC";
    classfiedVectorList = new vector<pair< vector<double>, string > >;
    notClassfiedVectorList = new vector<pair< vector<double>, string > >;
}

Values::~Values() {
    delete notClassfiedVectorList;
    delete classfiedVectorList;
}
