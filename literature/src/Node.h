/*
 * dugum.h
 *
 *  Created on: Jun 27, 2020
 *      Author: aliarslan
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
cModule *node;

enum MSG_TYPE{ SENDING, RECEIVING, BROADCAST };
enum ATTACK_MODE { OFF, ON };

const int RANDOM_NUMBER_GENERATOR_SEED = 1; // omnet.ini seed number


class Node : public cSimpleModule {
    private:
        int nodeId;
        int nodeIndex;
        int kaynak;
        int hedef;
        int nodeSayisi;
        int topolojiX;
        int topolojiY;
        int nodeKordinatX;
        int nodeKordinatY;
        int radius, malcsRadius;
        int rss, minRSS, avgRSS, maxRSS, malcsRSS;
        int helloMesajiSayisi = 0;
        int guncelHopSayisi=0, enKucukHop=0, enBuyukHedefSiraNo=0;
        double delaySuspicious;
        double delayTime;
        int attackMode;
        int zararliPaketBoyutu;
        int ddosGonderimSayisi;
        int saldiriSayisi = 0;
        const char* zararlilar;
        bool isHelloSent = false;

        vector<int> komsu;
        vector<int> rreqSenders;
        map<string, int> geriRotalama;
        map<string, int> ileriRotalama;

        int rreqId = 0;
        int receivedRreqCount = 0; // to select smaller hop
        int round = 0;
        int hedefSeqNo = 0;

        double eElec;
        double eMp;
        double eFs;
        double eDa;
        int alfa1;
        int alfa2;
        int thDistance;
        double maxDistanceInTopology;

        bool isBatteryFull = true;
        double battery;
        double initialBattery;
        double consumedEnergy = 0;
        double totalConsumedEnergy = 0;
        bool isWaitingForTestMsgResponse = false;

        int packetSize;
        int dataPacketSize;

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual void handleHello(cMessage *msg);
        virtual void handleRREQ(AODVRREQ *rreq);
        virtual void handleRREP(AODVRREP *rrep);
        void sendHello();
        void RREQ();
        void RREP();
        void sendData(const char* msg);
        void send(cMessage *msg, int receiver);
        void sendDelay(cMessage *msg, float delayTime, int receiver);
        void start();
        bool isHelloAttack(int senderRSS, int senderIndex, double sentTime);
        void setAsNeighbor(int senderNodeIndex);
        void broadcast(cMessage *msg);
        void newRound();
        void decreaseBattery(double distance, int msgSendingType, int payload);
        void checkBattery();
};

#endif /* NODE_H_ */
