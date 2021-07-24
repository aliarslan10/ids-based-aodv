/*
 * node.cpp
 *
 *  Created on: Oct 12, 2020
 *  Author: aliarslan
 */


#include "AODVMsgPacket_m.h"
#include "Node.h"
#include "Util.h"

Define_Module(Node);

void Node::initialize(){

    node = getModuleByPath(this->getFullPath().c_str());
    nodeId = this->getId();
    nodeIndex  = this->getIndex();

    flatTopologyModule = getModuleByPath("FlatTopology");
    nodeSayisi = flatTopologyModule->par("nodeSayisi");
    kaynak = flatTopologyModule->par("kaynak");
    hedef  = flatTopologyModule->par("hedef");
    radius = flatTopologyModule->par("radius");
    malcsRadius = flatTopologyModule->par("malcsRadius");
    attackMode = flatTopologyModule->par("attackMode");
    //zararlilar = flatTopologyModule->par("zararlilar");
    packetSize = flatTopologyModule->par("packetSize");
    dataPacketSize = flatTopologyModule->par("dataPacketSize");
    selectedSeed = flatTopologyModule->par("selectedSeed");
    maliciousCountThatWeNeedForEachRound = flatTopologyModule->par("maliciousForEachRound");
    initialBattery = node->par("battery").doubleValue();
    battery = initialBattery;

    EV << "BATTERY : " << initialBattery << endl;

    topolojiX = flatTopologyModule->par("constraintAreaX");
    topolojiY = flatTopologyModule->par("constraintAreaY");

    maxDistanceInTopology = Util::calculateDiagonalDistance(topolojiX, topolojiY);

    // 3. parametre omnet.ini dosyasında yer alan seed-no. toplam 6tane var.
    nodeKordinatX  = intuniform (5, topolojiX, selectedSeed);
    nodeKordinatY  = intuniform (5, topolojiY, selectedSeed);
    getDisplayString().setTagArg("p", 0, nodeKordinatX);
    getDisplayString().setTagArg("p", 1, nodeKordinatY);

    getDisplayString().setTagArg("r", 0, radius);

    /*
     * GET LEACH ENERGY MODEL PARAMETERS
     */
    eElec = flatTopologyModule->par("eElec").doubleValue();
    eMp = flatTopologyModule->par("eMp").doubleValue();
    eFs = flatTopologyModule->par("eFs").doubleValue();
    eDa = flatTopologyModule->par("eDa").doubleValue();
    alfa1 = flatTopologyModule->par("alfa1");
    alfa2 = flatTopologyModule->par("alfa2");
    thDistance = flatTopologyModule->par("thDistance");

    /**
     * SET RANDOM SOURCE NODE
     */
    //kaynak = Util::randomNumberGenerator(0, nodeSayisi);
    if(nodeIndex == kaynak) {
        EV << "kaynak : " << kaynak << endl;
        getDisplayString().setTagArg("t", 0, "SOURCE");
    }

    /**
     * BASE WILL START TO SIMULATION - ROUND 1
     */
    if(nodeIndex == hedef) {
        getDisplayString().setTagArg("t", 0, "BASE STATION");
        getDisplayString().setTagArg("i", 0, "device/antennatower");
        getDisplayString().setTagArg("is",0, "m");
        zararlilar = flatTopologyModule->par("zararlilar").stringValue();
        baseStationMaliciousList = Util::csvToVector(zararlilar);
        this->start();
    }
}

void Node::setMaliciousNodesIfAttackModeActive(string maliciousCSV) {
    if (attackMode == ATTACK_MODE::ON) {
        if(Util::isMaliciousNode(maliciousCSV, nodeIndex)) {
            EV << " MALICIOUS -->" << nodeIndex << endl;
            getDisplayString().setTagArg("t", 0, "MALCS.");
            getDisplayString().setTagArg("i", 1, "YELLOW");
            radius = malcsRadius;
        }
    }
}

