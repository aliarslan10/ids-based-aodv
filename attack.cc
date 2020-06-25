/*
 * attack.cc
 *
 *  Created on: 26 Oca 2020
 *      Author: Ali
 */

#include "attack.h"

/*
attack::attack() { // TODO Auto-generated constructor stub }
attack::~attack() { // TODO Auto-generated destructor stub }
*/

// art arda ve büyük boyutta mesajlar göndererek saldırıya sebep oluyor
int Attack::ddos(vector<int> komsu, cMessage *msg){
    EV << " :::: DDOS SALDIRISI BAŞLADI!" << endl;

    for(int i; i < komsu.size(); i++){
       EV << "Komsu["<<i<< "] : " << komsu[i] << endl;
    }
    int nodeIndex = rand() % komsu.size();
    EV << " Komsu sayısı : " << komsu.size() << endl;
    EV << " Buna saldırıyorum : " << komsu[nodeIndex] << endl;
    return komsu[nodeIndex];
}
