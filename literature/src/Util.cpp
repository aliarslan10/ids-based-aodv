/*
 * Util.cpp
 *
 * Created on: 30 Tem 2020
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

vector<int> Util::stringToVector(string str) {
    vector<int> vector;
    stringstream strStream(str);

    for (int i; strStream >> i;) {
        vector.push_back(i);
        if (strStream.peek() == ',')
            strStream.ignore();
    }

    return vector;
}
