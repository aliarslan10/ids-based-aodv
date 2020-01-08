//
// Generated file, do not edit! Created by nedtool 5.5 from AODVMesajPaketi.msg.
//

#ifndef __AODVMESAJPAKETI_M_H
#define __AODVMESAJPAKETI_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0505
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Enum generated from <tt>AODVMesajPaketi.msg:9</tt> by nedtool.
 * <pre>
 * enum AODVMesajPaketiTipi
 * {
 *     RREQ = 1;
 *     RREP = 2;
 *     RERR = 3;
 *     RREP_ACK = 4;
 * 
 * }
 * </pre>
 */
enum AODVMesajPaketiTipi {
    RREQ = 1,
    RREP = 2,
    RERR = 3,
    RREP_ACK = 4
};

/**
 * Class generated from <tt>AODVMesajPaketi.msg:19</tt> by nedtool.
 * <pre>
 * //cPaket'in tüm özelliklerini miras alan bir sınıf
 * packet AODVMesajPaketi
 * {
 *     unsigned int paketTipi;
 *     unsigned int xEkseni;
 *     unsigned int yEkseni;
 * }
 * </pre>
 */
class AODVMesajPaketi : public ::omnetpp::cPacket
{
  protected:
    unsigned int paketTipi;
    unsigned int xEkseni;
    unsigned int yEkseni;

  private:
    void copy(const AODVMesajPaketi& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const AODVMesajPaketi&);

