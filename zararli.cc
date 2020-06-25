/*
 * zararli.cc
 *
 *  Created on: 2 Şub 2020
 *      Author: Ali
 */

#include "zararli.h"

Define_Module(Zararli);

void Zararli::initialize(){

}

void Zararli::handleMessage(cMessage *msg) {
    if(strcmp(msg->getName(), "RREQ") == 0){

        EV << "VERİYİ ALINDI ZARARLI ALID" << endl;
        EV << "VERİ ZARARLI BAŞARIYLA ALINDI." << endl;


    }
}
