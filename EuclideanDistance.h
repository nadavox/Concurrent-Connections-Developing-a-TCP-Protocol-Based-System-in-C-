#ifndef ADVANCEDPROGRAMINGPART2_EUCLIDEANDISTANCE_H
#define ADVANCEDPROGRAMINGPART2_EUCLIDEANDISTANCE_H
#include <vector>
#include "math.h"
#include "Distance.h"

using namespace std;

class EuclideanDistance : public Distance {
public:
    double distance(vector<double> v1, vector<double> v2) override;
};

#endif //ADVANCEDPROGRAMINGPART2_EUCLIDEANDISTANCE_H