//
// Generated file, do not edit! Created by nedtool 5.6 from src/AODVMsgPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "AODVMsgPacket_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("AODVMesajPaketiTipi");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("AODVMesajPaketiTipi"));
    e->insert(RREQ, "RREQ");
    e->insert(RREP, "RREP");
    e->insert(RERR, "RERR");
    e->insert(RREP_ACK, "RREP_ACK");
)

Register_Class(AODVMesajPaketi)

AODVMesajPaketi::AODVMesajPaketi(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->xEkseni = 0;
    this->yEkseni = 0;
}

AODVMesajPaketi::AODVMesajPaketi(const AODVMesajPaketi& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

AODVMesajPaketi::~AODVMesajPaketi()
{
}

AODVMesajPaketi& AODVMesajPaketi::operator=(const AODVMesajPaketi& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void AODVMesajPaketi::copy(const AODVMesajPaketi& other)
{
    this->xEkseni = other.xEkseni;
    this->yEkseni = other.yEkseni;
}

void AODVMesajPaketi::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->xEkseni);
    doParsimPacking(b,this->yEkseni);
}

void AODVMesajPaketi::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->xEkseni);
    doParsimUnpacking(b,this->yEkseni);
}

unsigned int AODVMesajPaketi::getXEkseni() const
{
    return this->xEkseni;
}

void AODVMesajPaketi::setXEkseni(unsigned int xEkseni)
{
    this->xEkseni = xEkseni;
}

unsigned int AODVMesajPaketi::getYEkseni() const
{
    return this->yEkseni;
}

void AODVMesajPaketi::setYEkseni(unsigned int yEkseni)
{
    this->yEkseni = yEkseni;
}

class AODVMesajPaketiDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    AODVMesajPaketiDescriptor();
    virtual ~AODVMesajPaketiDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(AODVMesajPaketiDescriptor)

AODVMesajPaketiDescriptor::AODVMesajPaketiDescriptor() : omnetpp::cClassDescriptor("AODVMesajPaketi", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

AODVMesajPaketiDescriptor::~AODVMesajPaketiDescriptor()
{
    delete[] propertynames;
}

bool AODVMesajPaketiDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AODVMesajPaketi *>(obj)!=nullptr;
}

const char **AODVMesajPaketiDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *AODVMesajPaketiDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int AODVMesajPaketiDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int AODVMesajPaketiDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *AODVMesajPaketiDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "xEkseni",
        "yEkseni",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int AODVMesajPaketiDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='x' && strcmp(fieldName, "xEkseni")==0) return base+0;
    if (fieldName[0]=='y' && strcmp(fieldName, "yEkseni")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *AODVMesajPaketiDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "unsigned int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **AODVMesajPaketiDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *AODVMesajPaketiDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int AODVMesajPaketiDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    AODVMesajPaketi *pp = (AODVMesajPaketi *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *AODVMesajPaketiDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    AODVMesajPaketi *pp = (AODVMesajPaketi *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AODVMesajPaketiDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    AODVMesajPaketi *pp = (AODVMesajPaketi *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getXEkseni());
        case 1: return ulong2string(pp->getYEkseni());
        default: return "";
    }
}

bool AODVMesajPaketiDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    AODVMesajPaketi *pp = (AODVMesajPaketi *)object; (void)pp;
    switch (field) {
        case 0: pp->setXEkseni(string2ulong(value)); return true;
        case 1: pp->setYEkseni(string2ulong(value)); return true;
        default: return false;
    }
}

const char *AODVMesajPaketiDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *AODVMesajPaketiDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    AODVMesajPaketi *pp = (AODVMesajPaketi *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(AODVRREQ)

AODVRREQ::AODVRREQ(const char *name) : ::AODVMesajPaketi(name)
{
    this->joinFlag = false;
    this->repairFlag = false;
    this->gratuitousRREPFlag = false;
    this->destOnlyFlag = false;
    this->unknownSeqNumFlag = false;
    this->hopCount = 0;
    this->rreqId = 0;
    this->hedefAdr = 0;
    this->hedefSeqNo = 0;
    this->kaynakAdr = 2;
    this->kaynakSeqNo = 0;
}

AODVRREQ::AODVRREQ(const AODVRREQ& other) : ::AODVMesajPaketi(other)
{
    copy(other);
}

AODVRREQ::~AODVRREQ()
{
}

AODVRREQ& AODVRREQ::operator=(const AODVRREQ& other)
{
    if (this==&other) return *this;
    ::AODVMesajPaketi::operator=(other);
    copy(other);
    return *this;
}

void AODVRREQ::copy(const AODVRREQ& other)
{
    this->joinFlag = other.joinFlag;
    this->repairFlag = other.repairFlag;
    this->gratuitousRREPFlag = other.gratuitousRREPFlag;
    this->destOnlyFlag = other.destOnlyFlag;
    this->unknownSeqNumFlag = other.unknownSeqNumFlag;
    this->hopCount = other.hopCount;
    this->rreqId = other.rreqId;
    this->hedefAdr = other.hedefAdr;
    this->hedefSeqNo = other.hedefSeqNo;
    this->kaynakAdr = other.kaynakAdr;
    this->kaynakSeqNo = other.kaynakSeqNo;
}

void AODVRREQ::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::AODVMesajPaketi::parsimPack(b);
    doParsimPacking(b,this->joinFlag);
    doParsimPacking(b,this->repairFlag);
    doParsimPacking(b,this->gratuitousRREPFlag);
    doParsimPacking(b,this->destOnlyFlag);
    doParsimPacking(b,this->unknownSeqNumFlag);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->rreqId);
    doParsimPacking(b,this->hedefAdr);
    doParsimPacking(b,this->hedefSeqNo);
    doParsimPacking(b,this->kaynakAdr);
    doParsimPacking(b,this->kaynakSeqNo);
}

