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
#include <ctime>

using namespace std;

#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

class Util {
    public:
        static double calculateTwoNodeDistance(int receiverX, int receiverY, int senderX, int senderY);
        static double calculateDiagonalDistance(int xSideLength, int ySideLength);
        static bool isMaliciousNode(string m, int nodeIndex);
        static vector<int> detectMaliciousNodes(vector<int> neighbors, vector<int> rreqSenders);
        static string vectorToString(vector<int> neighbors);
        static vector<int> stringToVector(string str);
};
#endif /* SRC_UTIL_H_ */
