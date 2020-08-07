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

    flatTopologyModule = getModuleByPath("FlatTopology");
    nodeSayisi = flatTopologyModule->par("nodeSayisi");
    kaynak = flatTopologyModule->par("kaynak");
    hedef  = flatTopologyModule->par("hedef");
    radius = flatTopologyModule->par("radius");
    rss = flatTopologyModule->par("rss");
    zararliRss = flatTopologyModule->par("zararliRss");
    thresholdRss = flatTopologyModule->par("thresholdRss");
    delayTime = flatTopologyModule->par("delayTime");
    attackMode = flatTopologyModule->par("attackMode");
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


    // get malicious nodes and set them in simulation
    if (attackMode == 1) {
        string zararlilar = flatTopologyModule->par("zararlilar");
        if(Util::isMaliciousNode(zararlilar, nodeIndex, zararliRss, rss)) {
            getDisplayString().setTagArg("t", 0, "MALCS.");
            getDisplayString().setTagArg("i", 1, "YELLOW");
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

           cModule *node;

           for (int i = 0; i < nodeSayisi; i++) // sistemdeki dugumlere yollanacak.
           {
                node = flatTopologyModule->getSubmodule("nodes", i);
                sendDirect(hello, node, "inputGate");
                hello = hello->dup();
            }

        }


        /* ########## HELLO MESAJLARI İLE KOMŞU BUL ########## */

        if (strcmp(msg->getName(), "HELLO") == 0 && nodeIndex != msg->par("HELLO_INDEX").doubleValue()){
            handleHello(msg);
        }

        if(strcmp(msg->getName(), "TEST_MSG") == 0){
            EV << ":::: SUPHELI MESAJI ALDI :::: " << nodeId << endl;
            cMessage *testMsgResp = new cMessage("TEST_MSG_RESP");
            testMsgResp->addPar("TEST_MSG_ID");
            int msgSenderId =  testMsgResp->par("TEST_MSG_ID");

            cModule *node = flatTopologyModule->getSubmodule("nodes", msgSenderId);

            EV << "delay" << delayTime << endl;
            EV << "sim tim - 1"  << simTime().dbl() << endl;
            usleep(delayTime);
            EV << "SENDING TIME - 2" << simTime().dbl() << endl;
            EV << "SENDER" << msgSenderId << endl;

            sendDirect(testMsgResp, node, "inputGate");
        }


        if(strcmp(msg->getName(), "TEST_MSG_RESP") == 0){
            EV << "TEST_MSG_RESP -- SUPHELI MSG ATTI --" << endl << endl;
            EV << "CURRENT TIME" << simTime().dbl() << endl;
        }


        /* ########## VERİ GÖNDER ########## */

        if(strcmp(msg->getName(), "DATA") == 0){

            EV << "VERİ ALINDI" << endl;
            EV << "GONDEREN ID   : "<< msg->par("NODE_ID").doubleValue() << endl;
            EV << "GONDEREN INDEX: "<< msg->par("NODE_INDEX").doubleValue() << endl;

            if(nodeIndex != hedef)
                this->sendData();
            else
                EV << "VERİ BAŞARIYLA ALINDI." << endl;
        }


        /* ########## PAKETLERİ YAKALA ########## */

         if(AODVMesajPaketiTipi::RREQ)
             handleRREQ(dynamic_cast<AODVRREQ*>(msg)); // alternatif : check_and_cast<AODVRREQ*>(msg)

         if(AODVMesajPaketiTipi::RREP)
             handleRREP(dynamic_cast<AODVRREP*>(msg));

       //  if(AODVMesajPaketiTipi::RERR)
             //handleRERR(dynamic_cast<AODVRERR*>(msg));

        // if(AODVMesajPaketiTipi::RREP_ACK)
             //handleRREP(dynamic_cast<AODVRREP*>(msg));

         //throw cRuntimeError("tanımsız paket");
    }

}