void AODVRREQ::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::AODVMesajPaketi::parsimUnpack(b);
    doParsimUnpacking(b,this->joinFlag);
    doParsimUnpacking(b,this->repairFlag);
    doParsimUnpacking(b,this->gratuitousRREPFlag);
    doParsimUnpacking(b,this->destOnlyFlag);
    doParsimUnpacking(b,this->unknownSeqNumFlag);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->rreqId);
    doParsimUnpacking(b,this->hedefAdr);
    doParsimUnpacking(b,this->hedefSeqNo);
    doParsimUnpacking(b,this->kaynakAdr);
    doParsimUnpacking(b,this->kaynakSeqNo);
}

bool AODVRREQ::getJoinFlag() const
{
    return this->joinFlag;
}

void AODVRREQ::setJoinFlag(bool joinFlag)
{
    this->joinFlag = joinFlag;
}

bool AODVRREQ::getRepairFlag() const
{
    return this->repairFlag;
}

void AODVRREQ::setRepairFlag(bool repairFlag)
{
    this->repairFlag = repairFlag;
}

bool AODVRREQ::getGratuitousRREPFlag() const
{
    return this->gratuitousRREPFlag;
}

void AODVRREQ::setGratuitousRREPFlag(bool gratuitousRREPFlag)
{
    this->gratuitousRREPFlag = gratuitousRREPFlag;
}

bool AODVRREQ::getDestOnlyFlag() const
{
    return this->destOnlyFlag;
}

void AODVRREQ::setDestOnlyFlag(bool destOnlyFlag)
{
    this->destOnlyFlag = destOnlyFlag;
}

bool AODVRREQ::getUnknownSeqNumFlag() const
{
    return this->unknownSeqNumFlag;
}

void AODVRREQ::setUnknownSeqNumFlag(bool unknownSeqNumFlag)
{
    this->unknownSeqNumFlag = unknownSeqNumFlag;
}

unsigned int AODVRREQ::getHopCount() const
{
    return this->hopCount;
}

void AODVRREQ::setHopCount(unsigned int hopCount)
{
    this->hopCount = hopCount;
}

unsigned int AODVRREQ::getRreqId() const
{
    return this->rreqId;
}

void AODVRREQ::setRreqId(unsigned int rreqId)
{
    this->rreqId = rreqId;
}

unsigned int AODVRREQ::getHedefAdr() const
{
    return this->hedefAdr;
}

void AODVRREQ::setHedefAdr(unsigned int hedefAdr)
{
    this->hedefAdr = hedefAdr;
}

unsigned int AODVRREQ::getHedefSeqNo() const
{
    return this->hedefSeqNo;
}

void AODVRREQ::setHedefSeqNo(unsigned int hedefSeqNo)
{
    this->hedefSeqNo = hedefSeqNo;
}

unsigned int AODVRREQ::getKaynakAdr() const
{
    return this->kaynakAdr;
}

void AODVRREQ::setKaynakAdr(unsigned int kaynakAdr)
{
    this->kaynakAdr = kaynakAdr;
}

unsigned int AODVRREQ::getKaynakSeqNo() const
{
    return this->kaynakSeqNo;
}

void AODVRREQ::setKaynakSeqNo(unsigned int kaynakSeqNo)
{
    this->kaynakSeqNo = kaynakSeqNo;
}

class AODVRREQDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    AODVRREQDescriptor();
    virtual ~AODVRREQDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(AODVRREQDescriptor)

AODVRREQDescriptor::AODVRREQDescriptor() : omnetpp::cClassDescriptor("AODVRREQ", "AODVMesajPaketi")
{
    propertynames = nullptr;
}

AODVRREQDescriptor::~AODVRREQDescriptor()
{
    delete[] propertynames;
}

