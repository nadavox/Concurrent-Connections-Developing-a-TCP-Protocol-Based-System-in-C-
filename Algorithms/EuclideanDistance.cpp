#include "EuclideanDistance.h"
/**
 * the function returns the distance between 2 vectors according to the euclidean method.
 * @param v1 - the first vector
 * @param v2 - the second vector
 * @return the distance between the 2 vectors.
 */
double EuclideanDistance::distance(vector<double> v1, vector<double> v2) {
    double m, sum = 0;
    // running over all the points of the vectors
    for (int i = 0; i < v1.size(); ++i) {
        m = v1.at(i) - v2.at(i);
        sum += pow(m, 2);
    }
    sum = sqrt(sum);
    return sum;
}