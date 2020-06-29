/*
 * dugum.h
 *
 *  Created on: May 9, 2018
 *      Author: aliarslan
 */

#ifndef NODE_H_
#define NODE_H_

#include <string.h>
#include <omnetpp.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>
#include <stdio.h>
#include <map>
#include <vector>

#include "AODVMsgPacket_m.h"

using namespace omnetpp;
using namespace std;

cModule *flatTopologyModule;


class Node : public cSimpleModule{
    private:
        int kaynak;
        int hedef;
        int nodeSayisi;
        int kapsama;
        int topolojiX;
        int topolojiY;
        int nodeKordinatX;
        int nodeKordinatY;
        int helloMesajiSayisi = 0;
        int guncelHopSayisi=0, enKucukHop=0, enBuyukHedefSiraNo=0;

        vector<int> komsu;
        map<string, int> geriRotalama;
        map<string, int> ileriRotalama;

        int rreqId = 0;
        int hedefHerKomsudanBirRREPalsin = 0; // en küçük hop seçimi için

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual void handleRREQ(AODVRREQ *rreq);
        virtual void handleRREP(AODVRREP *rrep);
        void RREQ();
        void RREP();
        void veriGonder();
        double kapsamaAlaniHesapla(int mesaji_gonderen_dugum_X, int mesaji_gonderen_dugum_Y);
};

#endif /* NODE_H_ */