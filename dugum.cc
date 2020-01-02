/*
 * dugum.cc
 *
 *  Created on: Apr 27, 2018
 *      Author: aliarslan
 */

#include "dugum.h"


Define_Module(Dugum);


void Dugum::initialize(){ // sadece başlangıçta çalışıyor

    flatTopolojiModulu = getModuleByPath("flatTopoloji");

    dugumSayisi = flatTopolojiModulu->par("dugumSayisi");
    kaynak = flatTopolojiModulu->par("kaynak");
    hedef  = flatTopolojiModulu->par("hedef");
    kapsama= flatTopolojiModulu->par("kapsama");

    /* istringstream türü bir string(dize) okur, ostringstream bir dize yazar ve stringstream dizeyi okur ve yazar.
     * << operatörünü kullanarak bir std::stringstream nesnesine istenilen verilerin nasıl yazılacağını göstermektedir.
     * >> işleci kullanılarak bir std::stringstream nesnesinden biçimlendirilmiş verilerin nasıl okunacağını gösterir.
     * string ve diğer sayısal türleri arasında kolay dönüşüm yapmak için stringstream kullanılır */


    stringstream topolojiBoyutuX;
    topolojiBoyutuX << flatTopolojiModulu->getDisplayString().getTagArg("bgb",0);
    topolojiBoyutuX >> TOPOLOJI_X; // string değer, integer olan değere atandı.


    stringstream topolojiBoyutuY;
    topolojiBoyutuY << flatTopolojiModulu->getDisplayString().getTagArg("bgb",1);
    topolojiBoyutuY >> TOPOLOJI_Y;


    // her bir düğümün kapsama alanı (topoloji boyutunu geçmeyecek)

//    int maxKapsama = sqrt(double(pow((TOPOLOJI_X), 2) + pow((TOPOLOJI_Y), 2)));

    dugumKoord_X = flatTopolojiModulu->par("posX").doubleValue();
    dugumKoord_Y = flatTopolojiModulu->par("posY").doubleValue();


    EV << "X-TEEESSTT >> " <<  dugumKoord_X << endl;
    EV << "Y-TEEESSTT >> " <<  dugumKoord_Y << endl;

    // refresh layout'tan etkilenmemeleri için sabitledik.
    getDisplayString().setTagArg("p", 0, dugumKoord_X);  // x konumunu ayarla
    getDisplayString().setTagArg("p", 1, dugumKoord_Y);  // y konumunu ayarla

    if(this->getIndex() == kaynak)
        getDisplayString().setTagArg("t", 0, "KAYNAK");
    if(this->getIndex() == hedef)
        getDisplayString().setTagArg("t", 0, "HEDEF");


   // flatToplojiModulu->handleParameterChange("posX");
    // flatToplojiModulu->handleParameterChange("posY");

    cMessage *baslat = new cMessage("baslat");

    baslat->addPar("posX");
    baslat->par("posX") = dugumKoord_X;
    baslat->addPar("posY");
    baslat->par("posY") = dugumKoord_Y;

    scheduleAt(simTime()+uniform(0,5), baslat); //kendine mesaj gönderiyor. kendini uyandırıyor.


}