bool AODVRREQDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AODVRREQ *>(obj)!=nullptr;
}

const char **AODVRREQDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *AODVRREQDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int AODVRREQDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 11+basedesc->getFieldCount() : 11;
}

unsigned int AODVRREQDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<11) ? fieldTypeFlags[field] : 0;
}

const char *AODVRREQDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "joinFlag",
        "repairFlag",
        "gratuitousRREPFlag",
        "destOnlyFlag",
        "unknownSeqNumFlag",
        "hopCount",
        "rreqId",
        "hedefAdr",
        "hedefSeqNo",
        "kaynakAdr",
        "kaynakSeqNo",
    };
    return (field>=0 && field<11) ? fieldNames[field] : nullptr;
}

int AODVRREQDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='j' && strcmp(fieldName, "joinFlag")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "repairFlag")==0) return base+1;
    if (fieldName[0]=='g' && strcmp(fieldName, "gratuitousRREPFlag")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "destOnlyFlag")==0) return base+3;
    if (fieldName[0]=='u' && strcmp(fieldName, "unknownSeqNumFlag")==0) return base+4;
    if (fieldName[0]=='h' && strcmp(fieldName, "hopCount")==0) return base+5;
    if (fieldName[0]=='r' && strcmp(fieldName, "rreqId")==0) return base+6;
    if (fieldName[0]=='h' && strcmp(fieldName, "hedefAdr")==0) return base+7;
    if (fieldName[0]=='h' && strcmp(fieldName, "hedefSeqNo")==0) return base+8;
    if (fieldName[0]=='k' && strcmp(fieldName, "kaynakAdr")==0) return base+9;
    if (fieldName[0]=='k' && strcmp(fieldName, "kaynakSeqNo")==0) return base+10;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *AODVRREQDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",
        "bool",
        "bool",
        "bool",
        "bool",
        "unsigned int",
        "unsigned int",
        "unsigned int",
        "unsigned int",
        "unsigned int",
        "unsigned int",
    };
    return (field>=0 && field<11) ? fieldTypeStrings[field] : nullptr;
}

const char **AODVRREQDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *AODVRREQDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int AODVRREQDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    AODVRREQ *pp = (AODVRREQ *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *AODVRREQDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    AODVRREQ *pp = (AODVRREQ *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AODVRREQDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    AODVRREQ *pp = (AODVRREQ *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getJoinFlag());
        case 1: return bool2string(pp->getRepairFlag());
        case 2: return bool2string(pp->getGratuitousRREPFlag());
        case 3: return bool2string(pp->getDestOnlyFlag());
        case 4: return bool2string(pp->getUnknownSeqNumFlag());
        case 5: return ulong2string(pp->getHopCount());
        case 6: return ulong2string(pp->getRreqId());
        case 7: return ulong2string(pp->getHedefAdr());
        case 8: return ulong2string(pp->getHedefSeqNo());
        case 9: return ulong2string(pp->getKaynakAdr());
        case 10: return ulong2string(pp->getKaynakSeqNo());
        default: return "";
    }
}

bool AODVRREQDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    AODVRREQ *pp = (AODVRREQ *)object; (void)pp;
    switch (field) {
        case 0: pp->setJoinFlag(string2bool(value)); return true;
        case 1: pp->setRepairFlag(string2bool(value)); return true;
        case 2: pp->setGratuitousRREPFlag(string2bool(value)); return true;
        case 3: pp->setDestOnlyFlag(string2bool(value)); return true;
        case 4: pp->setUnknownSeqNumFlag(string2bool(value)); return true;
        case 5: pp->setHopCount(string2ulong(value)); return true;
        case 6: pp->setRreqId(string2ulong(value)); return true;
        case 7: pp->setHedefAdr(string2ulong(value)); return true;
        case 8: pp->setHedefSeqNo(string2ulong(value)); return true;
        case 9: pp->setKaynakAdr(string2ulong(value)); return true;
        case 10: pp->setKaynakSeqNo(string2ulong(value)); return true;
        default: return false;
    }
}

