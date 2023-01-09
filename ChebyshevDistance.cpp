#include "ChebyshevDistance.h"
/**
 * the function returns the distance between 2 vectors according to the chebyshev method.
 * @param v1 - the first vector
 * @param v2 - the second vector
 * @return the distance between the 2 vectors.
 */
double ChebyshevDistance::distance(vector<double> v1, vector<double> v2) {
    double max = 0, c;
    // running over all the points of the vectors
    for (int i = 0; i < v1.size(); ++i) {
        c = abs(v1.at(i) - v2.at(i));
        // checks which is the maximum value
        if (c > max) {
            max = c;
        }
    }
    return max;
}