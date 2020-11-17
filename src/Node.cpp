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

    flatTopologyModule = getModuleByPath("FlatTopology");
    nodeSayisi = flatTopologyModule->par("nodeSayisi");
    kaynak = flatTopologyModule->par("kaynak");
    hedef  = flatTopologyModule->par("hedef");
    radius = flatTopologyModule->par("radius");
    minRss = flatTopologyModule->par("minRss");
    avgRss = flatTopologyModule->par("avgRss");
    maxRss = flatTopologyModule->par("maxRss");
    zararliRss = flatTopologyModule->par("zararliRss");
    delayTime = flatTopologyModule->par("delayTime");
    attackMode = flatTopologyModule->par("attackMode");
    zararlilar = flatTopologyModule->par("zararlilar");
    nodeId = this->getId();
    nodeIndex  = this->getIndex();

    stringstream topolojiBoyutuX;
    topolojiBoyutuX << flatTopologyModule->getDisplayString().getTagArg("bgb",0);
    topolojiBoyutuX >> topolojiX; // string değer, integer olan değere atandı.

    stringstream topolojiBoyutuY;
    topolojiBoyutuY << flatTopologyModule->getDisplayString().getTagArg("bgb",1);
    topolojiBoyutuY >> topolojiY;

    // 3. parametre omnet.ini dosyasında yer alan seed-no. toplam 6tane var.
    nodeKordinatX  = intuniform (5,400,RANDOM_NUMBER_GENERATOR);
    nodeKordinatY  = intuniform (5,150,RANDOM_NUMBER_GENERATOR);
    getDisplayString().setTagArg("p", 0, nodeKordinatX);
    getDisplayString().setTagArg("p", 1, nodeKordinatY);
    getDisplayString().setTagArg("r", 0, radius);

    EV << "KONUM : " << nodeKordinatX << " - " << nodeKordinatY << endl;

    if(nodeIndex == kaynak)
        getDisplayString().setTagArg("t", 0, "SOURCE");
    if(nodeIndex == hedef)
        getDisplayString().setTagArg("t", 0, "DEST.");

    rss = intuniform(minRss, maxRss);

    // get malicious nodes and set them in simulation
    if (attackMode == 1) {
        if(Util::isMaliciousNode(zararlilar, nodeIndex)) {
            getDisplayString().setTagArg("t", 0, "MALCS.");
            getDisplayString().setTagArg("i", 1, "YELLOW");
            rss = zararliRss;
        }
    }

    start();
}

void Node::start(){
    cMessage *baslat = new cMessage("BASLAT");
    baslat->addPar("POSX");
    baslat->par("POSX") = nodeKordinatX;
    baslat->addPar("POSY");
    baslat->par("POSY") = nodeKordinatY;
    scheduleAt(simTime()+uniform(0,5), baslat);
}

void Node::handleMessage(cMessage *msg){

    if(msg != nullptr){

        if (strcmp(msg->getName(), "WAKE_AND_CHECK_MALCS_ON_DEST") == 0){
            if(receivedRreqCount != komsu.size()) {
                vector<int> malcs = Util::checkMaliciousNodes(komsu, rreqSenders);
                for (int i : malcs) {
                    EV << "MLCS : " << i << " - alarm üretilecek "<< endl;
                }
            }
        }

        if (strcmp(msg->getName(), "BASLAT") == 0){

           EV << "Hello Mesajı İle Komşular Belirleniyor.." << endl;

           cMessage *hello = new cMessage("HELLO");
           hello->addPar("HELLO_X");
           hello->par("HELLO_X") = msg->par("POSX").doubleValue();
           hello->addPar("HELLO_Y");
           hello->par("HELLO_Y") = msg->par("POSY").doubleValue();
           hello->addPar("HELLO_INDEX");
           hello->par("HELLO_INDEX") = nodeIndex;
           hello->addPar("HELLO_NODE_ID");
           hello->par("HELLO_NODE_ID") = nodeId;
           hello->addPar("RSS");
           hello->par("RSS") = rss;
           hello->addPar("SENDING_TIME");
           hello->par("SENDING_TIME") = simTime().dbl();
           EV << "Gönderdiğim RSS " << rss << endl;
           cModule *node;

           for (int i = 0; i < nodeSayisi; i++) // sistemdeki dugumlere yollanacak.
           {
                node = flatTopologyModule->getSubmodule("nodes", i);
                sendDirect(hello, node, "inputGate");
                hello = hello->dup();
            }
        }


        if (strcmp(msg->getName(), "HELLO") == 0 && nodeIndex != msg->par("HELLO_INDEX").doubleValue()){
            handleHello(msg);
        }


        if(strcmp(msg->getName(), "DATA") == 0){

            EV << "VERİ ALINDI" << endl;
            EV << "GONDEREN ID   : "<< msg->par("NODE_ID").doubleValue() << endl;
            EV << "GONDEREN INDEX: "<< msg->par("NODE_INDEX").doubleValue() << endl;

            if(nodeIndex != hedef)
                this->sendData("DATA");
            else
                EV << "VERİ BAŞARIYLA ALINDI." << endl;
        }

         if(AODVMesajPaketiTipi::RREQ)
             handleRREQ(dynamic_cast<AODVRREQ*>(msg)); // alternatif : check_and_cast<AODVRREQ*>(msg)

         if(AODVMesajPaketiTipi::RREP)
             handleRREP(dynamic_cast<AODVRREP*>(msg));
    }
}