const char *AODVRREQDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *AODVRREQDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    AODVRREQ *pp = (AODVRREQ *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(AODVRREP)

AODVRREP::AODVRREP(const char *name) : ::AODVMesajPaketi(name)
{
    this->repairFlag = false;
    this->ackRequiredFlag = false;
    this->prefixSize = 0;
    this->hopCount = 0;
    this->hedefAdr = 0;
    this->hedefSeqNo = 0;
    this->kaynakAdr = 0;
    this->kaynakSeqNo = 0;
    this->lifeTime = 0;
}

AODVRREP::AODVRREP(const AODVRREP& other) : ::AODVMesajPaketi(other)
{
    copy(other);
}

AODVRREP::~AODVRREP()
{
}

AODVRREP& AODVRREP::operator=(const AODVRREP& other)
{
    if (this==&other) return *this;
    ::AODVMesajPaketi::operator=(other);
    copy(other);
    return *this;
}

void AODVRREP::copy(const AODVRREP& other)
{
    this->repairFlag = other.repairFlag;
    this->ackRequiredFlag = other.ackRequiredFlag;
    this->prefixSize = other.prefixSize;
    this->hopCount = other.hopCount;
    this->hedefAdr = other.hedefAdr;
    this->hedefSeqNo = other.hedefSeqNo;
    this->kaynakAdr = other.kaynakAdr;
    this->kaynakSeqNo = other.kaynakSeqNo;
    this->lifeTime = other.lifeTime;
}

void AODVRREP::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::AODVMesajPaketi::parsimPack(b);
    doParsimPacking(b,this->repairFlag);
    doParsimPacking(b,this->ackRequiredFlag);
    doParsimPacking(b,this->prefixSize);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->hedefAdr);
    doParsimPacking(b,this->hedefSeqNo);
    doParsimPacking(b,this->kaynakAdr);
    doParsimPacking(b,this->kaynakSeqNo);
    doParsimPacking(b,this->lifeTime);
}

void AODVRREP::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::AODVMesajPaketi::parsimUnpack(b);
    doParsimUnpacking(b,this->repairFlag);
    doParsimUnpacking(b,this->ackRequiredFlag);
    doParsimUnpacking(b,this->prefixSize);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->hedefAdr);
    doParsimUnpacking(b,this->hedefSeqNo);
    doParsimUnpacking(b,this->kaynakAdr);
    doParsimUnpacking(b,this->kaynakSeqNo);
    doParsimUnpacking(b,this->lifeTime);
}

bool AODVRREP::getRepairFlag() const
{
    return this->repairFlag;
}

void AODVRREP::setRepairFlag(bool repairFlag)
{
    this->repairFlag = repairFlag;
}

bool AODVRREP::getAckRequiredFlag() const
{
    return this->ackRequiredFlag;
}

void AODVRREP::setAckRequiredFlag(bool ackRequiredFlag)
{
    this->ackRequiredFlag = ackRequiredFlag;
}

unsigned int AODVRREP::getPrefixSize() const
{
    return this->prefixSize;
}

void AODVRREP::setPrefixSize(unsigned int prefixSize)
{
    this->prefixSize = prefixSize;
}

unsigned int AODVRREP::getHopCount() const
{
    return this->hopCount;
}

void AODVRREP::setHopCount(unsigned int hopCount)
{
    this->hopCount = hopCount;
}

unsigned int AODVRREP::getHedefAdr() const
{
    return this->hedefAdr;
}

void AODVRREP::setHedefAdr(unsigned int hedefAdr)
{
    this->hedefAdr = hedefAdr;
}

unsigned int AODVRREP::getHedefSeqNo() const
{
    return this->hedefSeqNo;
}

void AODVRREP::setHedefSeqNo(unsigned int hedefSeqNo)
{
    this->hedefSeqNo = hedefSeqNo;
}

unsigned int AODVRREP::getKaynakAdr() const
{
    return this->kaynakAdr;
}

void AODVRREP::setKaynakAdr(unsigned int kaynakAdr)
{
    this->kaynakAdr = kaynakAdr;
}

unsigned int AODVRREP::getKaynakSeqNo() const
{
    return this->kaynakSeqNo;
}

void AODVRREP::setKaynakSeqNo(unsigned int kaynakSeqNo)
{
    this->kaynakSeqNo = kaynakSeqNo;
}

::omnetpp::simtime_t AODVRREP::getLifeTime() const
{
    return this->lifeTime;
}

void AODVRREP::setLifeTime(::omnetpp::simtime_t lifeTime)
{
    this->lifeTime = lifeTime;
}

class AODVRREPDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    AODVRREPDescriptor();
    virtual ~AODVRREPDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(AODVRREPDescriptor)

AODVRREPDescriptor::AODVRREPDescriptor() : omnetpp::cClassDescriptor("AODVRREP", "AODVMesajPaketi")
{
    propertynames = nullptr;
}

AODVRREPDescriptor::~AODVRREPDescriptor()
{
    delete[] propertynames;
}

bool AODVRREPDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AODVRREP *>(obj)!=nullptr;
}

const char **AODVRREPDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *AODVRREPDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int AODVRREPDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 9+basedesc->getFieldCount() : 9;
}

unsigned int AODVRREPDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<9) ? fieldTypeFlags[field] : 0;
}

const char *AODVRREPDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "repairFlag",
        "ackRequiredFlag",
        "prefixSize",
        "hopCount",
        "hedefAdr",
        "hedefSeqNo",
        "kaynakAdr",
        "kaynakSeqNo",
        "lifeTime",
    };
    return (field>=0 && field<9) ? fieldNames[field] : nullptr;
}

int AODVRREPDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "repairFlag")==0) return base+0;
    if (fieldName[0]=='a' && strcmp(fieldName, "ackRequiredFlag")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "prefixSize")==0) return base+2;
    if (fieldName[0]=='h' && strcmp(fieldName, "hopCount")==0) return base+3;
    if (fieldName[0]=='h' && strcmp(fieldName, "hedefAdr")==0) return base+4;
    if (fieldName[0]=='h' && strcmp(fieldName, "hedefSeqNo")==0) return base+5;
    if (fieldName[0]=='k' && strcmp(fieldName, "kaynakAdr")==0) return base+6;
    if (fieldName[0]=='k' && strcmp(fieldName, "kaynakSeqNo")==0) return base+7;
    if (fieldName[0]=='l' && strcmp(fieldName, "lifeTime")==0) return base+8;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *AODVRREPDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",
        "bool",
        "unsigned int",
        "unsigned int",
        "unsigned int",
        "unsigned int",
        "unsigned int",
        "unsigned int",
        "simtime_t",
    };
    return (field>=0 && field<9) ? fieldTypeStrings[field] : nullptr;
}

const char **AODVRREPDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *AODVRREPDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int AODVRREPDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    AODVRREP *pp = (AODVRREP *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *AODVRREPDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    AODVRREP *pp = (AODVRREP *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AODVRREPDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    AODVRREP *pp = (AODVRREP *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getRepairFlag());
        case 1: return bool2string(pp->getAckRequiredFlag());
        case 2: return ulong2string(pp->getPrefixSize());
        case 3: return ulong2string(pp->getHopCount());
        case 4: return ulong2string(pp->getHedefAdr());
        case 5: return ulong2string(pp->getHedefSeqNo());
        case 6: return ulong2string(pp->getKaynakAdr());
        case 7: return ulong2string(pp->getKaynakSeqNo());
        case 8: return simtime2string(pp->getLifeTime());
        default: return "";
    }
}

bool AODVRREPDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    AODVRREP *pp = (AODVRREP *)object; (void)pp;
    switch (field) {
        case 0: pp->setRepairFlag(string2bool(value)); return true;
        case 1: pp->setAckRequiredFlag(string2bool(value)); return true;
        case 2: pp->setPrefixSize(string2ulong(value)); return true;
        case 3: pp->setHopCount(string2ulong(value)); return true;
        case 4: pp->setHedefAdr(string2ulong(value)); return true;
        case 5: pp->setHedefSeqNo(string2ulong(value)); return true;
        case 6: pp->setKaynakAdr(string2ulong(value)); return true;
        case 7: pp->setKaynakSeqNo(string2ulong(value)); return true;
        case 8: pp->setLifeTime(string2simtime(value)); return true;
        default: return false;
    }
}

const char *AODVRREPDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *AODVRREPDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    AODVRREP *pp = (AODVRREP *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(AODVRERR)

AODVRERR::AODVRERR(const char *name) : ::AODVMesajPaketi(name)
{
    hataliDugumler_arraysize = 0;
    this->hataliDugumler = 0;
    hataliDugumlerSeqNo_arraysize = 0;
    this->hataliDugumlerSeqNo = 0;
    this->noDeleteFlag = false;
    this->destCount = 0;
}

AODVRERR::AODVRERR(const AODVRERR& other) : ::AODVMesajPaketi(other)
{
    hataliDugumler_arraysize = 0;
    this->hataliDugumler = 0;
    hataliDugumlerSeqNo_arraysize = 0;
    this->hataliDugumlerSeqNo = 0;
    copy(other);
}

AODVRERR::~AODVRERR()
{
    delete [] this->hataliDugumler;
    delete [] this->hataliDugumlerSeqNo;
}

AODVRERR& AODVRERR::operator=(const AODVRERR& other)
{
    if (this==&other) return *this;
    ::AODVMesajPaketi::operator=(other);
    copy(other);
    return *this;
}

void AODVRERR::copy(const AODVRERR& other)
{
    delete [] this->hataliDugumler;
    this->hataliDugumler = (other.hataliDugumler_arraysize==0) ? nullptr : new int[other.hataliDugumler_arraysize];
    hataliDugumler_arraysize = other.hataliDugumler_arraysize;
    for (unsigned int i=0; i<hataliDugumler_arraysize; i++)
        this->hataliDugumler[i] = other.hataliDugumler[i];
    delete [] this->hataliDugumlerSeqNo;
    this->hataliDugumlerSeqNo = (other.hataliDugumlerSeqNo_arraysize==0) ? nullptr : new int[other.hataliDugumlerSeqNo_arraysize];
    hataliDugumlerSeqNo_arraysize = other.hataliDugumlerSeqNo_arraysize;
    for (unsigned int i=0; i<hataliDugumlerSeqNo_arraysize; i++)
        this->hataliDugumlerSeqNo[i] = other.hataliDugumlerSeqNo[i];
    this->noDeleteFlag = other.noDeleteFlag;
    this->destCount = other.destCount;
}

void AODVRERR::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::AODVMesajPaketi::parsimPack(b);
    b->pack(hataliDugumler_arraysize);
    doParsimArrayPacking(b,this->hataliDugumler,hataliDugumler_arraysize);
    b->pack(hataliDugumlerSeqNo_arraysize);
    doParsimArrayPacking(b,this->hataliDugumlerSeqNo,hataliDugumlerSeqNo_arraysize);
    doParsimPacking(b,this->noDeleteFlag);
    doParsimPacking(b,this->destCount);
}

