/*
 * dugum.h
 *
 *  Created on: Oct 12, 2020
 *  Author: aliarslan
 */

#ifndef NODE_H_
#define NODE_H_

#include <string.h>
#include <omnetpp.h>
#include <unistd.h>
#include <algorithm>

using namespace omnetpp;
using namespace std;

cModule *flatTopologyModule;

const int RANDOM_NUMBER_GENERATOR = 2; // omnet.ini seed number

class Node : public cSimpleModule {
    private:
        int nodeId;
        int nodeIndex;
        int kaynak;
        int hedef;
        int nodeSayisi;
        int radius;
        int topolojiX;
        int topolojiY;
        int nodeKordinatX;
        int nodeKordinatY;
        int helloMesajiSayisi = 0;
        int guncelHopSayisi=0, enKucukHop=0, enBuyukHedefSiraNo=0;
        int minRss, avgRss, maxRss, rss, zararliRss;
        double delayTime;
        int attackMode;
        int zararliPaketBoyutu;
        int ddosGonderimSayisi;
        int saldiriSayisi = 0;
        const char* zararlilar;

        vector<int> komsu;
        map<string, int> geriRotalama;
        map<string, int> ileriRotalama;

        int rreqId = 0;
        int hedefHerKomsudanBirRREPalsin = 0; // en küçük hop seçimi için

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual void handleHello(cMessage *msg);
        virtual void handleRREQ(AODVRREQ *rreq);
        virtual void handleRREP(AODVRREP *rrep);
        void RREQ();
        void RREP();
        void sendData(const char* msg);
        void send(cMessage *msg, int receiver);
        void sendDelay(cMessage *msg, float delayTime, int receiver);
        void start();
        void setAsNeighbor(int senderNodeIndex);
};

#endif /* NODE_H_ */