void Node::start() {
    cMessage *start = new cMessage("START");
    if (baseStationMaliciousList.size() > 0) {
        vector<int> maliciousList = Util::selectRandomValues(baseStationMaliciousList, maliciousCountThatWeNeedForEachRound);
        zararlilar = Util::vectorToCSV(maliciousList);
        baseStationMaliciousList = Util::updateVector(baseStationMaliciousList, maliciousList);
    }
    cout << "xxxx zararlilar xxxxx" << zararlilar << endl;
    start->addPar("MALICIOUS").setStringValue(zararlilar.c_str());
    this->broadcast(start);
}

void Node::handleMessage(cMessage *msg) {

    if(msg != nullptr && isBatteryFull) {

        this->decreaseBattery(0, MSG_TYPE::RECEIVING, packetSize);

        if (strcmp(msg->getName(), "WAKE_AND_CHECK_MALCS_ON_DEST") == 0) {

            cout << "BASE STATION WILL CREATE ALARM" << endl;
            cout << "BASE STATION WILL CREATE ALARM" << receivedRreqCount << endl;
            cout << "BASE STATION WILL CREATE ALARM" << komsu.size() << endl;

            //// ZARARLI RREQ GONDERDI. ALARM O YUZDEN FIRLAMIYOR!!!
            if(receivedRreqCount != komsu.size()) {
                vector<int> malcs = Util::checkMaliciousNodes(komsu, rreqSenders);

                // TODO: broadcast one alarm for multi malcious
                if (malcs.size() > 0) {

                    for (int malicious : malcs) {
                        komsu.erase(std::remove(komsu.begin(), komsu.end(), malicious), komsu.end());
                        Node::alarm(malicious);
                    }

                    /// removing it from neighb's list is enough. no need to create an alarm.

                    // send RREP to legal node - for now it will send first element of the node
                    // TODO: should send to node which has shortest path and has least hop-count
                    geriRotalama["sonraki"] = komsu[0];
                    this->RREP();
                }
            }
        }


        if (strcmp(msg->getName(), "UNICAST_ALARM") == 0){
            Node::handleUnicastAlarm(msg);
        }

        if (strcmp(msg->getName(), "BROADCAST_ALARM") == 0){
            int malcsNodeIndex = (int) msg->par("MLCS_NODE_INDEX").doubleValue();
            blackList.push_back(malcsNodeIndex);
            komsu.erase(std::remove(komsu.begin(), komsu.end(), malcsNodeIndex), komsu.end());
            EV << nodeIndex << " i removed malicious from my neighbours : " << malcsNodeIndex << endl;
        }


        if (strcmp(msg->getName(), "START") == 0) {
            zararlilar = msg->par("MALICIOUS").stringValue();
            this->setMaliciousNodesIfAttackModeActive(zararlilar);
            this->newRound();
        }

        if (strcmp(msg->getName(), "HELLO") == 0 && this->nodeIndex != msg->par("NODE_INDEX").doubleValue()) {
            /**
             * if attack mode is off: all nodes will handle hello message anyway.
             * if attack mode is on : only legal nodes will care the hello message.
             * in else case : malicious will send hello but it never handle the helloMsg.
             */
            if (attackMode == ATTACK_MODE::OFF)
                handleHello(msg);
            else if (!Util::isMaliciousNode(zararlilar, nodeIndex)) /// !!!!!!!!!SORUN BURADA!!!!!!!!!!!!!
                handleHello(msg);
            else
                this->sendHello();
        }


        if(strcmp(msg->getName(), "DATA") == 0) {

            EV << "DATA RECEIVED" << endl;
            EV << "SENDER ID   : "<< msg->par("NODE_ID").doubleValue() << endl;
            EV << "SENDER INDEX: "<< msg->par("NODE_INDEX").doubleValue() << endl;

            if(nodeIndex != hedef) {
                this->sendData("DATA");
            } else {
                EV << "DATA RECEIVED BY BASE STATION." << endl;
                EV << "NEW ROUND IS STARTING..." << endl;
                this->start();
            }
        }

        if(strcmp(msg->getName(), "STATS") == 0 && nodeIndex == hedef) {
            double consumedBattery = msg->par("CONSUMED_BATTERY").doubleValue();
            totalConsumedBatteryStats += consumedBattery;
            EV << "ROUND : " << round << " CONSUMED ENERGY STAT : " << totalConsumedBatteryStats << endl;
        }

         if(AODVMesajPaketiTipi::RREQ)
             handleRREQ(dynamic_cast<AODVRREQ*>(msg)); // alternatif : check_and_cast<AODVRREQ*>(msg)

         if(AODVMesajPaketiTipi::RREP)
             handleRREP(dynamic_cast<AODVRREP*>(msg));
    }

    delete msg;
}

