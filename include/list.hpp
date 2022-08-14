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
    P
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
    std::vector<BasicListNode*>::iterator begin();
    std::vector<BasicListNode*>::iterator end();
    List* appendList(std::string inVal);
    List* appendList(std::string inVal, njnr::type inType);
    List* appendList(ReturnPacket* expr);
    int size() const;
private:
    std::vector<BasicListNode*> list;
};
}
#endif