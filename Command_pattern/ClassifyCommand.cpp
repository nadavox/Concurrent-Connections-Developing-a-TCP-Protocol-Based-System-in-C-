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
string getKnnOutput(const string& kindDistance, int k, vector<double> userVector,
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
    // the user have uploaded the vectors yet
    if (values->getNotClassifiedVectorList()->empty()) {
        string noData = "please upload data\n";
        // send the no data string to the client
        this->dio->writeInput(noData);
    }
        // the vectors in the classified file are not in the same size as the vectors in the un classified file
        //TODO: not good. maybe the second one is not good but the first is good
    else if (values->getNotClassifiedVectorList()->at(0).size() != values->getClassifiedVectorList()->at(0).first.size()){
        // error
    }
        // we can classify
    else {
        string kindDistance = values->getDistanceMetric(), output;
        int k = values->getK(), sizeOfUnClassifiedVectors = values->getNotClassifiedVectorList()->size();
        for (int i = 0; i < sizeOfUnClassifiedVectors; ++i) {
            // get the classification of the vector
            output = getKnnOutput(kindDistance, k, values->getNotClassifiedVectorList()->at(i), values->getClassifiedVectorList());
            pair<vector<double>, string> result;
            result.first = values->getNotClassifiedVectorList()->at(i);
            result.second = output;
            // save the result
            values->setAfterClassifing(&result);
        }
        for (int i = 0; i < values->getAfterClassifingList()->size(); ++i) {
            for (int j = 0; j <values->getAfterClassifingList()->at(i).first.size(); ++j) {
                cout <<values->getAfterClassifingList()->at(i).first.at(j) << " ";
            }
            cout << values->getAfterClassifingList()->at(i).second << endl;
        }
        string complete = "classifying data complete\n";
        // send the complete string to the client
        this->dio->writeInput(complete);
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
    valuesCopy->setSocket(socket);
    this->dio = dio;
}