void Node::handleHello(cMessage *msg){

    int gonderenIndex = msg->par("HELLO_INDEX");
    int gonderenId = msg->par("HELLO_NODE_ID");
    int gelenX = msg->par("HELLO_X");
    int gelenY = msg->par("HELLO_Y");
    int gelenRss = msg->par("RSS");
    double sendingTime = msg->par("SENDING_TIME");

    EV <<  "HANDLE HELLO - GELEN RSS: " << gelenRss << endl;

    // esikten buyukse kesin zararli
    if(gelenRss > thresholdRss) {
        EV << "Indexli Düğüm Zararlı" << gonderenIndex << endl;
        EV << "SENDING TIME" << sendingTime << endl;
        EV << "CURRENT TIME" << simTime().dbl() << endl;

        EV << "GONDEREN INDEX " << gonderenIndex << endl;
        EV << "MSG - GONDEREN ID " << gonderenId << endl;
        EV << "BEN - GET ID " << nodeId << endl;

    // sadece rssden buyukse süpheli
    } else if(gelenRss > rss) {
        EV << ":::: SUPHELI :::: " << nodeId << endl;
        cMessage *testMsg = new cMessage("TEST_MSG");
        testMsg->addPar("TEST_MSG_ID");
        testMsg->par("TEST_MSG_ID") = nodeId;
        cModule *node = flatTopologyModule->getSubmodule("nodes", gonderenId);
        sendDirect(testMsg, node, "inputGate");

    // sıkıntı yok devam et
    } else {

        double uzaklik = Util::calculateDistance(nodeKordinatX, nodeKordinatY, gelenX, gelenY);

        EV << "Uzaklık : " << uzaklik << endl;
        EV << "NODE::ID " << nodeId << " -- NODE::INDEX " << nodeIndex << " -- X::Y " << nodeKordinatX << "-" << nodeKordinatY << endl;
        EV << "S::NODE::ID " << gonderenIndex << " -- S::NODE::INDEX " << gonderenIndex << " -- X::Y " << gelenX << "-" << gelenY << endl;

        if(uzaklik < radius && gonderenIndex != nodeIndex){

            komsu.push_back(gonderenIndex);

            for(int i=1; i<komsu.size(); i++){

                EV << "Node INDEX komsu[i] = " <<  komsu[i] << endl;
            }
        }

        if(nodeIndex == kaynak){

            helloMesajiSayisi++;

            if(helloMesajiSayisi == nodeSayisi-1){ // tüm komşulardan alana kadar, kendisi hariç

                EV << "ROTA KEŞFİ BAŞLATILIYOR..." << endl << endl;
                rreqId  = uniform(0,999); // ilk atama burada yapılıyor
                scheduleStart(simTime()+uniform(500,1000));
                RREQ();
            }

        }
    }
}


void Node::RREQ(){

    EV << "RREQ Gönderiliyor..." << endl;

    AODVRREQ *rreq = new AODVRREQ("RREQ");
    rreq->setKaynakAdr(kaynak);
    rreq->setRreqId(rreqId);
    rreq->setHedefAdr(hedef);
    rreq->setHopCount(guncelHopSayisi);
    rreq->setHedefSeqNo(1);
    rreq->addPar("NODE_INDEX");
    rreq->par("NODE_INDEX") = nodeIndex;

    cModule *node;

    for (int i = 0; i < komsu.size(); i++) // sistemdeki t�m d���mlere yollanacak.
    {
       node = flatTopologyModule->getSubmodule("nodes", komsu[i]);

        EV << "Komşu Index : " <<  komsu[i] << endl;

        sendDirect(rreq, node, "inputGate");
        rreq = rreq->dup(); // ayni mesaj iki kere gonderilmez duplicate olur.
    }
}


