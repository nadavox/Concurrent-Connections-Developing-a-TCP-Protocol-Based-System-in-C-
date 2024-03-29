#include "ClassifyCommand.h"
#include "../Algorithms/Distance.h"
#include "../Algorithms/EuclideanDistance.h"
#include "../Algorithms/TaxicabGeometry.h"
#include "../Algorithms/ChebyshevDistance.h"
#include "../Algorithms/MinkowskiDistance.h"
#include "../Algorithms/CanberraDistance.h"
#include "../Algorithms/Knn.h"

using namespace std;

/**
 * this function classified the user vector.
 * @param kindDistance
 * @param k
 * @param userVector
 * @param vectorsList
 * @return the name of the classified vector
 */
string ClassifyCommand::getKnnOutput(const string& kindDistance, int k, vector<double> userVector,
                    vector<pair<vector<double>, string> > *vectorsList) {
    string output;
    Distance *distanceAlgo;
    // we will calculate knn according to euclidean distance
    if (kindDistance == "AUC") {
        distanceAlgo = new EuclideanDistance;
    }
        // we will calculate knn according to taxicab geometry
    else if (kindDistance == "MAN") {
        distanceAlgo = new TaxicabGeometry;
    }
        // we will calculate knn according to chebyshev distance
    else if (kindDistance == "CHB") {
        distanceAlgo = new ChebyshevDistance;
    }
        // we will calculate knn according to canberra distance
    else if (kindDistance == "CAN") {
        distanceAlgo = new CanberraDistance;
    }
        // we will calculate knn according to minkowski distance
    else {
        distanceAlgo = new MinkowskiDistance;
    }
    // now we have the vector all what left is to calculate.
    Knn knnAlgo = Knn(distanceAlgo, k);
    // calculate knn
    output = knnAlgo.CalculateKNN(userVector, *vectorsList);
    free(distanceAlgo);
    return output;
}

/**
 * the function classify the vectors according to the classified vectors the user gave.
 */
void ClassifyCommand::execute()
{
    values->getAfterClassifingList()->clear();
    int k = values->getK(), sizeOfClassifiedVectors = values->getClassifiedVectorList()->size();
    // k is bigger that the number of classified vectors
    if (k > sizeOfClassifiedVectors) {
        string noData = "invalid value for k\n";
        // send the no data string to the client
        this->dio->writeInput(noData);
        // get from client that we are done
        this->dio->readInput();
        return;
    }

    // the user have uploaded the vectors yet
    if (values->getNotClassifiedVectorList()->empty()) {
        string noData = "please upload data\n";
        // send the no data string to the client
        this->dio->writeInput(noData);
        // get from client that we are done
        this->dio->readInput();
    }
    // we can classify
    else {
        string kindDistance = values->getDistanceMetric(), output;
        int sizeOfUnClassifiedVectors = values->getNotClassifiedVectorList()->size();
        for (int i = 0; i < sizeOfUnClassifiedVectors; ++i) {
            // get the classification of the vector
            output = getKnnOutput(kindDistance, k, values->getNotClassifiedVectorList()->at(i), values->getClassifiedVectorList());
            pair<vector<double>, string> result;
            result.first = values->getNotClassifiedVectorList()->at(i);
            result.second = output;
            // save the result
            values->setAfterClassifing(&result);
        }
        string complete = "classifying data complete\n";
        // send the complete string to the client
        this->dio->writeInput(complete);
        // get from client that we are done
        this->dio->readInput();
    }
}

/**
 * the function returns it's description in the menu
 * @return it's description in the menu
 */
string ClassifyCommand::description() {
    return "3. classify data\n";
}

/**
 * the constructor of ClassifyCommand
 * @param socket - the socket of the client
 * @param valuesCopy - values object
 * @param dio - pointer to DefaultIO object
 */
ClassifyCommand::ClassifyCommand(int socket, Values *valuesCopy, DefaultIO *dio) {
    values = valuesCopy;
    valuesCopy->setClientSocket(socket);
    this->dio = dio;
}