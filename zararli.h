/*
 * zararli.h
 *
 *  Created on: 26 Oca 2020
 *      Author: Ali
 */

#ifndef ZARARLI_H_
#define ZARARLI_H_


#include <string.h>
#include <omnetpp.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>
#include <stdio.h>

using namespace omnetpp;
using namespace std;

class Zararli : public cSimpleModule {
    public:
        //Attack();
        //virtual ~Attack();
        void initialize();
        virtual void handleMessage(cMessage *msg);
};


#endif /* ZARARLI_H_ */