void AODVRERR::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::AODVMesajPaketi::parsimUnpack(b);
    delete [] this->hataliDugumler;
    b->unpack(hataliDugumler_arraysize);
    if (hataliDugumler_arraysize==0) {
        this->hataliDugumler = 0;
    } else {
        this->hataliDugumler = new int[hataliDugumler_arraysize];
        doParsimArrayUnpacking(b,this->hataliDugumler,hataliDugumler_arraysize);
    }
    delete [] this->hataliDugumlerSeqNo;
    b->unpack(hataliDugumlerSeqNo_arraysize);
    if (hataliDugumlerSeqNo_arraysize==0) {
        this->hataliDugumlerSeqNo = 0;
    } else {
        this->hataliDugumlerSeqNo = new int[hataliDugumlerSeqNo_arraysize];
        doParsimArrayUnpacking(b,this->hataliDugumlerSeqNo,hataliDugumlerSeqNo_arraysize);
    }
    doParsimUnpacking(b,this->noDeleteFlag);
    doParsimUnpacking(b,this->destCount);
}

void AODVRERR::setHataliDugumlerArraySize(unsigned int size)
{
    int *hataliDugumler2 = (size==0) ? nullptr : new int[size];
    unsigned int sz = hataliDugumler_arraysize < size ? hataliDugumler_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        hataliDugumler2[i] = this->hataliDugumler[i];
    for (unsigned int i=sz; i<size; i++)
        hataliDugumler2[i] = 0;
    hataliDugumler_arraysize = size;
    delete [] this->hataliDugumler;
    this->hataliDugumler = hataliDugumler2;
}

unsigned int AODVRERR::getHataliDugumlerArraySize() const
{
    return hataliDugumler_arraysize;
}

int AODVRERR::getHataliDugumler(unsigned int k) const
{
    if (k>=hataliDugumler_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", hataliDugumler_arraysize, k);
    return this->hataliDugumler[k];
}

void AODVRERR::setHataliDugumler(unsigned int k, int hataliDugumler)
{
    if (k>=hataliDugumler_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", hataliDugumler_arraysize, k);
    this->hataliDugumler[k] = hataliDugumler;
}

void AODVRERR::setHataliDugumlerSeqNoArraySize(unsigned int size)
{
    int *hataliDugumlerSeqNo2 = (size==0) ? nullptr : new int[size];
    unsigned int sz = hataliDugumlerSeqNo_arraysize < size ? hataliDugumlerSeqNo_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        hataliDugumlerSeqNo2[i] = this->hataliDugumlerSeqNo[i];
    for (unsigned int i=sz; i<size; i++)
        hataliDugumlerSeqNo2[i] = 0;
    hataliDugumlerSeqNo_arraysize = size;
    delete [] this->hataliDugumlerSeqNo;
    this->hataliDugumlerSeqNo = hataliDugumlerSeqNo2;
}

unsigned int AODVRERR::getHataliDugumlerSeqNoArraySize() const
{
    return hataliDugumlerSeqNo_arraysize;
}

int AODVRERR::getHataliDugumlerSeqNo(unsigned int k) const
{
    if (k>=hataliDugumlerSeqNo_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", hataliDugumlerSeqNo_arraysize, k);
    return this->hataliDugumlerSeqNo[k];
}

void AODVRERR::setHataliDugumlerSeqNo(unsigned int k, int hataliDugumlerSeqNo)
{
    if (k>=hataliDugumlerSeqNo_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", hataliDugumlerSeqNo_arraysize, k);
    this->hataliDugumlerSeqNo[k] = hataliDugumlerSeqNo;
}

bool AODVRERR::getNoDeleteFlag() const
{
    return this->noDeleteFlag;
}

void AODVRERR::setNoDeleteFlag(bool noDeleteFlag)
{
    this->noDeleteFlag = noDeleteFlag;
}

unsigned int AODVRERR::getDestCount() const
{
    return this->destCount;
}

void AODVRERR::setDestCount(unsigned int destCount)
{
    this->destCount = destCount;
}

class AODVRERRDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    AODVRERRDescriptor();
    virtual ~AODVRERRDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(AODVRERRDescriptor)

AODVRERRDescriptor::AODVRERRDescriptor() : omnetpp::cClassDescriptor("AODVRERR", "AODVMesajPaketi")
{
    propertynames = nullptr;
}

AODVRERRDescriptor::~AODVRERRDescriptor()
{
    delete[] propertynames;
}

bool AODVRERRDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AODVRERR *>(obj)!=nullptr;
}

const char **AODVRERRDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *AODVRERRDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int AODVRERRDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int AODVRERRDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *AODVRERRDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "hataliDugumler",
        "hataliDugumlerSeqNo",
        "noDeleteFlag",
        "destCount",
    };
    return (field>=0 && field<4) ? fieldNames[field] : nullptr;
}

int AODVRERRDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='h' && strcmp(fieldName, "hataliDugumler")==0) return base+0;
    if (fieldName[0]=='h' && strcmp(fieldName, "hataliDugumlerSeqNo")==0) return base+1;
    if (fieldName[0]=='n' && strcmp(fieldName, "noDeleteFlag")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "destCount")==0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *AODVRERRDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "bool",
        "unsigned int",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : nullptr;
}

