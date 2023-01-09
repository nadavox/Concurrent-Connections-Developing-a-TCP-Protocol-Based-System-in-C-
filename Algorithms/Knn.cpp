#include "Knn.h"

/**
 * Constructor that get pointer to the wanted distance class and k
 * @param distanceAlgo
 * @param k
 */
Knn::Knn(Distance *distanceAlgo, int k) {
    this->distanceAlgo = distanceAlgo;
    this->k = k;
}

/**
 * the function get vector from the user, calculate the distance from the user vector to the classified vectors and
 * finds the k closest neighbors of the user vector
 * @param userVector
 * @param vectorsList
 * @return the most common title of the k closest neighbors of the user vector
 *
 */
string Knn::CalculateKNN(vector<double> userVector, vector<pair<vector<double>, string> > vectorsList) {
    // create new vector array for the distance values
    vector <pair<double, string> > distanceFromVector;
    // insert to the vector the distance between the vectors
    for (int i = 0; i < vectorsList.size(); i++) {
        distanceFromVector.push_back(make_pair(this->distanceAlgo->distance(vectorsList.at(i).first, userVector), vectorsList.at(i).second));
    }
    // sorts the distance values
    sort(distanceFromVector.begin(), distanceFromVector.end());
    // create new vector that will hold the k closest neighbors to the user vector
    vector <pair<double, string> > kDistanceFromVector;
    // insert the first k values
    for (int i = 0; i < k; ++i) {
        kDistanceFromVector.push_back(distanceFromVector.at(i));
    }

    // create new vector that will hold how many times every title appears in the k neighbors vector
    vector <pair<int, string> > countString;
    for (int i = 0; i < kDistanceFromVector.size(); ++i) {
        int flag = 0;
        for (int j = 0; j < countString.size(); ++j) {
            // if the title already appears in the vector - add 1 to the amount of times the title shows up
            if (kDistanceFromVector.at(i).second == countString.at(j).second) {
                countString.at(j).first += 1;
                flag = 1;
            }
        }
        // the title doesn't exist in the vector - insert it to the vector with the number of 1 (first time it shows up)
        if (!flag) {
            countString.push_back(make_pair(1, kDistanceFromVector.at(i).second));
        }
    }
    // sort the countString vector in order to know which title showed up the most.
    sort(countString.begin(), countString.end());
    return countString.at(countString.size() - 1).second;
}