void Node::handleRREQ(AODVRREQ *rreq){

    //AODVRREQ *rreq = dynamic_cast<AODVRREQ*> (msg);

    if (rreq != nullptr) {

        EV << "Broadcast Mesaj. Gönderen Index : " << rreq->par("NODE_INDEX").doubleValue() << endl;

        guncelHopSayisi = rreq->getHopCount() + 1;

        if(nodeIndex == hedef){


            if(hedefHerKomsudanBirRREPalsin < komsu.size()){

                hedefHerKomsudanBirRREPalsin++;

                EV << "###### HEDEF NodeE GELEN PAKETLER KARŞILAŞTIRILIYOR! ######" << endl;

                if(enKucukHop > guncelHopSayisi || enKucukHop == 0){

                    enKucukHop = guncelHopSayisi;

                    geriRotalama["kaynak"]      = rreq->getKaynakAdr();
                    geriRotalama["hedef"]       = rreq->getHedefAdr();
                    geriRotalama["hedefSeqNo"]  = rreq->getHedefSeqNo();
                    geriRotalama["hopSayisi"]   = enKucukHop;
                    geriRotalama["sonraki"]     = rreq->par("NODE_INDEX").doubleValue();
                    geriRotalama["hedefSeqNo"]  = rreq->getHedefSeqNo();

                }else if(enBuyukHedefSiraNo < rreq->getHedefSeqNo()) {

                    enBuyukHedefSiraNo = rreq->getHedefSeqNo();

                    geriRotalama["kaynak"]      = rreq->getKaynakAdr();
                    geriRotalama["hedef"]       = rreq->getHedefAdr();
                    geriRotalama["hedefSeqNo"]  = rreq->getHedefSeqNo();
                    geriRotalama["hopSayisi"]   = guncelHopSayisi;
                    geriRotalama["sonraki"]     = rreq->par("NODE_INDEX").doubleValue();
                    geriRotalama["hedefSeqNo"]  = enBuyukHedefSiraNo;

                }else{}

                for(int i=0; i<komsu.size(); i++){

                  EV << "Node INDEX komsu[i] = " <<  komsu[i] << endl;
                }

                EV << "HEDEF GERİ ROTALAMA TABLOSU " << endl << "-------------------------" << endl;
                EV << "KAYNAK  INDEX:" << geriRotalama["kaynak"] << endl;
                EV << "HEDEF   INDEX:" << geriRotalama["hedef"] << endl;
                EV << "SONRAKI INDEX:" << geriRotalama["sonraki"] << endl;
                EV << "HOP SAYISI   :" << geriRotalama["hopSayisi"] << endl;

                if(hedefHerKomsudanBirRREPalsin == komsu.size()){ // Node seçimi tamamlandıktan sonra burası çalışacak

                    EV << "###### GERİ ROTALAMA TAMAMLANDI! ######" << endl << "-------------------------" << endl;
                    EV << "İlk RREP Gönderilecek Nodeün Index Bilgisi : " << geriRotalama["sonraki"] << endl;

                    this->RREP(); // hedef ilk RREP mesajını buradan tetikliyor.
                    //endSimulation();
                }

            }else{}


        }else{

           if(rreqId != rreq->getRreqId() && nodeIndex != kaynak){

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


           }else{

               //EV << "Bu broadcast beni ilgilendirmiyor : kaynak Node veya daha önceden alınan bir broadcast" << endl;
               //EV << "RREQ ID Global : " << rreqId << endl << "Paketle gelen RREQ ID : " << rreq->getRreqId() << endl;
           }
        }

    } else {}
}


void Node::RREP(){

    EV << "RREP Gönderiliyor..." << endl;

    AODVRREP *rrep = new AODVRREP("RREP");
    rrep->setKaynakAdr(hedef);
    rrep->setHedefAdr(kaynak);
    rrep->setHopCount(guncelHopSayisi);
    rrep->setHedefSeqNo(2); // Sadece ilk RREP tarafından arttırılabilir.
    rrep->addPar("NODE_INDEX");
    rrep->par("NODE_INDEX") = nodeIndex;

    cModule *node = flatTopologyModule->getSubmodule("nodes", geriRotalama["sonraki"]);
    sendDirect(rrep, node, "inputGate");

}

void Node::handleRREP(AODVRREP *rrep){

    // AODVRREP *rrep = dynamic_cast<AODVRREP*>(msg);

    if(rrep != nullptr){

        if (nodeIndex != kaynak) {

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
            this->sendData();
        }
    }
}

void Node::sendData(){
    cMessage *veri = new cMessage("DATA");
    veri->addPar("NODE_INDEX");
    veri->par("NODE_INDEX") = nodeIndex;
    veri->addPar("NODE_ID");
    veri->par("NODE_ID") = nodeId;

    cModule *node = flatTopologyModule->getSubmodule("nodes", ileriRotalama["sonraki"]);
    sendDirect(veri, node, "inputGate");
}