const char **AODVRERRDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *AODVRERRDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int AODVRERRDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    AODVRERR *pp = (AODVRERR *)object; (void)pp;
    switch (field) {
        case 0: return pp->getHataliDugumlerArraySize();
        case 1: return pp->getHataliDugumlerSeqNoArraySize();
        default: return 0;
    }
}

const char *AODVRERRDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    AODVRERR *pp = (AODVRERR *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AODVRERRDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    AODVRERR *pp = (AODVRERR *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getHataliDugumler(i));
        case 1: return long2string(pp->getHataliDugumlerSeqNo(i));
        case 2: return bool2string(pp->getNoDeleteFlag());
        case 3: return ulong2string(pp->getDestCount());
        default: return "";
    }
}

bool AODVRERRDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    AODVRERR *pp = (AODVRERR *)object; (void)pp;
    switch (field) {
        case 0: pp->setHataliDugumler(i,string2long(value)); return true;
        case 1: pp->setHataliDugumlerSeqNo(i,string2long(value)); return true;
        case 2: pp->setNoDeleteFlag(string2bool(value)); return true;
        case 3: pp->setDestCount(string2ulong(value)); return true;
        default: return false;
    }
}

const char *AODVRERRDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *AODVRERRDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    AODVRERR *pp = (AODVRERR *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(AODVRREP_ACK)

AODVRREP_ACK::AODVRREP_ACK(const char *name) : ::AODVMesajPaketi(name)
{
}

AODVRREP_ACK::AODVRREP_ACK(const AODVRREP_ACK& other) : ::AODVMesajPaketi(other)
{
    copy(other);
}

AODVRREP_ACK::~AODVRREP_ACK()
{
}

AODVRREP_ACK& AODVRREP_ACK::operator=(const AODVRREP_ACK& other)
{
    if (this==&other) return *this;
    ::AODVMesajPaketi::operator=(other);
    copy(other);
    return *this;
}

void AODVRREP_ACK::copy(const AODVRREP_ACK& other)
{
}

void AODVRREP_ACK::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::AODVMesajPaketi::parsimPack(b);
}

void AODVRREP_ACK::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::AODVMesajPaketi::parsimUnpack(b);
}

class AODVRREP_ACKDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    AODVRREP_ACKDescriptor();
    virtual ~AODVRREP_ACKDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(AODVRREP_ACKDescriptor)

AODVRREP_ACKDescriptor::AODVRREP_ACKDescriptor() : omnetpp::cClassDescriptor("AODVRREP_ACK", "AODVMesajPaketi")
{
    propertynames = nullptr;
}

AODVRREP_ACKDescriptor::~AODVRREP_ACKDescriptor()
{
    delete[] propertynames;
}

bool AODVRREP_ACKDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AODVRREP_ACK *>(obj)!=nullptr;
}

