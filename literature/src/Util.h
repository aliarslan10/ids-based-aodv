/*
 * Util.h
 *
 * Created on: 30 Tem 2020
 * Author: Ali Arslan
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
        static bool isMaliciousNode(string malicious, int nodeIndex);
        static vector<int> checkMaliciousNodes(vector<int> neighbors, vector<int> rreqSenders);
        static vector<int> csvToVector(string commaSeparatedValue);
        static string vectorToCSV(vector<int> vector);
        static int randomNumberGenerator(int min, int max);
        static vector<int> selectRandomValues(vector<int>, int quantity);
        static vector<int> updateVector(vector<int> items, vector<int> selectedValues);
};
#endif /* SRC_UTIL_H_ */