void Node::sendHello() {

    cout << "\n ------------------------------------------------------------ \n ";
    cout << "ROUND " << round << " helloId Status : " << helloId << endl;
    cout << "\n ------------------------------------------------------------ \n ";

    if (helloId == round) {
        cMessage *hello = new cMessage("HELLO");
        hello->addPar("HELLO_ID").setDoubleValue(helloId);
        hello->addPar("NODE_ABSCISSA").setDoubleValue(this->nodeKordinatX);
        hello->addPar("NODE_ORDINATE").setDoubleValue(this->nodeKordinatY);
        hello->addPar("NODE_INDEX").setDoubleValue(this->nodeIndex);
        hello->addPar("NODE_RADIUS").setDoubleValue(this->radius);

        this->broadcast(hello);
        helloId++;
    }
}

void Node::handleHello(cMessage *msg) {

    int senderIndex = msg->par("NODE_INDEX");
    int senderCoordinateX = msg->par("NODE_ABSCISSA");
    int senderCoordinateY = msg->par("NODE_ORDINATE");
    int senderRadius = msg->par("NODE_RADIUS");

    double distance = Util::calculateTwoNodeDistance(nodeKordinatX, nodeKordinatY, senderCoordinateX, senderCoordinateY);

    EV << "SENDER NODE ::: " << senderIndex << endl;
    EV << "DISTANCE :::::: " << distance << endl;
    EV << "SENDER RADIUS : " << senderRadius << endl;

    if(distance < senderRadius && senderIndex != this->nodeIndex) {
        this->setAsNeighbor(senderIndex);
    }


    if(nodeIndex == kaynak) {

        helloMesajiSayisi++;


        cout << "helloCount " << helloMesajiSayisi << endl;
        cout << "nodeSayisi " << nodeSayisi << endl;


        if(helloMesajiSayisi == nodeSayisi-1) { // helloMesajiSayisi <= nodeSayisi-1

            EV << this->nodeIndex << " ::: RREQ STARTED :::" << "ROUND : " << round << endl;
            scheduleStart(simTime()+uniform(500,1000)); // wait and start RREQ
            this->RREQ();
        }
    } else {
        this->sendHello();
    }
}

void Node::newRound() {

    round++;
    helloId = round;

    // if attackMode is active, then new round will start with hello message
    if (attackMode == ATTACK_MODE::ON) {
        komsu.clear();
        helloMesajiSayisi = 0;
    }

    // FOR BASE STATION
    rreqSenders.clear();
    sendStatsToBaseStation();

    this->checkBattery();
    this->startNewRound();
}

void Node::startNewRound() {

    if (nodeIndex == kaynak) {

        rreqId++;
        hedefSeqNo++;

        if (attackMode == ATTACK_MODE::ON) {
            this->sendHello();
        } else {
            round == 1 ? this->sendHello() : this->RREQ();
        }
    }
    EV << "::::::::::: ROUND " << round << " IS STARTING :::::::::::" << endl;
}

void Node::RREQ() {

    cout << "RREQ() is triggered. Round : " << round << endl;

    AODVRREQ *rreq = new AODVRREQ("RREQ");
    rreq->setKaynakAdr(kaynak);
    rreq->setRreqId(rreqId);
    rreq->setHedefAdr(hedef);
    rreq->setHopCount(guncelHopSayisi);
    rreq->setHedefSeqNo(hedefSeqNo);
    rreq->addPar("NODE_INDEX").setDoubleValue(nodeIndex);
    //rreq->addPar("NEIGHBORS_STORAGE").setStringValue((route).c_str());

    cModule *node;

    // more like unicast
    for (int i : komsu)
    {
       node = flatTopologyModule->getSubmodule("nodes", i);

        EV << "RREQ SENT TO : " <<  i << endl;

        sendDirect(rreq, node, "inputGate");
        rreq = rreq->dup();
    }

    this->decreaseBattery(0, MSG_TYPE::BROADCAST, packetSize);
}

