#include <config.h>
#include <string>

#include "debug.hpp"
#include "list.hpp"
#include "type.hpp"
#include "compiler.hpp"
using njnr::BasicListNode;
using njnr::ListNode;
using njnr::ReturnPacketListNode;
using njnr::PListNode;
using njnr::TranslationUnitListNode;

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

   const std::string BasicListNode::toString() const
   {
      std::string r{"nodeType: Invalid"};
      switch(nodeType)
      {
        case njnr::eNodeType::EXPR:
           r = "nodeType: njnr::eNodeType::EXPR";
           break;
        case njnr::eNodeType::P:
           r = "nodeType: njnr::eNodeType::P";
           break;
        case njnr::eNodeType::STANDARD:
           r = "nodeType: njnr::eNodeType::STANDARD";
           break;
        case njnr::eNodeType::STMT:
           r = "nodeType: njnr::eNodeType::STMT";
           break;
        case njnr::eNodeType::TRANSLATION_UNIT:
           r = "nodeType: njnr::eNodeType::TRANSLATION_UNIT";
           break;
        case njnr::eNodeType::TYPE:
           r = "nodeType: njnr::eNodeType::TYPE";
           break;
        default:
           // set as default "Invalid"
           break;
      }

      return r;
   }

    const std::string ListNode::toString() const
    {
       return BasicListNode::toString() + "\nval: " + val;
    }

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

   ReturnPacket* ReturnPacketListNode::getexpr(void)
   {
    return expr;
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

   const std::string ReturnPacketListNode::toString() const
   {
      std::string r{BasicListNode::toString() + "\n Expr: "};
      if(NULL != expr)
      {
         r += expr->toString();
      }
      return r;
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

   const std::string PListNode::toString() const
   {
       std::string r{ListNode::toString() + "\n PListNode: type: "};
       r += "njnr::type::";
       r += Compiler::getStringFromType(type);
       return r;
   }

   TranslationUnitListNode::TranslationUnitListNode()
   {
      set_nodeType(njnr::eNodeType::TRANSLATION_UNIT);
   }
   TranslationUnitListNode::TranslationUnitListNode(Funcb* infunc) : unit{infunc},trans_type{njnr::trans_unit_type::FUNCTION}
   {
      set_nodeType(njnr::eNodeType::TRANSLATION_UNIT);
   }
   TranslationUnitListNode::TranslationUnitListNode(Varb* invardecl): unit{invardecl}, trans_type{njnr::trans_unit_type::VARDECL}
   {
      set_nodeType(njnr::eNodeType::TRANSLATION_UNIT);
   } // need to change actual class used this was placeholder

   const njnr::trans_unit_type TranslationUnitListNode::get_trans_unit_type(void) const
   {
      return trans_type;
   }
   const Varb* TranslationUnitListNode::getVarDecl(void) const
   {
      Varb* r{nullptr};
      if(trans_type == njnr::trans_unit_type::VARDECL)
      {
         if(nullptr != unit)
         {
            r = dynamic_cast<Varb*>(unit);
         }
      }
      return r;
   }
   Funcb* TranslationUnitListNode::getFunc(void) const
   {
      Funcb* r{nullptr};
      if(trans_type == njnr::trans_unit_type::FUNCTION)
      {
         if(nullptr != unit)
         {
            r = dynamic_cast<Funcb*>(unit);
         }
      }
      return r;
   }

   const std::string TranslationUnitListNode::toString() const
   {
      std::string r{ListNode::toString() + "\n TranslationUnit: trans type: "};

      switch(trans_type)
      {
        case njnr::trans_unit_type::VARDECL:  // Variable Declaration translation unit
           r += "VARDECL";
           break;

        case njnr::trans_unit_type::FUNCTION:  // Function translation unit
           r += "FUNCTION";
           break;

        case njnr::trans_unit_type::INVALID:  // Invalid translation unit type
        default:
           r += "INVALID";
           break;
      }

      r += " unit: ";
      if(NULL != unit)
      {
         switch(trans_type)
         {
            case njnr::trans_unit_type::VARDECL:  // Variable Declaration translation unit
               r += dynamic_cast<Varb*>(unit)->toString() + "\n";
               break;

            case njnr::trans_unit_type::FUNCTION:  // Function translation unit
               r += dynamic_cast<Funcb*>(unit)->toString();
               break;

           case njnr::trans_unit_type::INVALID:  // Invalid translation unit type
           default:
              r += "INVALID";
              break;
         }
      }

      return r;
   }

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


   const std::string TypeListNode::toString() const
   {
       std::string r{ListNode::toString() + "\n TypeListNode: type: "};
       r += "njnr::type::";
       r += Compiler::getStringFromType(type);
       return r;
   }

      StmtListNode::StmtListNode() : stmt{nullptr}
      {
      set_nodeType(njnr::eNodeType::STMT);
      }
      StmtListNode::StmtListNode(Statement* instmt) : stmt{instmt}
      {
      set_nodeType(njnr::eNodeType::STMT);
      }
      Statement* StmtListNode::getstmt(void){ return stmt; }
      void StmtListNode::setstmt(Statement* instmt) { stmt = instmt; }

   const std::string StmtListNode::toString() const
   {
      std::string r{ListNode::toString() + "\n StmtListNode: stmt: "};

      if(NULL != stmt)
      {
         r += stmt->toString();
      }

      return r;
   }


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

   List* List::mklist(Identifier* i)
   {
      return (new List{})->appendList(i);
   }
   List* List::mklist(Constant* c)
   {
      return (new List{})->appendList(c);
   }
   List* List::appendList(Identifier* inVal)
   {
       ReturnPacketListNode* nnode{new ReturnPacketListNode{inVal}};
       list.push_back(dynamic_cast<BasicListNode*>(nnode));
       return this;
   }
   List* List::appendList(Constant* inVal)
   {
       ReturnPacketListNode* nnode{new ReturnPacketListNode{inVal}};
       list.push_back(dynamic_cast<BasicListNode*>(nnode));
       return this;
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

    const std::string List::toString() const
    {
       std::string r{"List: "};

       for(auto e: list)
       {
        switch(e->get_nodeType())
        {
          case njnr::eNodeType::EXPR:
             r += dynamic_cast<ReturnPacketListNode*>(e)->toString();
             break;
         case njnr::eNodeType::P:
             r += dynamic_cast<PListNode*>(e)->toString();
             break;
          case njnr::eNodeType::STANDARD:
             r += dynamic_cast<ListNode*>(e)->toString();
             break;
          case njnr::eNodeType::STMT:
             r += dynamic_cast<StmtListNode*>(e)->toString();
             break;
          case njnr::eNodeType::TRANSLATION_UNIT:
             r += dynamic_cast<TranslationUnitListNode*>(e)->toString();
             break;
          case njnr::eNodeType::TYPE:
             r += dynamic_cast<TypeListNode*>(e)->toString();
             break;
          default:
             // set as default "Invalid"
             break;
        }
       }
       return r;
    }

}  // namespace njnr
