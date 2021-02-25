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

using namespace omnetpp;
using namespace std;

cModule *flatTopologyModule;
cModule *node;

const int RANDOM_NUMBER_GENERATOR = 2; // omnet.ini seed number

enum MSG_TYPE{ SENDING, RECEIVING, BROADCAST };

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
        vector<int> routes;
        string route;
        vector<int> rreqSenders;
        map<string, int> geriRotalama;
        map<string, int> ileriRotalama;
        string neighborsOfMyNeighbors;
        vector<string> neighborsOfNodesOnTheRoute;
        bool setMalcsControllerOnDest = true;
        vector<int> blackList;

        int rreqId = 0;
        int receivedRreqCount = 0; // en küçük hop seçimi için
        int round = 0;
        int currentRound = 1;
        int hedefSeqNo = 1;

        double eElec;
        double eMp;
        double eFs;
        double eDa;
        int alfa1;
        int alfa2;
        int thDistance;
        double maxDistanceInTopology;

        double battery;
        double initialBattery;
        bool isBatteryFull = true;
        double consumedEnergy = 0;
        double totalConsumedEnergy = 0;

        int packetSize;
        int dataPacketSize;


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
        void alarm(int malcsNodeIndex);
        void handleAlarm(cMessage *msg);
        void broadcastAlarm(int malcsNodeIndex);
        void broadcast(cMessage *msg);
        void newRound();
        void decreaseBattery(double distance, int msgSendingType, int payload);
        void checkBattery();
};

#endif /* NODE_H_ */