const char **AODVRREP_ACKDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *AODVRREP_ACKDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int AODVRREP_ACKDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int AODVRREP_ACKDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *AODVRREP_ACKDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int AODVRREP_ACKDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *AODVRREP_ACKDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **AODVRREP_ACKDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *AODVRREP_ACKDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int AODVRREP_ACKDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    AODVRREP_ACK *pp = (AODVRREP_ACK *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *AODVRREP_ACKDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    AODVRREP_ACK *pp = (AODVRREP_ACK *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AODVRREP_ACKDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    AODVRREP_ACK *pp = (AODVRREP_ACK *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool AODVRREP_ACKDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    AODVRREP_ACK *pp = (AODVRREP_ACK *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *AODVRREP_ACKDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *AODVRREP_ACKDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    AODVRREP_ACK *pp = (AODVRREP_ACK *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(RREP_BeklemeSuresi)

RREP_BeklemeSuresi::RREP_BeklemeSuresi(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
    this->hedefAdr = 0;
    this->sonTTL = 0;
    this->gecersizDugumdenMiAlindi = false;
}

RREP_BeklemeSuresi::RREP_BeklemeSuresi(const RREP_BeklemeSuresi& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

RREP_BeklemeSuresi::~RREP_BeklemeSuresi()
{
}

RREP_BeklemeSuresi& RREP_BeklemeSuresi::operator=(const RREP_BeklemeSuresi& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void RREP_BeklemeSuresi::copy(const RREP_BeklemeSuresi& other)
{
    this->hedefAdr = other.hedefAdr;
    this->sonTTL = other.sonTTL;
    this->gecersizDugumdenMiAlindi = other.gecersizDugumdenMiAlindi;
}

void RREP_BeklemeSuresi::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->hedefAdr);
    doParsimPacking(b,this->sonTTL);
    doParsimPacking(b,this->gecersizDugumdenMiAlindi);
}

void RREP_BeklemeSuresi::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->hedefAdr);
    doParsimUnpacking(b,this->sonTTL);
    doParsimUnpacking(b,this->gecersizDugumdenMiAlindi);
}

unsigned int RREP_BeklemeSuresi::getHedefAdr() const
{
    return this->hedefAdr;
}

void RREP_BeklemeSuresi::setHedefAdr(unsigned int hedefAdr)
{
    this->hedefAdr = hedefAdr;
}

unsigned int RREP_BeklemeSuresi::getSonTTL() const
{
    return this->sonTTL;
}

void RREP_BeklemeSuresi::setSonTTL(unsigned int sonTTL)
{
    this->sonTTL = sonTTL;
}

bool RREP_BeklemeSuresi::getGecersizDugumdenMiAlindi() const
{
    return this->gecersizDugumdenMiAlindi;
}

void RREP_BeklemeSuresi::setGecersizDugumdenMiAlindi(bool gecersizDugumdenMiAlindi)
{
    this->gecersizDugumdenMiAlindi = gecersizDugumdenMiAlindi;
}

class RREP_BeklemeSuresiDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    RREP_BeklemeSuresiDescriptor();
    virtual ~RREP_BeklemeSuresiDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(RREP_BeklemeSuresiDescriptor)

RREP_BeklemeSuresiDescriptor::RREP_BeklemeSuresiDescriptor() : omnetpp::cClassDescriptor("RREP_BeklemeSuresi", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

RREP_BeklemeSuresiDescriptor::~RREP_BeklemeSuresiDescriptor()
{
    delete[] propertynames;
}

bool RREP_BeklemeSuresiDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RREP_BeklemeSuresi *>(obj)!=nullptr;
}

const char **RREP_BeklemeSuresiDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *RREP_BeklemeSuresiDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int RREP_BeklemeSuresiDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int RREP_BeklemeSuresiDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *RREP_BeklemeSuresiDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "hedefAdr",
        "sonTTL",
        "gecersizDugumdenMiAlindi",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int RREP_BeklemeSuresiDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='h' && strcmp(fieldName, "hedefAdr")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sonTTL")==0) return base+1;
    if (fieldName[0]=='g' && strcmp(fieldName, "gecersizDugumdenMiAlindi")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *RREP_BeklemeSuresiDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "unsigned int",
        "bool",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **RREP_BeklemeSuresiDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *RREP_BeklemeSuresiDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int RREP_BeklemeSuresiDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    RREP_BeklemeSuresi *pp = (RREP_BeklemeSuresi *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *RREP_BeklemeSuresiDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    RREP_BeklemeSuresi *pp = (RREP_BeklemeSuresi *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RREP_BeklemeSuresiDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    RREP_BeklemeSuresi *pp = (RREP_BeklemeSuresi *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getHedefAdr());
        case 1: return ulong2string(pp->getSonTTL());
        case 2: return bool2string(pp->getGecersizDugumdenMiAlindi());
        default: return "";
    }
}

bool RREP_BeklemeSuresiDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    RREP_BeklemeSuresi *pp = (RREP_BeklemeSuresi *)object; (void)pp;
    switch (field) {
        case 0: pp->setHedefAdr(string2ulong(value)); return true;
        case 1: pp->setSonTTL(string2ulong(value)); return true;
        case 2: pp->setGecersizDugumdenMiAlindi(string2bool(value)); return true;
        default: return false;
    }
}

const char *RREP_BeklemeSuresiDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *RREP_BeklemeSuresiDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    RREP_BeklemeSuresi *pp = (RREP_BeklemeSuresi *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


