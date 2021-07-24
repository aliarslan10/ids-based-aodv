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

enum MSG_TYPE{ SENDING, RECEIVING, BROADCAST };
enum ATTACK_MODE { OFF, ON };

class Node : public cSimpleModule {
    private:
        int nodeId;
        int nodeIndex;
        int kaynak;
        int hedef;
        int nodeSayisi;
        int radius, malcsRadius;
        int topolojiX;
        int topolojiY;
        int nodeKordinatX;
        int nodeKordinatY;
        int helloMesajiSayisi = 0;
        int guncelHopSayisi=0, enKucukHop=0, enBuyukHedefSiraNo=0;
        int attackMode;
        int zararliPaketBoyutu;
        int ddosGonderimSayisi;
        int saldiriSayisi = 0;
        string zararlilar;
        bool isHelloSent = false;
        int helloId = 0;

        vector<int> komsu;
        vector<int> routes;
        vector<int> rreqSenders;
        map<string, int> geriRotalama;
        map<string, int> ileriRotalama;
        string neighborsOfMyNeighbors;
        vector<string> neighborsOfNodesOnTheRoute;
        bool setMalcsControllerOnDest = true;
        vector<int> blackList;
        int alarmId;

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

        int packetSize;
        int dataPacketSize;
        int selectedSeed;
        double totalConsumedBatteryStats = 0;
        int maliciousCountThatWeNeedForEachRound = 10;

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
        void setAsNeighbor(int senderNodeIndex);
        void alarm(int malcsNodeIndex);
        void handleUnicastAlarm(cMessage *msg);
        void broadcastAlarm(int malcsNodeIndex);
        void broadcast(cMessage *msg);
        void newRound();
        void startNewRound();
        void decreaseBattery(double distance, int msgSendingType, int payload);
        void checkBattery();
        void sendStatsToBaseStation();

        void setMaliciousNodesIfAttackModeActive(string maliciousCSV);
        vector<int> baseStationMaliciousList;
};

#endif /* NODE_H_ */
