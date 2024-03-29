/*
 * node.cpp
 *
 *  Created on: Jun 27, 2020
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
    sources = flatTopologyModule->par("sources").stringValue();
    destination  = flatTopologyModule->par("destination");
    radius = flatTopologyModule->par("radius");
    malcsRadius = flatTopologyModule->par("malcsRadius");
    minRSS = flatTopologyModule->par("minRss");
    avgRSS = flatTopologyModule->par("avgRss");
    maxRSS = flatTopologyModule->par("maxRss");
    malcsRSS = flatTopologyModule->par("malcsRSS");
    delayTime = flatTopologyModule->par("delayTime");
    attackMode = flatTopologyModule->par("attackMode");
    malcsNodes = flatTopologyModule->par("malcsNodes");
    packetSize = flatTopologyModule->par("packetSize");
    dataPacketSize = flatTopologyModule->par("dataPacketSize");
    selectedSeed = flatTopologyModule->par("selectedSeed");
    initialBattery = node->par("battery").doubleValue();
    battery = initialBattery;
    sourceVector = Util::stringToVector(sources);

    topolojiX = flatTopologyModule->par("constraintAreaX");
    topolojiY = flatTopologyModule->par("constraintAreaY");

    maxDistanceInTopology = Util::calculateDiagonalDistance(topolojiX, topolojiY);

    // 3. parametre omnet.ini dosyasında yer alan seed-no. toplam 6tane var.
    nodeKordinatX  = intuniform (5, topolojiX, selectedSeed);
    nodeKordinatY  = intuniform (5, topolojiY, selectedSeed);
    getDisplayString().setTagArg("p", 0, nodeKordinatX);
    getDisplayString().setTagArg("p", 1, nodeKordinatY);


    // will cause suspicious node activity
    rss = intuniform(minRSS, maxRSS);
    EV << "RSS VALUE : " << rss << endl;

    // get malicious nodes and set them in simulation
    if (attackMode == ATTACK_MODE::ON) {
        if(Util::isMaliciousNode(malcsNodes, nodeIndex)) {
            getDisplayString().setTagArg("t", 0, "MALCS.");
            getDisplayString().setTagArg("i", 1, "YELLOW");
            radius = malcsRadius;
            rss = malcsRSS;
        } else if(rss > avgRSS) {
            getDisplayString().setTagArg("t", 0, "SUSPICIOUS");
            int randomNumberGeneratorSeed = 4;
            delaySuspicious = 0.4;
            EV << "SUSPCS DELAY : " << delaySuspicious << endl;
        }
    }

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
     * BASE WILL START TO SIMULATION - ROUND 1
     */
    if(nodeIndex == destination) {
        rss = avgRSS; // destination shouldn't be malcs or suspcs.
        getDisplayString().setTagArg("t", 0, "BASE STATION");
        getDisplayString().setTagArg("i", 0, "device/antennatower");
        getDisplayString().setTagArg("is",0, "m");
        this->start();
    }
}

void Node::start() {
    cMessage *start = new cMessage("START");
    this->broadcast(start);
}

void Node::newRound() {

    round++;

    if (nodeIndex == source)
        getDisplayString().removeTag("t");

    source = sourceVector[round % sourceVector.size()];

    if (nodeIndex == source) {
        getDisplayString().setTagArg("t", 0, "SOURCE");
        rreqId++;
        hedefSeqNo++;
    }

    // FOR BASE STATION
    rreqSenders.clear();
    sendStatsToBaseStation();

    EV << "::::::::::: ROUND " << round << " IS STARTING :::::::::::";
    EV << "::::::::::: NEW SOURCE " << source;
    EV << "::::::::::: RREQ ID " << rreqId << endl;
}