  public:
    AODVMesajPaketi(const char *name=nullptr, short kind=0);
    AODVMesajPaketi(const AODVMesajPaketi& other);
    virtual ~AODVMesajPaketi();
    AODVMesajPaketi& operator=(const AODVMesajPaketi& other);
    virtual AODVMesajPaketi *dup() const override {return new AODVMesajPaketi(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual unsigned int getPaketTipi() const;
    virtual void setPaketTipi(unsigned int paketTipi);
    virtual unsigned int getXEkseni() const;
    virtual void setXEkseni(unsigned int xEkseni);
    virtual unsigned int getYEkseni() const;
    virtual void setYEkseni(unsigned int yEkseni);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const AODVMesajPaketi& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, AODVMesajPaketi& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>AODVMesajPaketi.msg:27</tt> by nedtool.
 * <pre>
 * class AODVRREQ extends AODVMesajPaketi
 * {
 *     unsigned int paketTipi = RREQ;
 *     bool joinFlag;		//multicast için
 *     bool repairFlag;	//multicast için
 *     bool gratuitousRREPFlag; //RREP'nin unicast olması gerekip gerekmediği belirtilir
 *     bool destOnlyFlag;	//mesajı alan düğümün bu RREQ'ya cevap verip vermeyeceğini belirtir
 *     bool unknownSeqNumFlag; //hedef sıra numarasının bilinmediğini belirtir
 *     unsigned int hopCount;
 *     unsigned int rreq_id = 0;
 *     unsigned int hedefAdr;
 *     unsigned int hedefSeqNo;
 *     unsigned int kaynakAdr = 2;
 *     unsigned int kaynakSeqNo;
 * 
 * }
 * </pre>
 */
class AODVRREQ : public ::AODVMesajPaketi
{
  protected:
    unsigned int paketTipi;
    bool joinFlag;
    bool repairFlag;
    bool gratuitousRREPFlag;
    bool destOnlyFlag;
    bool unknownSeqNumFlag;
    unsigned int hopCount;
    unsigned int rreq_id;
    unsigned int hedefAdr;
    unsigned int hedefSeqNo;
    unsigned int kaynakAdr;
    unsigned int kaynakSeqNo;

  private:
    void copy(const AODVRREQ& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const AODVRREQ&);

  public:
    AODVRREQ(const char *name=nullptr);
    AODVRREQ(const AODVRREQ& other);
    virtual ~AODVRREQ();
    AODVRREQ& operator=(const AODVRREQ& other);
    virtual AODVRREQ *dup() const override {return new AODVRREQ(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual unsigned int getPaketTipi() const;
    virtual void setPaketTipi(unsigned int paketTipi);
    virtual bool getJoinFlag() const;
    virtual void setJoinFlag(bool joinFlag);
    virtual bool getRepairFlag() const;
    virtual void setRepairFlag(bool repairFlag);
    virtual bool getGratuitousRREPFlag() const;
    virtual void setGratuitousRREPFlag(bool gratuitousRREPFlag);
    virtual bool getDestOnlyFlag() const;
    virtual void setDestOnlyFlag(bool destOnlyFlag);
    virtual bool getUnknownSeqNumFlag() const;
    virtual void setUnknownSeqNumFlag(bool unknownSeqNumFlag);
    virtual unsigned int getHopCount() const;
    virtual void setHopCount(unsigned int hopCount);
    virtual unsigned int getRreq_id() const;
    virtual void setRreq_id(unsigned int rreq_id);
    virtual unsigned int getHedefAdr() const;
    virtual void setHedefAdr(unsigned int hedefAdr);
    virtual unsigned int getHedefSeqNo() const;
    virtual void setHedefSeqNo(unsigned int hedefSeqNo);
    virtual unsigned int getKaynakAdr() const;
    virtual void setKaynakAdr(unsigned int kaynakAdr);
    virtual unsigned int getKaynakSeqNo() const;
    virtual void setKaynakSeqNo(unsigned int kaynakSeqNo);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const AODVRREQ& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, AODVRREQ& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>AODVMesajPaketi.msg:46</tt> by nedtool.
 * <pre>
 * class AODVRREP extends AODVMesajPaketi
 * {
 *     unsigned int paketTipi = RREP;
 *     bool repairFlag;
 *     bool ackRequiredFlag;
 *     unsigned int prefixSize;
 *     unsigned int hopCount;
 *     unsigned int hedefAdr;
 *     unsigned int hedefSeqNo;
 *     unsigned int kaynakAdr;
 *     unsigned int kaynakSeqNo;
 *     simtime_t lifeTime;
 * 
 * }
 * </pre>
 */
class AODVRREP : public ::AODVMesajPaketi
{
  protected:
    unsigned int paketTipi;
    bool repairFlag;
    bool ackRequiredFlag;
    unsigned int prefixSize;
    unsigned int hopCount;
    unsigned int hedefAdr;
    unsigned int hedefSeqNo;
    unsigned int kaynakAdr;
    unsigned int kaynakSeqNo;
    ::omnetpp::simtime_t lifeTime;

  private:
    void copy(const AODVRREP& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const AODVRREP&);

  public:
    AODVRREP(const char *name=nullptr);
    AODVRREP(const AODVRREP& other);
    virtual ~AODVRREP();
    AODVRREP& operator=(const AODVRREP& other);
    virtual AODVRREP *dup() const override {return new AODVRREP(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual unsigned int getPaketTipi() const;
    virtual void setPaketTipi(unsigned int paketTipi);
    virtual bool getRepairFlag() const;
    virtual void setRepairFlag(bool repairFlag);
    virtual bool getAckRequiredFlag() const;
    virtual void setAckRequiredFlag(bool ackRequiredFlag);
    virtual unsigned int getPrefixSize() const;
    virtual void setPrefixSize(unsigned int prefixSize);
    virtual unsigned int getHopCount() const;
    virtual void setHopCount(unsigned int hopCount);
    virtual unsigned int getHedefAdr() const;
    virtual void setHedefAdr(unsigned int hedefAdr);
    virtual unsigned int getHedefSeqNo() const;
    virtual void setHedefSeqNo(unsigned int hedefSeqNo);
    virtual unsigned int getKaynakAdr() const;
    virtual void setKaynakAdr(unsigned int kaynakAdr);
    virtual unsigned int getKaynakSeqNo() const;
    virtual void setKaynakSeqNo(unsigned int kaynakSeqNo);
    virtual ::omnetpp::simtime_t getLifeTime() const;
    virtual void setLifeTime(::omnetpp::simtime_t lifeTime);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const AODVRREP& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, AODVRREP& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>AODVMesajPaketi.msg:62</tt> by nedtool.
 * <pre>
 * class AODVRERR extends AODVMesajPaketi
 * {
 *     unsigned int paketTipi = RERR;
 *     int hataliDugumler[]; // id, ip, adr
 *     int hataliDugumlerSeqNo[];
 *     bool noDeleteFlag;
 *     unsigned int destCount; // ulasilmayan node sayısı, en az 1 olmalı
 * 
 * }
 * </pre>
 */
class AODVRERR : public ::AODVMesajPaketi
{
  protected:
    unsigned int paketTipi;
    int *hataliDugumler; // array ptr
    unsigned int hataliDugumler_arraysize;
    int *hataliDugumlerSeqNo; // array ptr
    unsigned int hataliDugumlerSeqNo_arraysize;
    bool noDeleteFlag;
    unsigned int destCount;

  private:
    void copy(const AODVRERR& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const AODVRERR&);

  public:
    AODVRERR(const char *name=nullptr);
    AODVRERR(const AODVRERR& other);
    virtual ~AODVRERR();
    AODVRERR& operator=(const AODVRERR& other);
    virtual AODVRERR *dup() const override {return new AODVRERR(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual unsigned int getPaketTipi() const;
    virtual void setPaketTipi(unsigned int paketTipi);
    virtual void setHataliDugumlerArraySize(unsigned int size);
    virtual unsigned int getHataliDugumlerArraySize() const;
    virtual int getHataliDugumler(unsigned int k) const;
    virtual void setHataliDugumler(unsigned int k, int hataliDugumler);
    virtual void setHataliDugumlerSeqNoArraySize(unsigned int size);
    virtual unsigned int getHataliDugumlerSeqNoArraySize() const;
    virtual int getHataliDugumlerSeqNo(unsigned int k) const;
    virtual void setHataliDugumlerSeqNo(unsigned int k, int hataliDugumlerSeqNo);
    virtual bool getNoDeleteFlag() const;
    virtual void setNoDeleteFlag(bool noDeleteFlag);
    virtual unsigned int getDestCount() const;
    virtual void setDestCount(unsigned int destCount);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const AODVRERR& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, AODVRERR& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>AODVMesajPaketi.msg:73</tt> by nedtool.
 * <pre>
 * class AODVRREP_ACK extends AODVMesajPaketi
 * {
 *     unsigned int paketTipi = RREP_ACK;
 * 
 * }
 * </pre>
 */
class AODVRREP_ACK : public ::AODVMesajPaketi
{
  protected:
    unsigned int paketTipi;

  private:
    void copy(const AODVRREP_ACK& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const AODVRREP_ACK&);

  public:
    AODVRREP_ACK(const char *name=nullptr);
    AODVRREP_ACK(const AODVRREP_ACK& other);
    virtual ~AODVRREP_ACK();
    AODVRREP_ACK& operator=(const AODVRREP_ACK& other);
    virtual AODVRREP_ACK *dup() const override {return new AODVRREP_ACK(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual unsigned int getPaketTipi() const;
    virtual void setPaketTipi(unsigned int paketTipi);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const AODVRREP_ACK& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, AODVRREP_ACK& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>AODVMesajPaketi.msg:81</tt> by nedtool.
 * <pre>
 * // RREP'nin belli bir süre sonra alınması için tanımlanan süre
 * message RREP_BeklemeSuresi
 * {
 *     unsigned int hedefAdr;
 *     unsigned int sonTTL;
 *     bool gecersizDugumdenMiAlindi; // doğru yada yanlis
 * 
 * }
 * </pre>
 */
class RREP_BeklemeSuresi : public ::omnetpp::cMessage
{
  protected:
    unsigned int hedefAdr;
    unsigned int sonTTL;
    bool gecersizDugumdenMiAlindi;

  private:
    void copy(const RREP_BeklemeSuresi& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RREP_BeklemeSuresi&);

  public:
    RREP_BeklemeSuresi(const char *name=nullptr, short kind=0);
    RREP_BeklemeSuresi(const RREP_BeklemeSuresi& other);
    virtual ~RREP_BeklemeSuresi();
    RREP_BeklemeSuresi& operator=(const RREP_BeklemeSuresi& other);
    virtual RREP_BeklemeSuresi *dup() const override {return new RREP_BeklemeSuresi(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual unsigned int getHedefAdr() const;
    virtual void setHedefAdr(unsigned int hedefAdr);
    virtual unsigned int getSonTTL() const;
    virtual void setSonTTL(unsigned int sonTTL);
    virtual bool getGecersizDugumdenMiAlindi() const;
    virtual void setGecersizDugumdenMiAlindi(bool gecersizDugumdenMiAlindi);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RREP_BeklemeSuresi& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RREP_BeklemeSuresi& obj) {obj.parsimUnpack(b);}


#endif // ifndef __AODVMESAJPAKETI_M_H

