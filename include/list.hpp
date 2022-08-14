#ifndef _MYLISTH
#define _MYLISTH
#include <vector>
#include <string>

#include "type.hpp"
#include "cpptypes.hpp"
namespace njnr
{
enum class eNodeType
{
    STANDARD,
    EXPR,
    P,
    STMT,
    TRANSLATION_UNIT,  // functions or variable declarations

};

class BasicListNode
{
public:
    BasicListNode(eNodeType t);
    virtual ~BasicListNode();
    eNodeType get_nodeType() const;
    void set_nodeType(eNodeType);
private:
    eNodeType nodeType;
};

class ListNode : public BasicListNode
{
public:
    ListNode();
    ListNode(std::string in);
    virtual ~ListNode() = default;
    std::string getval() const;
    void setval(std::string in);
private:
    std::string val;
};
class ReturnPacketListNode : public BasicListNode
{
public:
    ReturnPacketListNode();
    ReturnPacketListNode(ReturnPacket* expr);
    virtual ~ReturnPacketListNode();
    ReturnPacketListNode(const ReturnPacketListNode& in);
    virtual ReturnPacketListNode& operator=(const ReturnPacketListNode& in);
private:
    ReturnPacket* expr;
};

class PListNode : public ListNode
{
public:
    PListNode();
    PListNode(std::string, njnr::type);
    virtual ~PListNode() = default;
    njnr::type gettype() const;
    void settype(njnr::type type);
private:
    njnr::type type;
};

class TranslationUnitListNode : public ListNode
{
   public:
      TranslationUnitListNode();
      TranslationUnitListNode(Funcb* infunc);
      TranslationUnitListNode(Varb* invardecl); // need to change actual class used this was placeholder
      virtual ~TranslationUnitListNode() = default;
   private:
      ReturnPacket*         unit;
      trans_unit_type trans_type;
};



class List
{
public:
    List();
    ~List();
    List(const List& cp);
    List& operator=(const List& in);
    void push_back(BasicListNode* node);
    std::vector<BasicListNode*> getlist();
    static List* mklist(std::string inVal);
    static List* mklist(std::string inVal, type inType);
    static List* mklist(ReturnPacket* expr);
    static List* mklist(Funcb* expr);
    static List* mklist(Varb* expr);  // place holder type -- needs changing
    std::vector<BasicListNode*>::iterator begin();
    std::vector<BasicListNode*>::iterator end();
    List* appendList(std::string inVal);
    List* appendList(std::string inVal, njnr::type inType);
    List* appendList(ReturnPacket* expr);
    List* appendList(Funcb* expr);
    List* appendList(Varb* expr); // placeholder type -- needs changing
    int size() const;
private:
    std::vector<BasicListNode*> list;
};
}
#endif
