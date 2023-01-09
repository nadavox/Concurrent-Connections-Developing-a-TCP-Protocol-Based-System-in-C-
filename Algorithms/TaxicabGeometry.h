#ifndef ADVANCEDPROGRAMINGPART2_TAXICABGEOMETRY_H
#define ADVANCEDPROGRAMINGPART2_TAXICABGEOMETRY_H
#include <vector>
#include "math.h"
#include "Distance.h"

using namespace std;

class TaxicabGeometry : public Distance{
public:
    double distance(vector<double> v1, vector<double> v2) override;
};

#endif //ADVANCEDPROGRAMINGPART2_TAXICABGEOMETRY_H