void Node::handleRREQ(AODVRREQ *rreq) {

    if (rreq != nullptr) {

        int senderIndex = (int) rreq->par("NODE_INDEX").doubleValue();
        vector<int>::iterator it = std::find(komsu.begin(), komsu.end(), senderIndex);

        /**
         * Eger komsu listemde varsa handle et. Yoksa handle etme.
         * Hello zararlisinin yaptigi sey de bu aslinda.
         * Kendini komsu gibi gosterip, kendisine gonderilen paketlerin bosluga gitmesi.
         * tek tarafin komsuya eklemesi durumu
         */
        if (it != komsu.end()) {

            cout << nodeIndex << " - handleRREQ() is called. Round : " << round << endl;
            EV << " SENDER NODE INDEX " << senderIndex << endl;
            EV << " I GOT RREQ and I AM " << this->nodeIndex << endl;

            //check rreq on dest
            if (rreqId != rreq->getRreqId() && nodeIndex == hedef && attackMode == ATTACK_MODE::ON) {
                setMalcsControllerOnDest = true;
                rreqSenders.clear();
                rreqId = rreq->getRreqId();
                guncelHopSayisi = 0;
                enBuyukHedefSiraNo = 0;
            }

            guncelHopSayisi = rreq->getHopCount() + 1;
            rreqSenders.push_back(senderIndex);
            receivedRreqCount = rreqSenders.size();

            if (nodeIndex == hedef) {

                EV << "receivedRreqCount - komsu.size " << receivedRreqCount << " - " << komsu.size() << endl;

                if (receivedRreqCount <= komsu.size()) {

                    EV << "###### HEDEFE GELEN PAKETLER KARŞILAŞTIRILIYOR! ######" << endl;

                    EV << "enKucukHop :" << enKucukHop << endl;
                    EV << "guncelHopSayisi:" << guncelHopSayisi << endl;
                    EV << "enBuyukHedefSiraNo :" << enBuyukHedefSiraNo << endl;
                    EV << "rreq->getHedefSeqNo()   :" <<  rreq->getHedefSeqNo() << endl;

                    if (enKucukHop > guncelHopSayisi || enKucukHop == 0) {

                        EV << "###### ilk geri rotalama ###### round " << round<<  endl;

                        enKucukHop = guncelHopSayisi;

                        geriRotalama["kaynak"]      = rreq->getKaynakAdr();
                        geriRotalama["hedef"]       = rreq->getHedefAdr();
                        geriRotalama["hedefSeqNo"]  = rreq->getHedefSeqNo();
                        geriRotalama["hopSayisi"]   = enKucukHop;
                        geriRotalama["sonraki"]     = rreq->par("NODE_INDEX").doubleValue();
                        geriRotalama["hedefSeqNo"]  = rreq->getHedefSeqNo();

                    } else if(enBuyukHedefSiraNo < rreq->getHedefSeqNo()) {

                        enBuyukHedefSiraNo = rreq->getHedefSeqNo();

                        geriRotalama["kaynak"]      = rreq->getKaynakAdr();
                        geriRotalama["hedef"]       = rreq->getHedefAdr();
                        geriRotalama["hedefSeqNo"]  = rreq->getHedefSeqNo();
                        geriRotalama["hopSayisi"]   = guncelHopSayisi;
                        geriRotalama["sonraki"]     = rreq->par("NODE_INDEX").doubleValue();
                        geriRotalama["hedefSeqNo"]  = enBuyukHedefSiraNo;

                    }

                    for(int i=0; i<komsu.size(); i++){
                      EV << "Node INDEX komsu[i] = " <<  komsu[i] << endl;
                    }

                    EV << "HEDEF GERİ ROTALAMA TABLOSU " << endl << "-------------------------" << endl;
                    EV << "KAYNAK  INDEX:" << geriRotalama["kaynak"] << endl;
                    EV << "HEDEF   INDEX:" << geriRotalama["hedef"] << endl;
                    EV << "SONRAKI INDEX:" << geriRotalama["sonraki"] << endl;
                    EV << "HOP SAYISI   :" << geriRotalama["hopSayisi"] << endl;

                    EV << "Her komsudan bir RREQ ::: " << receivedRreqCount << endl;
                    EV << "Hedef Komsu Sayisi ::: " << komsu.size() << endl;

                    if(receivedRreqCount == komsu.size()) {
                        EV << "###### BACK ROUTE DISCOVERED! ######" << endl << "-------------------------" << endl;
                        EV << "RREP IS SENDING TO : " << geriRotalama["sonraki"] << endl;
                        this->RREP();
                    }

                    cout << "setMalcsControllerOnDest" << setMalcsControllerOnDest << endl;
                    cout << "attackMode" << attackMode << endl;

                    if (setMalcsControllerOnDest && attackMode == ATTACK_MODE::ON) {
                        cout << "create WAKE_AND_CHECK_MALCS_ON_DEST" << endl;
                        setMalcsControllerOnDest = false;
                        cMessage *msg = new cMessage("WAKE_AND_CHECK_MALCS_ON_DEST");
                        double delay = 0.1 * komsu.size();
                        cout << "delay ::: " << delay << endl;
                        scheduleAt(simTime()+delay, msg);
                    }

                }

            } else {

               if (rreqId != rreq->getRreqId() && nodeIndex != kaynak) {

                    geriRotalama["kaynak"]      = rreq->getKaynakAdr();
                    geriRotalama["hedef"]       = rreq->getHedefAdr();
                    geriRotalama["hedefSeqNo"]  = rreq->getHedefSeqNo();
                    geriRotalama["hopSayisi"]   = guncelHopSayisi;
                    geriRotalama["sonraki"]     = rreq->par("NODE_INDEX");
                    geriRotalama["hedefSeqNo"]  = rreq->getHedefSeqNo();

                    EV << "ARA Node GERİ ROTALAMA TABLOSU " << endl << "-------------------------" << endl;
                    EV << "KAYNAK  INDEX:" << geriRotalama["kaynak"] << endl;
                    EV << "HEDEF   INDEX:" << geriRotalama["hedef"] << endl;
                    EV << "SONRAKI INDEX:" << geriRotalama["sonraki"] << endl;
                    EV << "HOP SAYISI   :" << geriRotalama["hopSayisi"] << endl;

                    EV << "Rota tablosunu oluşturdum. Ben de aynı mesajı broadcast ediyorum..." << endl;

                    rreqId = rreq->getRreqId();
                    this->RREQ();
               }
            }
        } else {
            EV <<  this->nodeIndex << " :: RREQ bana gönderildi ama benim komsu listemde böyle bir node yok veya zararlı node :( " << endl;
        }
    }
}

