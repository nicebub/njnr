#include <string>

#include "debug.hpp"
#include "list.hpp"
#include "type.hpp"

using namespace njnr;

namespace njnr
{
   BasicListNode::BasicListNode(eNodeType t) : nodeType{t} {}

   eNodeType BasicListNode::get_nodeType() const
   {
       return nodeType;
   }
   void BasicListNode::set_nodeType(eNodeType in)
   {
       nodeType = in;
   }

   BasicListNode::~BasicListNode() {}

   ListNode::ListNode() : ListNode("") {}

   ListNode::ListNode(std::string in) : BasicListNode{eNodeType::STANDARD}, val{in} {}

   std::string ListNode::getval() const
   {
       return val;
   }
   void ListNode::setval(std::string in)
   {
       val = in;
   }

   ReturnPacketListNode::ReturnPacketListNode() : ReturnPacketListNode{NULL} {}

   ReturnPacketListNode::ReturnPacketListNode(ReturnPacket* expr) : BasicListNode{eNodeType::EXPR}, expr{expr} {}

   ReturnPacketListNode::~ReturnPacketListNode()
   {
       if(expr)
       {
           delete expr;
       }
   }
   ReturnPacketListNode::ReturnPacketListNode(const ReturnPacketListNode& in) : BasicListNode{in.get_nodeType()}
   {
       expr = in.expr;
   }
   ReturnPacketListNode& ReturnPacketListNode::operator=(const ReturnPacketListNode& in)
   {
       if(this != &in)
       {
           expr = in.expr;
       }
       return *this;
   }
   PListNode::PListNode() : ListNode{}, type{}
   {
       set_nodeType(eNodeType::P);
       setval("");
   }
   PListNode::PListNode(std::string inVal, njnr::type inType) : type{inType}
   {
       set_nodeType(eNodeType::P);
       setval(inVal);
   }

   njnr::type PListNode::gettype() const
   {
       return type;
   }
   void PListNode::settype(njnr::type type)
   {
       this->type = type;
   }

   TranslationUnitListNode::TranslationUnitListNode() {}
   TranslationUnitListNode::TranslationUnitListNode(Funcb* infunc) {}
   TranslationUnitListNode::TranslationUnitListNode(Varb* invardecl) {} // need to change actual class used this was placeholder

   TypeListNode::TypeListNode() : ListNode{}, type{}
   {
       set_nodeType(eNodeType::TYPE);
       setval("");
   }

   TypeListNode::TypeListNode(njnr::type type) : ListNode{}, type{type}
   {
       set_nodeType(eNodeType::TYPE);
       setval("");
   }

   njnr::type TypeListNode::gettype() const
   {
       return type;
   }
   void TypeListNode::settype(njnr::type type)
   {
       this->type = type;
   }

      StmtListNode::StmtListNode() : stmt{nullptr} {}
      StmtListNode::StmtListNode(Statement* instmt) : stmt{instmt} {}
      Statement* StmtListNode::getstmt(void){ return stmt; }
      void StmtListNode::setstmt(Statement* instmt) { stmt = instmt; }


   List::List() : list{} {}
   List::List(const List& cp) : list{cp.list} {}
   List::~List()
   {
       for(auto* element : list)
       {
           delete element;
       }
   }

   std::vector<BasicListNode*>::iterator List::begin()
   {
       return list.begin();
   }
   std::vector<BasicListNode*>::iterator List::end()
   {
       return list.end();
   }

   int List::size() const
   {
       return static_cast<int>(list.size());
   }

   List& List::operator=(const List& in)
   {
       return *this;
   }

   void List::push_back(BasicListNode* in)
   {
       list.push_back(in);
   }

   List* List::mklist(njnr::type inType)
   {
       return (new List{})->appendList(inType);
   }

   List* List::mklist(std::string inVal)
   {
       return (new List{})->appendList(inVal);
   }
   List* List::mklist(std::string inVal, type inType)
   {
       return (new List{})->appendList(inVal,inType);
   }
   List* List::mklist(ReturnPacket* inExpr)
   {
       return (new List{})->appendList(inExpr);
   }

   List* List::mklist(Statement* instmt)
   {
       return (new List{})->appendList(instmt);
   }

   List* List::appendList(std::string inVal)
   {
       ListNode* nnode{new ListNode{inVal}};
       list.push_back(dynamic_cast<BasicListNode*>(nnode));
       return this;
   }

   List* List::appendList(std::string inVal, type inType)
   {
       PListNode* nnode{new PListNode{inVal,inType}};
       list.push_back(dynamic_cast<BasicListNode*>(nnode));
       return this;
   }

   List* List::appendList(ReturnPacket* inexpr)
   {
       ReturnPacketListNode* nnode{new ReturnPacketListNode{inexpr}};
       list.push_back(dynamic_cast<BasicListNode*>(nnode));
       return this;
   }

   List* List::appendList(njnr::type intype)
   {
       TypeListNode* nnode{new TypeListNode{intype}};
       list.push_back(dynamic_cast<BasicListNode*>(nnode));
       return this;
   }

   List* List::appendList(Statement* instmt)
   {
       StmtListNode* nnode{new StmtListNode{instmt}};
       list.push_back(dynamic_cast<BasicListNode*>(nnode));
       return this;
   }

   std::vector<BasicListNode*> List::getlist()
   {
       return list;
   }

   List* List::mklist(Funcb* expr)
   {
       return (new List{})->appendList(expr);
   }

   List* List::mklist(Varb* expr)
   {
       return (new List{})->appendList(expr);
   } // place holder type -- needs changing

   List* List::appendList(Funcb* expr)
   {
       ListNode* nnode{new TranslationUnitListNode{expr}};
       list.push_back(dynamic_cast<BasicListNode*>(nnode));
       return this;
   }

   List* List::appendList(Varb* expr)
   {
       ListNode* nnode{new TranslationUnitListNode{expr}};
       list.push_back(dynamic_cast<BasicListNode*>(nnode));
       return this;
   } // placeholder type -- needs changing
}
