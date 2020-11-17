/*
 * Util.h
 *
 *  Created on: Oct 12, 2020
 *  Author: aliarslan
 */

#include <math.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

class Util {
    public:
        static double calculateDistance(int receiverX, int receiverY, int senderX, int senderY);
        static bool isMaliciousNode(string m, int nodeIndex);
        static vector<int> checkMaliciousNodes(vector<int> neighbors, vector<int> rreqSenders);
};
#endif /* SRC_UTIL_H_ */
