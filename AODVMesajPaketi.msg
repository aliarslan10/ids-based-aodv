// Copyright (C) 2018 Ali Arslan
// Author: Ali Arslan


// packet ile tanımlanan sınıflar	: Kütüphanedeki cPacket sınıfını kullanır
// message ile tanımlanan sınıflar	: Kütüphanedeki cMessage sınıfını kullanır
// enum : kelime anlamı sıralama ekle, sınıfları sırala. İçerdiği değerler benzersiz olmalı. 

enum AODVMesajPaketiTipi{

	RREQ = 1;
	RREP = 2;
	RERR = 3;
	RREP_ACK = 4;

}

//cPaket'in tüm özelliklerini miras alan bir sınıf
packet AODVMesajPaketi {
    
    unsigned int paketTipi;
    unsigned int xEkseni;
    unsigned int yEkseni;
}


class AODVRREQ extends AODVMesajPaketi{

	unsigned int paketTipi = RREQ;
	bool joinFlag;		//multicast için
	bool repairFlag;	//multicast için
	bool gratuitousRREPFlag; //RREP'nin unicast olması gerekip gerekmediği belirtilir
	bool destOnlyFlag;	//mesajı alan düğümün bu RREQ'ya cevap verip vermeyeceğini belirtir
	bool unknownSeqNumFlag; //hedef sıra numarasının bilinmediğini belirtir
	unsigned int hopCount;
	unsigned int rreq_id = 0;
	unsigned int hedefAdr;
	unsigned int hedefSeqNo;
	unsigned int kaynakAdr=2;
	unsigned int kaynakSeqNo;

}



class AODVRREP extends AODVMesajPaketi{

	unsigned int paketTipi = RREP;
	bool repairFlag;
	bool ackRequiredFlag;
	unsigned int prefixSize;
	unsigned int  hopCount;
	unsigned int hedefAdr;
	unsigned int hedefSeqNo;
	unsigned int kaynakAdr;
	unsigned int kaynakSeqNo;
	simtime_t lifeTime;

}


class AODVRERR extends AODVMesajPaketi{

	unsigned int paketTipi = RERR;
	int hataliDugumler[]; // id, ip, adr
	int hataliDugumlerSeqNo[];
	bool noDeleteFlag;
	unsigned int destCount; // ulasilmayan node sayısı, en az 1 olmalı

}


class AODVRREP_ACK extends AODVMesajPaketi{

	unsigned int paketTipi = RREP_ACK;

}


// RREP'nin belli bir süre sonra alınması için tanımlanan süre
message RREP_BeklemeSuresi{

	unsigned int hedefAdr;
	unsigned int sonTTL;
	bool gecersizDugumdenMiAlindi; // doğru yada yanlis

}
