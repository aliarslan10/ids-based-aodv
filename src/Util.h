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

using namespace std;

#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

class Util {
    public:
        double kapsamaAlaniHesapla(int msgGonderenX, int msgGonderenY);
        void setMaliciousNodes(string zararlilar, int nodeIndex, int zararli, int zararliRss, int rss);
}
#endif /* SRC_UTIL_H_ */
