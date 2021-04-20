/*
 * Util.cpp
 *
 * Created on: Oct 12, 2020
 * Author: Ali Arslan
 */

#include "Util.h"

 double Util::calculateTwoNodeDistance(int receiverX, int receiverY, int senderX, int senderY) {
    double x = double(pow(abs(receiverX - senderX), 2));
    double y = double(pow(abs(receiverY - senderY), 2));
    return sqrt(x + y);
}

 double Util::calculateDiagonalDistance(int xSideLength, int ySideLength) {
     return sqrt(double(pow((xSideLength), 2) + pow((ySideLength), 2)));
 }

bool Util::isMaliciousNode(string malicious, int nodeIndex) {
    vector<int> maliciousNodes;
    stringstream maliciousNodesFromConfig(malicious);
    bool nodeMaliciousStatus = false;

    for (int i; maliciousNodesFromConfig >> i;) {
        maliciousNodes.push_back(i);
        if (maliciousNodesFromConfig.peek() == ',')
            maliciousNodesFromConfig.ignore();
    }

    for (int malicious : maliciousNodes) {
        if(malicious == nodeIndex){
            nodeMaliciousStatus = true;
        }
    }

    return nodeMaliciousStatus;
}


string Util::vectorToString(vector<int> neighborsVector) {
    string neighbors;
    for(int item : neighborsVector) {
        neighbors += to_string(item) + ",";
    }
    neighbors.pop_back();
    return neighbors;

}

vector<int> Util::checkMaliciousNodes(vector<int> neighbors, vector<int> rreqSenders) {

    for(int sender : rreqSenders) {
        neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), sender), neighbors.end());
    }

    return neighbors;
}


int Util::randomNumberGenerator(int min, int max) {
    srand(static_cast <unsigned int> (time(0)));
    return rand() % max + min;
}