void Node::RREP() {

    EV << "RREP SENDING... " << geriRotalama["sonraki"] << endl;
    AODVRREP *rrep = new AODVRREP("RREP");
    rrep->setKaynakAdr(hedef);
    rrep->setHedefAdr(kaynak);
    rrep->setHopCount(guncelHopSayisi);
    rrep->setHedefSeqNo(2); // Sadece ilk RREP tarafından arttırılabilir.
    rrep->addPar("NODE_INDEX").setDoubleValue(nodeIndex);
    this->send(rrep, geriRotalama["sonraki"]);
}

void Node::handleRREP(AODVRREP *rrep) {

    if (rrep != nullptr) {

        if (nodeIndex != kaynak) {

            EV << "RREP ALINDI.. " << "ILERI ROTALAMA TABLOSU" << endl << "-------------------------------------" << endl;
            ileriRotalama["kaynak"]      = rrep->getHedefAdr();
            ileriRotalama["hedef"]       = rrep->getKaynakAdr();
            ileriRotalama["hedefSeqNo"]  = rrep->getHedefSeqNo();
            ileriRotalama["hopSayisi"]   = guncelHopSayisi;
            ileriRotalama["sonraki"]     = rrep->par("NODE_INDEX");

            int senderIndex = (int) rrep->par("NODE_INDEX").doubleValue();

            EV << "kaynak " << senderIndex << endl;
            EV << "hedef " << hedef << endl;
            EV << "komsu.size() " << komsu.size() << endl;
            EV << "rreqSenders.size() " << rreqSenders.size() << endl;

            if (senderIndex != hedef && komsu.size() != rreqSenders.size()) {
                vector<int> malcs = Util::checkMaliciousNodes(komsu, rreqSenders);
                for (int i : malcs) {
                    cout <<  this->nodeIndex << " - handleRREP() >> MALCS:" << i << endl;
                    Node::alarm(i);
                }
            }

            this->RREP();

        } else {
            ileriRotalama["kaynak"]      = rrep->getHedefAdr();
            ileriRotalama["hedef"]       = rrep->getKaynakAdr();
            ileriRotalama["hedefSeqNo"]  = rrep->getHedefSeqNo();
            ileriRotalama["hopSayisi"]   = guncelHopSayisi;
            ileriRotalama["sonraki"]     = rrep->par("NODE_INDEX");

            EV << "ROUTE DISCOVERED. DATA IS BEING SENT..." << endl;
            this->sendData("DATA");
        }
    }
}

