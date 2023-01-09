#include "CanberraDistance.h"
/**
 * the function returns the distance between 2 vectors according to the canberra method.
 * @param v1 - the first vector
 * @param v2 - the second vector
 * @return the distance between the 2 vectors.
 */
double CanberraDistance::distance(vector<double> v1, vector<double> v2) {
    double m, sum = 0, d;
    // running over all the points of the vectors
    for (int i = 0; i < v1.size(); ++i) {
        m = abs(v1.at(i) - v2.at(i));
        d = abs(v1.at(i)) + abs(v2.at(i));
        // if one vector in the location is not 0 so we add to sum.
        if (d != 0) {
            sum += m / d;
        }
    }
    return sum;
}