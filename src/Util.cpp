/*
 * Util.cpp
 *
 * Created on: Oct 12, 2020
 * Author: Ali Arslan
 */

#include "Util.h"

 double Util::calculateDistance(int receiverX, int receiverY, int senderX, int senderY) {
    double x = double(pow(abs(receiverX - senderX), 2));
    double y = double(pow(abs(receiverY - senderY), 2));
    return sqrt(x + y);
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

vector<int> Util::checkMaliciousNodes(vector<int> neighbors, vector<int> rreqSenders) {

    for(int sender : rreqSenders) {
        neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), sender), neighbors.end());
    }

    return neighbors;
}
