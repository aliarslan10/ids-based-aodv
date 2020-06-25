/*
 * dugum.h
 *
 *  Created on: May 9, 2018
 *      Author: aliarslan
 */

#ifndef DUGUM_H_
#define DUGUM_H_

#include <string.h>
#include <omnetpp.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>
#include <stdio.h>
#include <map>
#include <vector>

#include "AODVMesajPaketi_m.h"

using namespace omnetpp;
using namespace std;

cModule *flatTopolojiModulu;
IDS *ids;
Attack *attack;
cModule *yollanacakDugum;

class Dugum : public cSimpleModule{

    private:
        int kaynak;
        int hedef;
        int dugumSayisi;
        int paketBoyutu;
        int kapsama;
        int TOPOLOJI_X;
        int TOPOLOJI_Y;
        int dugumKoord_X;
        int dugumKoord_Y;
        int helloMesajiSayisi = 0;
        int guncelHopSayisi=0, enKucukHop=0, enBuyukHedefSiraNo=0;
        bool zararli = false;

        // zararli değişkenler
        int saldiriModu;
        int zararliPaketBoyutu;
        int ddosGonderimSayisi;
        int saldiriSayisi = 0;

        // ids degiskenleri
        int savunmaModu;
        int alarmSayisi;

        vector<int> komsu;
        map<string, int> geriRotalama;
        map<string, int> ileriRotalama;

        int rreq_id = 0;
        int hedefHerKomsudanBirRREPalsin = 0; // en küçük hop seçimi için

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual void handleRREQ(AODVRREQ *rreq);
        virtual void handleRREP(AODVRREP *rrep);
        void RREQ();
        void RREP();
        void veriGonder();
        double kapsamaAlaniHesapla(int mesaji_gonderen_dugum_X, int mesaji_gonderen_dugum_Y);
};

#endif /* DUGUM_H_ */
