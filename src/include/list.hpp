#ifndef SRC_INCLUDE_LIST_HPP_
#define SRC_INCLUDE_LIST_HPP_
#include <config.h>
#include <vector>
#include <string>
#include <memory>

#include "type.hpp"
#include "cpptypes.hpp"
#include "constant.hpp"

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
    BasicListNode(): nodeType{njnr::eNodeType::STANDARD} {};
    explicit BasicListNode(eNodeType t);
    virtual ~BasicListNode() = 0;
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
   explicit ListNode(std::string in);
   virtual ~ListNode()
   {
      report(njnr::logType::debug,
             "running ListNode() Destructor");
      report(njnr::logType::debug, this->toString());
   }
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
    explicit ReturnPacketListNode(std::shared_ptr<ReturnPacket> expr);
    virtual ~ReturnPacketListNode();
    ReturnPacketListNode(const ReturnPacketListNode& in);
    virtual ReturnPacketListNode& operator=(const ReturnPacketListNode& in);
    const std::string toString() const;
    std::shared_ptr<ReturnPacket> getexpr(void);
private:
    std::shared_ptr<ReturnPacket> expr;
};

class PListNode : public ListNode
{
public:
   PListNode();
   PListNode(std::string, njnr::type);
   virtual ~PListNode()
   {
      report(njnr::logType::debug,
             "running PListNode() Destructor");
      report(njnr::logType::debug, this->toString());
   }
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
      explicit TranslationUnitListNode(std::shared_ptr<Funcb> infunc);
      // need to change actual class used this was placeholder
      explicit TranslationUnitListNode(std::shared_ptr<Varb> invardecl);
      virtual ~TranslationUnitListNode()
      {
         report(njnr::logType::debug,
                "running TranslationUnitListNode() Destructor");
         report(njnr::logType::debug, this->toString());

//         unit = nullptr;
      }
      const std::string toString() const;
      const njnr::trans_unit_type get_trans_unit_type(void) const;
      const std::shared_ptr<Varb> getVarDecl(void) const;
      std::shared_ptr<Funcb> getFunc(void) const;
   private:
      std::shared_ptr<ReturnPacket>         unit;
      trans_unit_type                 trans_type;
};

class StmtListNode : public ListNode
{
   public:
      StmtListNode();
      explicit StmtListNode(std::shared_ptr<Statement> instmt);
      virtual ~StmtListNode()
      {
         report(njnr::logType::debug,
                "running StmtListNode() Destructor");
         report(njnr::logType::debug, this->toString());

//         stmt = nullptr;
      }
      std::shared_ptr<Statement> getstmt(void);
      void setstmt(std::shared_ptr<Statement> instmt);
      const std::string toString() const;
   private:
      std::shared_ptr<Statement>         stmt;
};



class IdentListNode : public ReturnPacketListNode
{
   public:
      IdentListNode();
      explicit IdentListNode(std::shared_ptr<Identifier> inident);
      virtual ~IdentListNode()
      {
         report(njnr::logType::debug, "running IdentListNode() Destructor");
         report(njnr::logType::debug, this->toString());

//         ident = nullptr;
      }
      std::shared_ptr<Identifier> getident(void);
      void setident(std::shared_ptr<Identifier> instmt);
      const std::string toString() const;
   private:
      std::shared_ptr<Identifier>         ident;
};

class TypeListNode : public ListNode
{
   public:
      TypeListNode();
      // need to change actual class used this was placeholder
      explicit TypeListNode(njnr::type intype);
      virtual ~TypeListNode()
      {
         report(njnr::logType::debug,
                "running TypeListNode() Destructor");
         report(njnr::logType::debug, this->toString());
      }
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
    virtual ~List();
    List(const List& cp);
/*    List& operator=(const List& in);*/
    void push_back(std::shared_ptr<BasicListNode> node);
    std::vector<std::shared_ptr<BasicListNode>> getlist();
    static std::shared_ptr<List> mklist(std::shared_ptr<Identifier>);
    static std::shared_ptr<List> mklist(std::shared_ptr<Constant>);
    static std::shared_ptr<List> mklist(std::string inVal);
    static std::shared_ptr<List> mklist(std::string inVal, type inType);
    static std::shared_ptr<List> mklist(std::shared_ptr<ReturnPacket> expr);
    // static List* mklist(Funcb* expr);
    static std::shared_ptr<List> mklist(std::shared_ptr<Funcb> expr);

    // place holder type -- needs changing
    static std::shared_ptr<List> mklist(std::shared_ptr<Varb> expr);

    static std::shared_ptr<List> mklist(njnr::type type);
    static std::shared_ptr<List> mklist(std::shared_ptr<Statement> instmt);
    std::vector<std::shared_ptr<BasicListNode>>::iterator begin();
    std::vector<std::shared_ptr<BasicListNode>>::iterator end();
    std::shared_ptr<List> appendList(std::string inVal);
    std::shared_ptr<List> appendList(std::string inVal, njnr::type inType);
    std::shared_ptr<List> appendList(std::shared_ptr<ReturnPacket> expr);
    std::shared_ptr<List> appendList(std::shared_ptr<Funcb> expr);

    // placeholder type -- needs changing
    std::shared_ptr<List> appendList(std::shared_ptr<Varb> expr);

    std::shared_ptr<List> appendList(njnr::type type);
    std::shared_ptr<List> appendList(std::shared_ptr<Statement> type);
    std::shared_ptr<List> appendList(std::shared_ptr<Identifier>);
    std::shared_ptr<List> appendList(std::shared_ptr<Constant>);
    int size() const;
    const std::string toString() const;
private:
    std::vector<std::shared_ptr<BasicListNode>> list;
    const std::shared_ptr<List> spthis{this};
};
}  // namespace njnr
#endif  // SRC_INCLUDE_LIST_HPP_
