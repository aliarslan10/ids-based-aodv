/*
 * attack.h
 *
 *  Created on: 26 Oca 2020
 *      Author: Ali
 */

#ifndef ATTACK_H_
#define ATTACK_H_


#include <string.h>
#include <omnetpp.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>
#include <stdio.h>

using namespace omnetpp;
using namespace std;

class Attack {
    public:
        //Attack();
        //virtual ~Attack();
        void paketBoyutunuKontrolEt(int m_paketBoyutu, int paketBoyutu);
        int ddos(vector<int> komsu, cMessage *msg);
        void sinkHole();
        void blackHole();
        void helloFlood();
        void selectiveForwarding();
};


#endif /* ATTACK_H_ */