/*
 * It sends message from source to destination through route
 */
void Node::sendData(const char* msg) {

    cMessage *message = new cMessage(msg);
    message->addPar("NODE_INDEX");
    message->par("NODE_INDEX") = nodeIndex;
    message->addPar("NODE_ID");
    message->par("NODE_ID") = nodeId;
    this->send(message, ileriRotalama["sonraki"]);
    this->decreaseBattery(0, MSG_TYPE::SENDING, dataPacketSize);
}

void Node::send(cMessage *msg, int receiver) {
    cModule *node = flatTopologyModule->getSubmodule("nodes", receiver);
    sendDirect(msg, node, "inputGate");
    this->decreaseBattery(radius, MSG_TYPE::SENDING, packetSize); // default dist.: radius
}

void Node::setAsNeighbor(int senderIndex) {
    bool isAddedAsNeighbor = false;
    for(int i=0; i<komsu.size(); i++){
        if(komsu[i] == senderIndex){
            isAddedAsNeighbor = true;
        }
    }


    if(!isAddedAsNeighbor){
        komsu.push_back(senderIndex);
    }


    EV << "--------- NEIGH. LIST -------- SIZE ::::: " << komsu.size() << endl;
    for(int i=0; i<komsu.size(); i++){
        EV << "Node INDEX komsu[i] = " <<  komsu[i] << endl;
    }
    EV << "--------- END --------" << endl;
}

// unicast alarm to inform destination
void Node::alarm(int malcsNodeIndex) {
    EV << "Malicious node is detected. MalcsId: " << malcsNodeIndex << endl;
    cMessage *unicastAlarm = new cMessage("UNICAST_ALARM");
    unicastAlarm->addPar("MLCS_NODE_INDEX").setDoubleValue(malcsNodeIndex);
    vector<int>::iterator it = std::find(blackList.begin(), blackList.end(), malcsNodeIndex);
    if (hedef != malcsNodeIndex && alarmId != malcsNodeIndex && it == blackList.end()) { // eger kara listemde yoksa..
        alarmId = malcsNodeIndex;
        if(nodeIndex != hedef) {
            this->send(unicastAlarm, ileriRotalama["sonraki"]);
        } else {
            this->broadcastAlarm(malcsNodeIndex);
        }
    }
}

void Node::handleUnicastAlarm(cMessage *msg) {
    int malcsNodeIndex = (int) msg->par("MLCS_NODE_INDEX").doubleValue();
    if(nodeIndex != hedef) {
        this->alarm(malcsNodeIndex);
    } else {
        this->broadcastAlarm(malcsNodeIndex);
    }
}

// it is used by base station
void Node::broadcastAlarm(int malcsNodeIndex){
    cMessage *alarm = new cMessage("BROADCAST_ALARM");
    alarm->addPar("MLCS_NODE_INDEX").setDoubleValue(malcsNodeIndex);
    Node::broadcast(alarm);
}

