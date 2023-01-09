#ifndef ADVANCEDPROGRAMINGPART2_CANBERRADISTANCE_H
#define ADVANCEDPROGRAMINGPART2_CANBERRADISTANCE_H
#include <vector>
#include <iostream>
#include <cmath>
#include "Distance.h"

using namespace std;

class CanberraDistance : public Distance{
public:
    double distance(vector<double> v1, vector<double> v2) override;
};
#endif //ADVANCEDPROGRAMINGPART2_CANBERRADISTANCE_H