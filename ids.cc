/*
 * ids.cpp
 *
 *  Created on: 25 Oca 2020
 *      Author: Ali
 */

#include "ids.h"

bool IDS::paketBoyutunuKontrolEt(int m_paketBoyutu, int paketBoyutu){
    if(m_paketBoyutu < paketBoyutu){
        EV << "IDS: DOS SALDIRI ŞÜPHESİ :: " << m_paketBoyutu << " < " << paketBoyutu << endl;
        return true;
    }
    return false;
}