void Node::handleMessage(cMessage *msg) {

    if(msg != nullptr && isBatteryFull) {

        this->decreaseBattery(0, MSG_TYPE::RECEIVING, packetSize);

        if (strcmp(msg->getName(), "START") == 0) {
            this->newRound();
            if (nodeIndex == source)
                round == 1 ? this->sendHello() : this->RREQ();
        }

        if (strcmp(msg->getName(), "HELLO") == 0 && this->nodeIndex != msg->par("INDEX").doubleValue()) {
            handleHello(msg);
        }


        if(strcmp(msg->getName(), "DATA") == 0){

            EV << "DATA RECEIVED" << endl;
            EV << "SENDER ID   : "<< msg->par("NODE_ID").doubleValue() << endl;
            EV << "SENDER INDEX: "<< msg->par("NODE_INDEX").doubleValue() << endl;

            if(nodeIndex != destination) {
                this->sendData("DATA");
            } else {
                EV << "DATA RECEIVED BY BASE STATION." << endl;
                EV << "NEW ROUND IS STARTING..." << endl;
                this->start();
            }
        }

        /* ########## CHECK SUSPICIOUS NODE ########## */
        if(strcmp(msg->getName(), "TEST_MSG") == 0){
            cMessage *testMsgResp = new cMessage("TEST_MSG_RESP");
            int msgSenderIndex =  msg->par("TEST_MSG_SENDER_INDEX");
            EV <<  "I GOT TEST_MSG FROM " << msgSenderIndex << endl;
            testMsgResp->addPar("DELAY").setDoubleValue(delaySuspicious);
            testMsgResp->addPar("TEST_RESP_MSG_SENDER_INDEX").setDoubleValue(nodeIndex);
            (delaySuspicious > delayTime) ? getDisplayString().setTagArg("t", 0, "MALCS.") : getDisplayString().removeTag("t");
            this->send(testMsgResp, msgSenderIndex);
        }

        if(strcmp(msg->getName(), "TEST_MSG_RESP") == 0){
            double delay =  msg->par("DELAY").doubleValue();
            int sender = msg->par("TEST_RESP_MSG_SENDER_INDEX");
            EV <<  "I GOT TEST_MSG_RESP FROM " << sender << endl;
            EV << "DELAY : " << delay << " //// SENDER : " << sender << endl;
            if (delay < delayTime) this->setAsNeighbor(sender);
            if (isWaitingForTestMsgResponse && nodeIndex == source) {
                cout << "start new rreq from here" << endl;
                EV << "start new rreq from here" << endl;
                isWaitingForTestMsgResponse = false;
                this->RREQ();
            }
        }
        /* ########## END - CHECK SUSPICIOUS NODE ########## */

        if(strcmp(msg->getName(), "STATS") == 0 && nodeIndex == destination) {
            totalConsumedBatteryStats += msg->par("CONSUMED_BATTERY").doubleValue();;
            EV << "ROUND : " << round << " CONSUMED ENERGY STAT - LITERATURE : " << totalConsumedBatteryStats << endl;
        }

         if(AODVMesajPaketiTipi::RREQ && strcmp(msg->getName(), "RREQ") == 0)
             handleRREQ(dynamic_cast<AODVRREQ*>(msg)); // alternatif : check_and_cast<AODVRREQ*>(msg)

         if(AODVMesajPaketiTipi::RREP)
             handleRREP(dynamic_cast<AODVRREP*>(msg));
    }

    cout << "msg name : " << msg->getName() << endl;

    delete msg;
}


void Node::sendHello() {

    if (!isHelloSent) {
        cMessage *hello = new cMessage("HELLO");
        hello->addPar("ABSCISSA").setDoubleValue(this->nodeKordinatX);
        hello->addPar("ORDINATE").setDoubleValue(this->nodeKordinatY);
        hello->addPar("INDEX").setDoubleValue(this->nodeIndex);
        hello->addPar("RADIUS").setDoubleValue(this->radius);
        hello->addPar("RSS").setDoubleValue(this->rss);
        hello->addPar("TIME").setDoubleValue(simTime().dbl());

        this->broadcast(hello);

        isHelloSent = true;
    }
}

void Node::handleHello(cMessage *msg){

    cout << nodeIndex << " - I received hello " << endl;

    int senderIndex = msg->par("INDEX");
    int senderCoordinateX = msg->par("ABSCISSA");
    int senderCoordinateY = msg->par("ORDINATE");
    int senderRadius = msg->par("RADIUS");
    int senderRSS = msg->par("RSS");
    double sentTime = msg->par("TIME");

    double distance = Util::calculateTwoNodeDistance(nodeKordinatX, nodeKordinatY, senderCoordinateX, senderCoordinateY);

    EV << "SENDER NODE ::: " << senderIndex << endl;
    EV << "DISTANCE :::::: " << distance << endl;
    EV << "SENDER RADIUS : " << senderRadius << endl;

    if(distance < senderRadius && senderIndex != this->nodeIndex) {
        if(!isHelloAttack(senderRSS, senderIndex, sentTime)) {
            this->setAsNeighbor(senderIndex);
        }
    }

    if(nodeIndex == source) {

        helloMesajiSayisi++;

        if (helloMesajiSayisi == nodeSayisi-1 && !isWaitingForTestMsgResponse) {

            EV << this->nodeIndex << " ::: RREQ STARTED :::" << endl << endl;
            scheduleStart(simTime()+uniform(500,1000));  // wait and start RREQ
            this->RREQ();
        }
    } else {
        cout << nodeIndex << " - I SHOULD SEND HELLO! " << endl;
        this->sendHello();
    }
}

