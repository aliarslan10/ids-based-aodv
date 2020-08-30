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

using namespace std;

#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

class Util {
    public:
        static double calculateDistance(int receiverX, int receiverY, int senderX, int senderY);
        static bool isMaliciousNode(string m, int nodeIndex);
};
#endif /* SRC_UTIL_H_ */
