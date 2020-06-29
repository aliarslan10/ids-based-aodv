/*
 * dugum.cpp
 *
 *  Created on: Apr 27, 2018
 *  Author: aliarslan
 */

#include "Node.h"

Define_Module(Node);

void Node::initialize(){ // sadece başlangıçta çalışıyor

    flatTopologyModule = getModuleByPath("FlatTopology");

    nodeSayisi = flatTopologyModule->par("nodeSayisi");
    kaynak = flatTopologyModule->par("kaynak");
    hedef  = flatTopologyModule->par("hedef");
    kapsama= flatTopologyModule->par("kapsama");

    stringstream topolojiBoyutuX;
    topolojiBoyutuX << flatTopologyModule->getDisplayString().getTagArg("bgb",0);
    topolojiBoyutuX >> topolojiX; // string değer, integer olan değere atandı.

    stringstream topolojiBoyutuY;
    topolojiBoyutuY << flatTopologyModule->getDisplayString().getTagArg("bgb",1);
    topolojiBoyutuY >> topolojiY;


    // node kapsama alanı topoloji boyutunu geçmeyecek
    // int maxKapsama = sqrt(double(pow((TOPOLOJI_X), 2) + pow((TOPOLOJI_Y), 2)));

    nodeKordinatX = flatTopologyModule->par("posX").doubleValue();
    nodeKordinatY = flatTopologyModule->par("posY").doubleValue();

    EV << "X-TEEESSTT >> " <<  nodeKordinatX << endl;
    EV << "Y-TEEESSTT >> " <<  nodeKordinatY << endl;

    // refresh layout'tan etkilenmemeleri için sabitledik.
    getDisplayString().setTagArg("p", 0, nodeKordinatX);  // x konumunu ayarla
    getDisplayString().setTagArg("p", 1, nodeKordinatY);  // y konumunu ayarla

    if(this->getIndex() == kaynak)
        getDisplayString().setTagArg("t", 0, "KAYNAK");
    if(this->getIndex() == hedef)
        getDisplayString().setTagArg("t", 0, "HEDEF");


   // flatToplojiModulu->handleParameterChange("POSX");
    // flatToplojiModulu->handleParameterChange("POSY");

    cMessage *baslat = new cMessage("BASLAT");

    baslat->addPar("POSX");
    baslat->par("POSX") = nodeKordinatX;
    baslat->addPar("POSY");
    baslat->par("POSY") = nodeKordinatY;

    // self msg. start node
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
           hello->par("HELLO_INDEX") = this->getIndex();

           cModule *yollanacakDugum;

           for (int i = 0; i < nodeSayisi; i++) // sistemdeki dugumlere yollanacak.
           {
                yollanacakDugum = flatTopologyModule->getSubmodule("nodes", i);
                sendDirect(hello, yollanacakDugum, "gate");
                hello = hello->dup();
            }

        }


        /* ########## HELLO MESAJLARI İLE KOMŞU BUL ########## */

        if (strcmp(msg->getName(), "HELLO") == 0 && this->getIndex() != msg->par("HELLO_INDEX").doubleValue()){

            //EV << "Benim X : " <<  nodeKordinatX << " - Benim Y : " << nodeKordinatY << endl;

            int gonderenIndex = msg->par("HELLO_INDEX");
            int gelenX = msg->par("HELLO_X");
            int gelenY = msg->par("HELLO_Y");


          //  EV << "Mesaj Gönderenin X Ekseni :" << gelenX << endl;
          //  EV << "Mesaj Gönderenin Y Ekseni :" << gelenY << endl;

            int uzaklik = kapsamaAlaniHesapla(gelenX,gelenY);

            EV <<  "Uzaklık : " << uzaklik       << endl;
            EV <<  "Gönderen Index: " << gonderenIndex << endl;

            if(uzaklik < kapsama && gonderenIndex != this->getIndex()){

             //   EV << "INDEX :::: " << this->getIndex() << endl;

                komsu.push_back(gonderenIndex);

                for(int i=1; i<komsu.size(); i++){

                    EV << "Node INDEX komsu[i] = " <<  komsu[i] << endl;
                }
            }

            if(this->getIndex() == kaynak){

                helloMesajiSayisi++;

                if(helloMesajiSayisi == nodeSayisi-1){ // tüm komşulardan alana kadar, kendisi hariç

                    EV << "ROTA KEŞFİ BAŞLATILIYOR..." << endl << endl;
                    rreqId  = uniform(0,999); // ilk atama burada yapılıyor
                    scheduleStart(simTime()+uniform(500,1000));
                    RREQ();
                }

            }
        }


        /* ########## VERİ GÖNDER ########## */

        if(strcmp(msg->getName(), "DATA") == 0){

            EV << "VERİ ALINDI" << endl;
            EV << "GONDEREN ID   : "<< msg->par("NODE_ID").doubleValue() << endl;
            EV << "GONDEREN INDEX: "<< msg->par("NODE_INDEX").doubleValue() << endl;

            if(this->getIndex() != hedef)
                this->veriGonder();
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


void Node::RREQ(){

    EV << "RREQ Gönderiliyor..." << endl;

    AODVRREQ *rreq = new AODVRREQ("RREQ");
    rreq->setKaynakAdr(kaynak);
    rreq->setRreqId(rreqId);
    rreq->setHedefAdr(hedef);
    rreq->setHopCount(guncelHopSayisi);
    rreq->setHedefSeqNo(1);
    rreq->addPar("NODE_INDEX");
    rreq->par("NODE_INDEX") = this->getIndex();

    cModule *yollanacakDugum;

    for (int i = 0; i < komsu.size(); i++) // sistemdeki t�m d���mlere yollanacak.
    {
       yollanacakDugum = flatTopologyModule->getSubmodule("nodes", komsu[i]);

        EV << "Komşu Index : " <<  komsu[i] << endl;


        //simtime_t propagationDelay = 0.5;
        //sendDirect(rreq, propagationDelay, SimTime::SimTime(), yollanacakDugum, "girisCikis");
        sendDirect(rreq, yollanacakDugum, "gate");
        rreq = rreq->dup(); // ayn� mesaj iki kere g�nderilemeyece�i i�in dublicate yap�lmas� gerekli.
    }
}


void Node::handleRREQ(AODVRREQ *rreq){

    //AODVRREQ *rreq = dynamic_cast<AODVRREQ*> (msg);

    if (rreq != nullptr) {

        EV << "Broadcast Mesaj. Gönderen Index : " << rreq->par("NODE_INDEX").doubleValue() << endl;

        guncelHopSayisi = rreq->getHopCount() + 1;

        if(this->getIndex() == hedef){


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

           if(rreqId != rreq->getRreqId() && this->getIndex() != kaynak){

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
    rrep->par("NODE_INDEX") = this->getIndex();

    cModule *yollanacakDugum = flatTopologyModule->getSubmodule("nodes", geriRotalama["sonraki"]);
    sendDirect(rrep, yollanacakDugum, "gate");

}

void Node::handleRREP(AODVRREP *rrep){

    // AODVRREP *rrep = dynamic_cast<AODVRREP*>(msg);

    if(rrep != nullptr){

        if (this->getIndex() != kaynak) {

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
            this->veriGonder();
        }
    }
}

void Node::veriGonder(){
    cMessage *veri = new cMessage("DATA");
    veri->addPar("NODE_INDEX");
    veri->par("NODE_INDEX") = this->getIndex();
    veri->addPar("NODE_ID");
    veri->par("NODE_ID") = this->getId();

    cModule *yollanacakDugum = flatTopologyModule->getSubmodule("nodes", ileriRotalama["sonraki"]);
    sendDirect(veri, yollanacakDugum, "gate");
}

double Node::kapsamaAlaniHesapla(int gondericiKordinatX, int gondericiKordinatY){
    double x = double(pow(abs(gondericiKordinatX - gondericiKordinatX), 2));
    double y = double(pow(abs(gondericiKordinatY - gondericiKordinatY), 2));
    return sqrt(x + y);
}