void Node::setAsNeighbor(int senderIndex){
    bool isThere = false;
    for(int nodeIndex : komsu){
        if(nodeIndex == senderIndex){
            isThere = true;
        }
    }

    if(!isThere){
        komsu.push_back(senderIndex);
    }

    EV << "::::::::: LAST SENDER ::::::::" << senderIndex << endl;
    EV << "--------- NEIGH. LIST --------" << endl;
    for(int nodeIndex : komsu){
        EV << "NEIGHBOUR INDEX = " <<  nodeIndex << endl;
    }
    EV << "--------- END --------" << endl;
}

bool Node::isHelloAttack(int senderRSS, int senderIndex, double sentTime) {

    if (attackMode == ATTACK_MODE::OFF) return false;

    // malcs.
    if(senderRSS > maxRSS) {
        EV << "MALICIOUS NODE IS DETECTED : " << senderIndex << endl;
        return true;

      // suspicious
    } else if(senderRSS > avgRSS) {

        EV << "senderRSS BIGGER THAN avgRSS " << senderRSS << " < " << avgRSS << endl;
        EV << ":::: SUSPICIOUS NODE DETECTED :::: " << senderIndex << endl;
        EV << ":::: I AM SENDING MSG TO SUSPICIOUS :::: " << senderIndex << endl;
        EV << "SENDING TIME" << sentTime << endl;
        EV << "CURRENT TIME" << simTime().dbl() << endl;

        cMessage *testMsg = new cMessage("TEST_MSG");
        testMsg->addPar("TEST_MSG_SENDER_INDEX").setDoubleValue(nodeIndex);

        if (nodeIndex == source) isWaitingForTestMsgResponse = true;

        this->send(testMsg, senderIndex);

        return true;
    }

    return false;
}

void Node::RREQ(){

    cout << "RREQ() is triggered. Round : " << round << endl;

    AODVRREQ *rreq = new AODVRREQ("RREQ");
    rreq->setKaynakAdr(source);
    rreq->setRreqId(rreqId);
    rreq->setHedefAdr(destination);
    rreq->setHopCount(guncelHopSayisi);
    rreq->setHedefSeqNo(1);
    rreq->addPar("NODE_INDEX");
    rreq->par("NODE_INDEX") = nodeIndex;

    cModule *node;

    for (int i : komsu) {

        node = flatTopologyModule->getSubmodule("nodes", i);

        EV << "RREQ SENT TO : " <<  i << endl;

        sendDirect(rreq, node, "inputGate");
        rreq = rreq->dup();
    }

    this->decreaseBattery(0, MSG_TYPE::BROADCAST, packetSize);
}


