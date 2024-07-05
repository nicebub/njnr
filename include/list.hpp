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
    TYPE,
    IDENTIFER,
    CHARCONSTANT,
    INTCONSTANT,
    FLOATCONSTANT,
    STRCONSTANT,
};

class BasicListNode
{
public:
    BasicListNode(eNodeType t);
    virtual ~BasicListNode();
    eNodeType get_nodeType() const;
    void set_nodeType(eNodeType);
    const std::string toString() const;

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
    const std::string toString() const;
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
    const std::string toString() const;
    ReturnPacket* getexpr(void);
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
    const std::string toString() const;
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
      const std::string toString() const;
      const njnr::trans_unit_type get_trans_unit_type(void) const;
      const Varb* getVarDecl(void) const;
      Funcb* getFunc(void) const;
   private:
      ReturnPacket*         unit;
      trans_unit_type trans_type;
};

class StmtListNode : public ListNode
{
   public:
      StmtListNode();
      StmtListNode(Statement* instmt);
      virtual ~StmtListNode() = default;
      Statement* getstmt(void);
      void setstmt(Statement* instmt);
      const std::string toString() const;
   private:
      Statement*         stmt;
};



class IdentListNode : public ReturnPacketListNode
{
   public:
      IdentListNode();
      IdentListNode(Identifier* inident);
      virtual ~IdentListNode() = default;
      Identifier* getident(void);
      void setident(Identifier* instmt);
      const std::string toString() const;
   private:
      Identifier*         ident;
};

class TypeListNode : public ListNode
{
   public:
      TypeListNode();
      TypeListNode(njnr::type intype); // need to change actual class used this was placeholder
      virtual ~TypeListNode() = default;
      njnr::type gettype() const;
      void settype(njnr::type type);
      const std::string toString() const;
   private:
      njnr::type         type;
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
    static List* mklist(Identifier*);
    static List* mklist(Constant*);
    static List* mklist(std::string inVal);
    static List* mklist(std::string inVal, type inType);
    static List* mklist(ReturnPacket* expr);
    static List* mklist(Funcb* expr);
    static List* mklist(Varb* expr);  // place holder type -- needs changing
    static List* mklist(njnr::type type);
    static List* mklist(Statement* instmt);
    std::vector<BasicListNode*>::iterator begin();
    std::vector<BasicListNode*>::iterator end();
    List* appendList(std::string inVal);
    List* appendList(std::string inVal, njnr::type inType);
    List* appendList(ReturnPacket* expr);
    List* appendList(Funcb* expr);
    List* appendList(Varb* expr); // placeholder type -- needs changing
    List* appendList(njnr::type type);
    List* appendList(Statement* type);
    List* appendList(Identifier*);
    List* appendList(Constant*);
    int size() const;
    const std::string toString() const;
private:
    std::vector<BasicListNode*> list;
};
}
#endif
