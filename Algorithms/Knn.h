#ifndef ADVANCEDPROGRAMINGPART2_KNN_H
#define ADVANCEDPROGRAMINGPART2_KNN_H

#include "Distance.h"
#include "EuclideanDistance.h"
#include "CanberraDistance.h"
#include "ChebyshevDistance.h"
#include "MinkowskiDistance.h"
#include "TaxicabGeometry.h"
//#include <bits/stdc++.h>

class Knn {
private:
    Distance* distanceAlgo;
    int k;
public:
    Knn(Distance* distanceAlgo, int k);
    string CalculateKNN(vector<double> userVector, vector<pair<vector<double>, string> > vectorsList);
};

#endif //ADVANCEDPROGRAMINGPART2_KNN_H