void Node::handleRREQ(AODVRREQ *rreq) {

    cout << nodeIndex << " - handleRREQ() is called. Round : " << round << endl;

    if (rreq != nullptr) {

        int senderIndex = (int) rreq->par("NODE_INDEX").doubleValue();
        string senderNode = to_string(senderIndex);
        vector<int>::iterator it = std::find(komsu.begin(), komsu.end(), senderIndex);

        EV << " SENDER NODE INDEX " << senderIndex << endl;
        EV << " I GOT RREQ and I AM " << this->nodeIndex << endl;

        /**
         * Eger komsu listemde varsa handle et. Yoksa handle etme.
         * Hello zararlisinin yaptigi sey de bu aslinda.
         * Kendini komsu gibi gosterip, kendisine gonderilen paketlerin bosa gitmesi.
         * tek tarafin komsuya eklemesi durumu
         */
        if (it != komsu.end()) {

            guncelHopSayisi = rreq->getHopCount() + 1;
            rreqSenders.push_back(senderIndex);
            receivedRreqCount = rreqSenders.size();

            if (nodeIndex == destination) {

                if (receivedRreqCount <= komsu.size()) {


                    if (enKucukHop > guncelHopSayisi || enKucukHop == 0) {

                        enKucukHop = guncelHopSayisi;

                        geriRotalama["kaynak"]      = rreq->getKaynakAdr();
                        geriRotalama["hedef"]       = rreq->getHedefAdr();
                        geriRotalama["hedefSeqNo"]  = rreq->getHedefSeqNo();
                        geriRotalama["hopSayisi"]   = enKucukHop;
                        geriRotalama["sonraki"]     = rreq->par("NODE_INDEX").doubleValue();
                        geriRotalama["hedefSeqNo"]  = rreq->getHedefSeqNo();

                    } else if (enBuyukHedefSiraNo < rreq->getHedefSeqNo()) {

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
                    EV << "Hedef Komsu Sayısı ::: " << komsu.size() << endl;

                    if(receivedRreqCount == komsu.size()){ // Node secimi tamamlandiktan sonra burasi calisicak

                        EV << "###### GERİ ROTALAMA TAMAMLANDI! ######" << endl << "-------------------------" << endl;
                        EV << "İlk RREP Gönderilecek Node Index : " << geriRotalama["sonraki"] << endl;

                        this->RREP(); // hedef ilk RREP mesajini buradan tetikliyor.
                        //endSimulation();
                    }

                } else { cout << "rreq and neighbour count mismatch!" << endl; }

            } else {

               if(rreqId != rreq->getRreqId() && nodeIndex != source){

                    geriRotalama["kaynak"]      = rreq->getKaynakAdr();
                    geriRotalama["hedef"]       = rreq->getHedefAdr();
                    geriRotalama["hedefSeqNo"]  = rreq->getHedefSeqNo();
                    geriRotalama["hopSayisi"]   = guncelHopSayisi;
                    geriRotalama["sonraki"]     = rreq->par("NODE_INDEX");
                    geriRotalama["hedefSeqNo"]  = rreq->getHedefSeqNo();

                    EV << "ARA NODE GERİ ROTALAMA TABLOSU " << endl << "-------------------------" << endl;
                    EV << "KAYNAK  INDEX:" << geriRotalama["kaynak"] << endl;
                    EV << "HEDEF   INDEX:" << geriRotalama["hedef"] << endl;
                    EV << "SONRAKI INDEX:" << geriRotalama["sonraki"] << endl;
                    EV << "HOP SAYISI   :" << geriRotalama["hopSayisi"] << endl;

                    EV << "Rota tablosunu oluşturdum. Ben de aynı mesajı broadcast ediyorum..." << endl;

                    rreqId = rreq->getRreqId();
                    this->RREQ();
               }
            }
        }

    } else {
        EV <<  this->nodeIndex << " :: RREQ bana gonderildi ama benim komsu listemde boyle bir node yok veya zararli. " << endl;
    }
}


void Node::RREP(){

    EV << "RREP Gonderiliyor..." << endl;

    AODVRREP *rrep = new AODVRREP("RREP");
    rrep->setKaynakAdr(destination);
    rrep->setHedefAdr(source);
    rrep->setHopCount(guncelHopSayisi);
    rrep->setHedefSeqNo(2); // Sadece ilk RREP tarafından arttırılabilir.
    rrep->addPar("NODE_INDEX");
    rrep->par("NODE_INDEX") = nodeIndex;

    this->send(rrep, geriRotalama["sonraki"]);
    this->decreaseBattery(0, MSG_TYPE::SENDING, packetSize);
}

void Node::handleRREP(AODVRREP *rrep){

    if(rrep != nullptr){

        if (nodeIndex != source) {

            EV << "RREP ALINDI.. " << "İLERİ ROTALAMA TABLOSU" << endl << "-------------------------------------" << endl;
            ileriRotalama["kaynak"]      = rrep->getHedefAdr();
            ileriRotalama["hedef"]       = rrep->getKaynakAdr();
            ileriRotalama["hedefSeqNo"]  = rrep->getHedefSeqNo();
            ileriRotalama["hopSayisi"]   = guncelHopSayisi;
            ileriRotalama["sonraki"]     = rrep->par("NODE_INDEX");

            RREP();

        } else {
            ileriRotalama["kaynak"]      = rrep->getHedefAdr();
            ileriRotalama["hedef"]       = rrep->getKaynakAdr();
            ileriRotalama["hedefSeqNo"]  = rrep->getHedefSeqNo();
            ileriRotalama["hopSayisi"]   = guncelHopSayisi;
            ileriRotalama["sonraki"]     = rrep->par("NODE_INDEX");

            EV << "ROTA KEŞFİ TAMAMLANDI. KAYNAK VERİYİ GÖNDERİLİYOR..." << endl;
            this->sendData("DATA");
        }
    }
}

/*
 * It sends message from source to destination through route
 */
void Node::sendData(const char* msg){

    cMessage *message = new cMessage(msg);
    message->addPar("NODE_INDEX");
    message->par("NODE_INDEX") = nodeIndex;
    message->addPar("NODE_ID");
    message->par("NODE_ID") = nodeId;
    this->send(message, ileriRotalama["sonraki"]);
}

void Node::send(cMessage *msg, int receiver) {
    cModule *node = flatTopologyModule->getSubmodule("nodes", receiver);
    sendDirect(msg, node, "inputGate");
    this->decreaseBattery(radius, MSG_TYPE::SENDING, packetSize); // default dist.: radius
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
    if (battery < (initialBattery * 0.05) && this->nodeIndex != destination) {
        isBatteryFull = false;
        getDisplayString().parse("i=block/circle,black;is=vs;t=DIED");
        EV << "Battery Finished : " << this->nodeIndex << endl;
    }
}

void Node::sendStatsToBaseStation() {
    if (nodeIndex != destination && !Util::isMaliciousNode(malcsNodes, nodeIndex)) {
        cMessage *stats = new cMessage("STATS");
        stats->addPar("CONSUMED_BATTERY").setDoubleValue(totalConsumedEnergy);
        this->send(stats, destination);
    }
}
