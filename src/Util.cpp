/*
 * Util.cpp
 *
 *  Created on: 30 Tem 2020
 *      Author: Ali Arslan
 */

#include "Util.h"

double Util::kapsamaAlaniHesapla(int gondericiKordinatX, int gondericiKordinatY){
    double x = double(pow(abs(gondericiKordinatX - gondericiKordinatY), 2));
    double y = double(pow(abs(gondericiKordinatY - gondericiKordinatX), 2));
    return sqrt(x + y);
}

bool Util::getMaliciousNodes(string maliciousFromConf, int nodeIndex, int maliciousRss, int rss) {
    vector<int> maliciousNodes;
    stringstream maliciousNodesFromConfig(maliciousFromConf);
    bool nodeMaliciousStatus = false;

    for (int i; maliciousNodesFromConfig >> i;) {
        maliciousNodes.push_back(i);
        if (maliciousNodesFromConfig.peek() == ',')
            maliciousNodesFromConfig.ignore();
    }

    for (int malicious : maliciousNodes) {
        if(malicious == nodeIndex){
            nodeMaliciousStatus = true;
            rss = rss + (std::rand() % (maliciousRss - rss + 1));
        }
    }

    return nodeMaliciousStatus;
}
