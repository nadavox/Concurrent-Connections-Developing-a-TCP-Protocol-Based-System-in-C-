#ifndef ADVANCEDPROGRAMING_DISTANCE_H
#define ADVANCEDPROGRAMING_DISTANCE_H
#include <vector>
#include <iostream>
#include <cmath>
#include <typeinfo>

using namespace std;

//abstract class
class Distance{
public:
    virtual ~Distance() = default;
    virtual double distance(vector<double> v1, vector<double> v2);
};

#endif //ADVANCEDPROGRAMING_DISTANCE_H