void Dugum::handleMessage(cMessage *msg){ // burası bir döngü gibi çalışıyor

    if(msg != nullptr){

        if (strcmp(msg->getName(), "baslat") == 0){

           EV << "Hello Mesajı İle Komşular Belirleniyor.." << endl;

           cMessage *hello = new cMessage("hello");
           hello->addPar("hello_X");
           hello->par("hello_X") = msg->par("posX").doubleValue();
           hello->addPar("hello_Y");
           hello->par("hello_Y") = msg->par("posY").doubleValue();
           hello->addPar("hello_index");
           hello->par("hello_index") = this->getIndex();

           cModule *yollanacak_dugum;

           for (int i = 0; i < dugumSayisi; i++) // sistemdeki dugumlere yollanacak.
           {
                yollanacak_dugum = flatTopolojiModulu->getSubmodule("n", i);

                sendDirect(hello, yollanacak_dugum, "girisCikis");

                hello = hello->dup(); // ayn� mesaj iki kere g�nderilemeyece�i i�in dublicate yap�lmas� gerekli.
            }

        }


        /* ########## HELLO MESAJLARI İLE KOMŞU BUL ########## */

        if (strcmp(msg->getName(), "hello") == 0 && this->getIndex() != msg->par("hello_index").doubleValue()){

            //EV << "Benim X : " <<  dugumKoord_X << " - Benim Y : " << dugumKoord_Y << endl;

            int gonderenIndex = msg->par("hello_index");
            int gelenX = msg->par("hello_X");
            int gelenY = msg->par("hello_Y");


          //  EV << "Mesaj Gönderenin X Ekseni :" << gelenX << endl;
          //  EV << "Mesaj Gönderenin Y Ekseni :" << gelenY << endl;

            int uzaklik = kapsamaAlaniHesapla(gelenX,gelenY);

            EV <<  "Uzaklık : " << uzaklik       << endl;
            EV <<  "Gönderen Index: " << gonderenIndex << endl;

            if(uzaklik < kapsama && gonderenIndex != this->getIndex()){

             //   EV << "INDEX :::: " << this->getIndex() << endl;

                komsu.push_back(gonderenIndex);

                for(int i=1; i<komsu.size(); i++){

                    EV << "Düğüm INDEX komsu[i] = " <<  komsu[i] << endl;
                }
            }

            if(this->getIndex() == kaynak){

                helloMesajiSayisi++;

                if(helloMesajiSayisi == dugumSayisi-1){ // tüm komşulardan alana kadar, kendisi hariç


                    EV << "ROTA KEŞFİ BAŞLATILIYOR..." << endl << endl;
                    rreq_id  = uniform(0,999); // ilk atama burada yapılıyor
                    scheduleStart(simTime()+uniform(500,1000));
                    RREQ();

                }

            }
        }


        /* ########## VERİ GÖNDER ########## */

        if(strcmp(msg->getName(), "veri") == 0){

            EV << "VERİ ALINDI" << endl;
            EV << "GONDEREN ID   : "<< msg->par("dugum_id").doubleValue() << endl;
            EV << "GONDEREN INDEX: "<< msg->par("dugum_index").doubleValue() << endl;

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


void Dugum::RREQ(){

    EV << "RREQ Gönderiliyor..." << endl;

    AODVRREQ *rreq = new AODVRREQ("RREQ");
    rreq->setKaynakAdr(kaynak);
    rreq->setRreq_id(rreq_id);
    rreq->setHedefAdr(hedef);
    rreq->setHopCount(guncelHopSayisi);
    rreq->setHedefSeqNo(1);
    rreq->addPar("dugum_index");
    rreq->par("dugum_index") = this->getIndex();

    cModule *yollanacak_dugum;


    for (int i = 0; i < komsu.size(); i++) // sistemdeki t�m d���mlere yollanacak.
    {
       yollanacak_dugum = flatTopolojiModulu->getSubmodule("n", komsu[i]);

        EV << "Komşu Index : " <<  komsu[i] << endl;


        //simtime_t propagationDelay = 0.5;
        //sendDirect(rreq, propagationDelay, SimTime::SimTime(), yollanacak_dugum, "girisCikis");
        sendDirect(rreq, yollanacak_dugum, "girisCikis");

        rreq = rreq->dup(); // ayn� mesaj iki kere g�nderilemeyece�i i�in dublicate yap�lmas� gerekli.
    }
}


void Dugum::handleRREQ(AODVRREQ *rreq){

    //AODVRREQ *rreq = dynamic_cast<AODVRREQ*> (msg);

    if (rreq != nullptr) {

        EV << "Broadcast Mesajı Geldi. Gönderen Index : " << rreq->par("dugum_index").doubleValue() << endl;

        guncelHopSayisi = rreq->getHopCount() + 1;

        if(this->getIndex() == hedef){


            if(hedefHerKomsudanBirRREPalsin < komsu.size()){

                hedefHerKomsudanBirRREPalsin++;

                EV << "###### HEDEF DÜĞÜME GELEN PAKETLER KARŞILAŞTIRILIYOR! ######" << endl;

                if(enKucukHop > guncelHopSayisi || enKucukHop == 0){

                    enKucukHop = guncelHopSayisi;

                    geriRotalama["kaynak"]      = rreq->getKaynakAdr();
                    geriRotalama["hedef"]       = rreq->getHedefAdr();
                    geriRotalama["hedefSeqNo"]  = rreq->getHedefSeqNo();
                    geriRotalama["hopSayisi"]   = enKucukHop;
                    geriRotalama["sonraki"]     = rreq->par("dugum_index").doubleValue();
                    geriRotalama["hedefSeqNo"]  = rreq->getHedefSeqNo();

                }else if(enBuyukHedefSiraNo < rreq->getHedefSeqNo()) {

                    enBuyukHedefSiraNo = rreq->getHedefSeqNo();

                    geriRotalama["kaynak"]      = rreq->getKaynakAdr();
                    geriRotalama["hedef"]       = rreq->getHedefAdr();
                    geriRotalama["hedefSeqNo"]  = rreq->getHedefSeqNo();
                    geriRotalama["hopSayisi"]   = guncelHopSayisi;
                    geriRotalama["sonraki"]     = rreq->par("dugum_index").doubleValue();
                    geriRotalama["hedefSeqNo"]  = enBuyukHedefSiraNo;

                }else{}

                for(int i=0; i<komsu.size(); i++){

                  EV << "Düğüm INDEX komsu[i] = " <<  komsu[i] << endl;
                }

                EV << "HEDEF GERİ ROTALAMA TABLOSU " << endl << "-------------------------" << endl;
                EV << "KAYNAK  INDEX:" << geriRotalama["kaynak"] << endl;
                EV << "HEDEF   INDEX:" << geriRotalama["hedef"] << endl;
                EV << "SONRAKI INDEX:" << geriRotalama["sonraki"] << endl;
                EV << "HOP SAYISI   :" << geriRotalama["hopSayisi"] << endl;

                if(hedefHerKomsudanBirRREPalsin == komsu.size()){ // düğüm seçimi tamamlandıktan sonra burası çalışacak

                    EV << "###### GERİ ROTALAMA TAMAMLANDI! ######" << endl << "-------------------------" << endl;
                    EV << "İlk RREP Gönderilecek Düğümün Index Bilgisi : " << geriRotalama["sonraki"] << endl;

                    this->RREP(); // hedef ilk RREP mesajını buradan tetikliyor.
                    //endSimulation();
                }

            }else{}



        }else{

           if(rreq_id != rreq->getRreq_id() && this->getIndex() != kaynak){

                geriRotalama["kaynak"]      = rreq->getKaynakAdr();
                geriRotalama["hedef"]       = rreq->getHedefAdr();
                geriRotalama["hedefSeqNo"]  = rreq->getHedefSeqNo();
                geriRotalama["hopSayisi"]   = guncelHopSayisi;
                geriRotalama["sonraki"]     = rreq->par("dugum_index");
                geriRotalama["hedefSeqNo"]  = rreq->getHedefSeqNo();

                EV << "ARA DÜĞÜM GERİ ROTALAMA TABLOSU " << endl << "-------------------------" << endl;
                EV << "KAYNAK  INDEX:" << geriRotalama["kaynak"] << endl;
                EV << "HEDEF   INDEX:" << geriRotalama["hedef"] << endl;
                EV << "SONRAKI INDEX:" << geriRotalama["sonraki"] << endl;
                EV << "HOP SAYISI   :" << geriRotalama["hopSayisi"] << endl;

                EV << "Rota tablosunu oluşturdum. Ben de aynı mesajı broadcast ediyorum..." << endl;

                rreq_id = rreq->getRreq_id();
                this->RREQ();


           }else{

               //EV << "Bu broadcast beni ilgilendirmiyor : kaynak düğüm veya daha önceden alınan bir broadcast" << endl;
               //EV << "RREQ ID Global : " << rreq_id << endl << "Paketle gelen RREQ ID : " << rreq->getRreq_id() << endl;
           }
        }

    } else {}
}


void Dugum::RREP(){

    EV << "RREP Gönderiliyor..." << endl;

    AODVRREP *rrep = new AODVRREP("RREP");
    rrep->setKaynakAdr(hedef);
    rrep->setHedefAdr(kaynak);
    rrep->setHopCount(guncelHopSayisi);
    rrep->setHedefSeqNo(2); // Sadece ilk RREP tarafından arttırılabilir.
    rrep->addPar("dugum_index");
    rrep->par("dugum_index") = this->getIndex();

    cModule *yollanacak_dugum = flatTopolojiModulu->getSubmodule("n", geriRotalama["sonraki"]);
    sendDirect(rrep, yollanacak_dugum, "girisCikis");

}

void Dugum::handleRREP(AODVRREP *rrep){

    // AODVRREP *rrep = dynamic_cast<AODVRREP*>(msg);

    if(rrep != nullptr){

        if (this->getIndex() != kaynak) {

            EV << "RREP ALINDI.. " << "İLERİ ROTALAMA TABLOSU" << endl << "-------------------------------------" << endl;
            ileriRotalama["kaynak"]      = rrep->getHedefAdr();
            ileriRotalama["hedef"]       = rrep->getKaynakAdr();
            ileriRotalama["hedefSeqNo"]  = rrep->getHedefSeqNo();
            ileriRotalama["hopSayisi"]   = guncelHopSayisi;
            ileriRotalama["sonraki"]     = rrep->par("dugum_index");

            RREP();

        }else{

            ileriRotalama["kaynak"]      = rrep->getHedefAdr();
            ileriRotalama["hedef"]       = rrep->getKaynakAdr();
            ileriRotalama["hedefSeqNo"]  = rrep->getHedefSeqNo();
            ileriRotalama["hopSayisi"]   = guncelHopSayisi;
            ileriRotalama["sonraki"]     = rrep->par("dugum_index");

            EV << "ROTA KEŞFİ TAMAMLANDI. KAYNAK VERİYİ GÖNDERİLİYOR..." << endl;
            this->veriGonder();

        }
    }
}

void Dugum::veriGonder(){

    cMessage *veri = new cMessage("veri");
    veri->addPar("dugum_index");
    veri->par("dugum_index") = this->getIndex();
    veri->addPar("dugum_id");
    veri->par("dugum_id") = this->getId();

    cModule *yollanacak_dugum = flatTopolojiModulu->getSubmodule("n", ileriRotalama["sonraki"]);
    sendDirect(veri, yollanacak_dugum, "girisCikis");
}


// herbir düğümün koordinatı ile ile mesajı gönderen düğüm arası olan uzaklık birbirlerinin kapsamaları dahilinde mi?
double Dugum::kapsamaAlaniHesapla(int mesaji_gonderen_dugum_X, int mesaji_gonderen_dugum_Y){

    double x = double(pow(abs(mesaji_gonderen_dugum_X - dugumKoord_X), 2));
    double y = double(pow(abs(mesaji_gonderen_dugum_Y - dugumKoord_Y), 2));

    return sqrt(x + y);

}







