/*
 * Util.cpp
 *
 *  Created on: 30 Tem 2020
 *      Author: Ali
 */

#include "Util.h"

double kapsamaAlaniHesapla(int gondericiKordinatX, int gondericiKordinatY){
    double x = double(pow(abs(gondericiKordinatX - gondericiKordinatY), 2));
    double y = double(pow(abs(gondericiKordinatY - gondericiKordinatX), 2));
    return sqrt(x + y);
}

void setMaliciousNodes(string zararlilar, int nodeIndex, int zararli, int zararliRss, int rss) {
    vector<int> zararliNode;
    stringstream zararliNodes(zararlilar);

    for (int i; zararliNodes >> i;) {
        zararliNode.push_back(i);
        if (zararliNodes.peek() == ',')
            zararliNodes.ignore();
    }

    for (std::size_t i = 0; i < zararliNode.size(); i++) {
        if(zararliNode[i] == nodeIndex){
            zararli = true;
            rss = rss + (std::rand() % (zararliRss - rss + 1));
        }
    }
}
