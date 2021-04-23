/*
 * Util.h
 *
 *  Created on: 30 Tem 2020
 *      Author: Ali
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
        static int randomNumberGenerator(int min, int max);
};
#endif /* SRC_UTIL_H_ */