void Node::handleHello(cMessage *msg){

    int senderIndex = msg->par("HELLO_INDEX");
    int senderId = msg->par("HELLO_NODE_ID");
    int gelenX = msg->par("HELLO_X");
    int gelenY = msg->par("HELLO_Y");
    int receivedRss = msg->par("RSS");
    double sendingTime = msg->par("SENDING_TIME");

    EV <<  "HANDLE HELLO - GELEN RSS: " << receivedRss << endl;

    double uzaklik = Util::calculateDistance(nodeKordinatX, nodeKordinatY, gelenX, gelenY);

    EV << "Uzaklık : " << uzaklik << endl;
    EV << " -- NODE::INDEX " << nodeIndex << " -- X::Y " << nodeKordinatX << "-" << nodeKordinatY << endl;
    EV << " -- SENDER::NODE::INDEX " << senderIndex << " -- X::Y " << gelenX << "-" << gelenY << endl;

    if(uzaklik < radius && senderIndex != nodeIndex) {
        this->setAsNeighbor(senderIndex);
    }

    ////////
    //// BURADAKİ MAGIC NUMBER IMPLEMENTE EDİLECEK
    ///////
    if (senderIndex == 4 || senderIndex == 8) { // magic no for demo. it's malcs.
        int tolerance = uzaklik - 50; // magic no for demo. it's tolerance no.
        if (tolerance < radius)
            this->setAsNeighbor(senderIndex);
    }

    if(nodeIndex == kaynak) {

        helloMesajiSayisi++;

        /**
         * tüm komşulardan alana kadar, kendisi hariç
         * herkesten hello mesajı aldıysa artık komsuları bellidir.
         */
        if(helloMesajiSayisi == nodeSayisi-1) {

            EV << "ROTA KEŞFİ BAŞLATILIYOR..." << endl << endl;
            rreqId  = uniform(0,999); // first assign
            scheduleStart(simTime()+uniform(500,1000));
            this->RREQ();
        }
    }
}

void Node::RREQ() {

    EV << "RREQ Gönderiliyor..." << endl;

    AODVRREQ *rreq = new AODVRREQ("RREQ");
    rreq->setKaynakAdr(kaynak);
    rreq->setRreqId(rreqId);
    rreq->setHedefAdr(hedef);
    rreq->setHopCount(guncelHopSayisi);
    rreq->setHedefSeqNo(1);
    rreq->addPar("NODE_INDEX").setDoubleValue(nodeIndex);

    cModule *node;
    for (int i : komsu)
    {
       node = flatTopologyModule->getSubmodule("nodes", i);

        EV << "Komşu Index : " <<  i << endl;

        sendDirect(rreq, node, "inputGate");
        rreq = rreq->dup();
    }
}

void Node::handleRREQ(AODVRREQ *rreq) {

    if (rreq != nullptr) {

        int senderIndex = (int) rreq->par("NODE_INDEX").doubleValue();
        vector<int>::iterator it = std::find(komsu.begin(), komsu.end(), senderIndex);

        /**
         * Eğer komsu listemde varsa handle et. Yoksa handle etme.
         * Hello zararlısının yaptığı şey de bu aslında.
         * Kendini komsu gibi gösterip, kendisine gönderilen paketlerin boşluğa gitmesi.
         */
        if (it != komsu.end()) {

            guncelHopSayisi = rreq->getHopCount() + 1;
            rreqSenders.push_back(senderIndex);
            receivedRreqCount = rreqSenders.size();

            if (nodeIndex == hedef) {

                if (receivedRreqCount <= komsu.size()) {

                    EV << "###### HEDEF NodeE GELEN PAKETLER KARŞILAŞTIRILIYOR! ######" << endl;

                    if (enKucukHop > guncelHopSayisi || enKucukHop == 0) {

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
                    EV << "Hedef Komsu Sayısı ::: " << komsu.size() << endl;

                    if(receivedRreqCount == komsu.size()) { // Node seçimi tamamlandıktan sonra burası çalışacak

                        EV << "###### GERİ ROTALAMA TAMAMLANDI! ######" << endl << "-------------------------" << endl;
                        EV << "İlk RREP Gönderilecek Nodeün Index Bilgisi : " << geriRotalama["sonraki"] << endl;

                        this->RREP();
                        cMessage *msg = new cMessage("WAKE_AND_CHECK_MALCS_ON_DEST");
                        cancelAndDelete(msg); // planlanmış scheduleAt eventini siler
                    }

                    if (setMalcsControllerOnDest) {
                        setMalcsControllerOnDest = false;
                        cMessage *msg = new cMessage("WAKE_AND_CHECK_MALCS_ON_DEST");
                        double delay = 0.1 * komsu.size();
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
            EV << "RREQ bana gönderildi ama ben zararlıyım ve bu paket boşa gitti" << endl;
        }
    }
}

void Node::RREP() {

    EV << "RREP Gönderiliyor..." << endl;

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

            EV << "RREP ALINDI.. " << "İLERİ ROTALAMA TABLOSU" << endl << "-------------------------------------" << endl;
            ileriRotalama["kaynak"]      = rrep->getHedefAdr();
            ileriRotalama["hedef"]       = rrep->getKaynakAdr();
            ileriRotalama["hedefSeqNo"]  = rrep->getHedefSeqNo();
            ileriRotalama["hopSayisi"]   = guncelHopSayisi;
            ileriRotalama["sonraki"]     = rrep->par("NODE_INDEX");

            int senderIndex = (int) rrep->par("NODE_INDEX").doubleValue();

            EV << "kayank " << senderIndex << endl;
            EV << "hedef " << hedef << endl;

            if (senderIndex != hedef && komsu.size() != rreqSenders.size()) {
                vector<int> malcs = Util::checkMaliciousNodes(komsu, rreqSenders);
                for (int i : malcs) {
                    EV << "MLCS : " << i << " - alarm üretilecek "<< endl;
                }
            } else {
                this->RREP();
            }


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
void Node::sendData(const char* msg) {

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
