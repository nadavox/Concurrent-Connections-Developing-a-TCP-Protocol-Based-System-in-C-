#ifndef ADVANCEDPROGRAMINGPART2_CHEBYSHEVDISTANCE_H
#define ADVANCEDPROGRAMINGPART2_CHEBYSHEVDISTANCE_H
#include <vector>
#include <iostream>
#include <cmath>
#include "Distance.h"

using namespace std;

class ChebyshevDistance : public Distance{
public:
    double distance(vector<double> v1, vector<double> v2) override;
};
#endif //ADVANCEDPROGRAMINGPART2_CHEBYSHEVDISTANCE_H