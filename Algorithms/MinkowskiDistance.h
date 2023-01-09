#ifndef ADVANCEDPROGRAMINGPART2_MINKOWSKIDISTANCE_H
#define ADVANCEDPROGRAMINGPART2_MINKOWSKIDISTANCE_H
#include <vector>
#include <iostream>
#include <cmath>
#include "Distance.h"

using namespace std;

class MinkowskiDistance : public Distance {
public:
    double distance(vector<double> v1, vector<double> v2) override;
};

#endif //ADVANCEDPROGRAMINGPART2_MINKOWSKIDISTANCE_H