void Node::broadcast(cMessage *msg) {
    for (int i = 0; i < nodeSayisi; i++) {
        cModule *node = flatTopologyModule->getSubmodule("nodes", i);
        sendDirect(msg, node, "inputGate");
        msg = msg->dup();
    }

    this->decreaseBattery(0, MSG_TYPE::BROADCAST, packetSize);
}

void Node::decreaseBattery(double distance, int sendingMsgType, int payload) {

    if (sendingMsgType == MSG_TYPE::SENDING) {

        if (distance < thDistance)
            consumedEnergy = eElec * payload + payload * eFs * pow(distance, alfa1);
        else
            consumedEnergy = eElec * payload + payload * eMp * pow(distance, alfa2);

    } else if (sendingMsgType == MSG_TYPE::RECEIVING) {

        consumedEnergy = eElec * payload;

    } else if (sendingMsgType == MSG_TYPE::BROADCAST) {

        if (maxDistanceInTopology < thDistance) {
            consumedEnergy = eElec * payload + payload * eFs * pow(maxDistanceInTopology, alfa1);
        }

        else {
            consumedEnergy = eElec * payload + payload * eMp * pow(maxDistanceInTopology, alfa2);
        }
    } /* else if (tip == BIRLESTIRME) {
        consumedEnergy = E_DA * payload;
    } */

    if (nodeIndex != kaynak)
        battery = battery - consumedEnergy;

    // buna gerek yok gibi.. zaten global olarak "battery" değişkeni var.
    // node->par("battery").setDoubleValue(battery); // parametre degerini degistir

    // varsayılan - round sonunda belli olacak
    if (battery > 0.0001) {

        totalConsumedEnergy += consumedEnergy; // o roundda harcanan enerjiye ekle

        //cout << "------------- NODE 0 STATS --------------";
        //cout << " ROUND : " << round;
        //cout << " NODE INDEX : " << nodeIndex;
        //cout << " MESSAGE TYPE : " << sendingMsgType;
        //cout << " DECREASED : " << consumedEnergy;
        //cout << " TOTAL CONSUMED : " << totalConsumedEnergy;
        //cout << " TOTAL BATTERY : " << initialBattery;
        //cout << " REMANING BATTERY : " << battery;
        //cout << "---------------------------" << endl;

        //diziHarcEnerji[indisEnerji] = consumedEnergy;
        //indisEnerji++;
        // bir düğümün harcadıgı toplam enerji = diziHarcEnerji


        // bu aslında burada yoktu
        // enerji_deger_SN[i][j]=(fullBatarya/diziHarcEnerji[j]);
        // anlamı = [(toplam pil gucu) / (yapilan isin tukettigi enerji)]
        // yani full bataryada ne kadar yemis?
        // total batarya gücünü harcanan güce bölerek,
        // enerjiye bagli guven hesaplaniyor
    }

    this->checkBattery();
}

void Node::checkBattery() {

    cout << " ROUND : " << round;
    cout << " NODE INDEX : " << nodeIndex;
    cout << " DECREASED : " << consumedEnergy;
    cout << " TOTAL CONSUMED : " << totalConsumedEnergy;
    cout << " TOTAL BATTERY : " << initialBattery;
    cout << " REMANING BATTERY : " << battery;

    if (battery < (initialBattery * 0.05) && this->nodeIndex != hedef) {
        isBatteryFull = false;
        getDisplayString().parse("i=block/circle,black;is=vs;t=DIED");
        EV << "Battery Finished : " << this->nodeIndex << endl;
    }
}

void Node::sendStatsToBaseStation() {
    cout << "\n\n sendstattobasestation() :: " << zararlilar << endl;
    if (nodeIndex != hedef && !Util::isMaliciousNode(zararlilar, nodeIndex)) {
        cMessage *stats = new cMessage("STATS");
        stats->addPar("CONSUMED_BATTERY").setDoubleValue(totalConsumedEnergy);
        this->send(stats, hedef);
    }
}




