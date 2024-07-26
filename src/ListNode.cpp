#include <config.h>
#include <memory>
#include <string>

#include "debug.hpp"
#include "ListNode.hpp"
#include "type.hpp"
#include "compiler.hpp"
using njnr::BasicListNode;
using njnr::ListNode;
using njnr::ReturnPacketListNode;
using njnr::PListNode;
using njnr::TranslationUnitListNode;


   BasicListNode::BasicListNode(eNodeType t) : nodeType{t} {}

   eNodeType BasicListNode::get_nodeType() const
   {
       return nodeType;
   }
   void BasicListNode::set_nodeType(eNodeType in)
   {
       nodeType = in;
   }

   BasicListNode::~BasicListNode()
   {
      report(njnr::logType::debug,
             "running BasicListNode() Destructor");
      report(njnr::logType::debug, this->toString());
   }

   const std::string BasicListNode::toString() const
   {
      std::string r{"nodeType: Invalid"};
      switch (nodeType)
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

   ListNode::ListNode() : BasicListNode{}, val{""} {}

   ListNode::ListNode(std::string in) : BasicListNode{eNodeType::STANDARD},
                                        val{in}
                                        {}

   std::string ListNode::getval() const
   {
       return val;
   }
   void ListNode::setval(std::string in)
   {
       val = in;
   }

   ReturnPacketListNode::ReturnPacketListNode() : BasicListNode{},
                                                  expr{nullptr}
                                                  {}

   ReturnPacketListNode::ReturnPacketListNode(std::shared_ptr<ReturnPacket> expr) :
                                    BasicListNode{eNodeType::EXPR},
                                    expr{expr}
                                    {}

   ReturnPacketListNode::~ReturnPacketListNode()
   {
      report(njnr::logType::debug,
             "running ReturnPacketListNode() Destructor");
      report(njnr::logType::debug, this->toString());

     //  delete expr;
        expr = nullptr;
   }

   std::shared_ptr<ReturnPacket> ReturnPacketListNode::getexpr(void)
   {
    return expr;
   }

   ReturnPacketListNode::ReturnPacketListNode(const ReturnPacketListNode& in) :
                                              BasicListNode{in.get_nodeType()}
   {
       expr = in.expr;
   }
   ReturnPacketListNode& ReturnPacketListNode::operator=(\
                                                 const ReturnPacketListNode& in)
   {
       if (this != &in)
       {
           expr = in.expr;
       }
       return *this;
   }

   const std::string ReturnPacketListNode::toString() const
   {
      std::string r{BasicListNode::toString() + "\n Expr: "};
      if (NULL != expr)
      {
         r += expr->toString();
      }
      return r;
   }

   PListNode::PListNode() : ListNode{""}, type{njnr::type::VOID}
   {
       set_nodeType(eNodeType::P);
       setval("");
   }
   PListNode::PListNode(std::string inVal, njnr::type inType) : ListNode{inVal}, type{inType}
   {
       set_nodeType(eNodeType::P);
       setval(inVal);
   }

   njnr::type PListNode::gettype() const
   {
       return this->type;
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
   TranslationUnitListNode::TranslationUnitListNode(std::shared_ptr<Funcb> infunc) :
                             unit{infunc},
                             trans_type{njnr::trans_unit_type::FUNCTION}
   {
      set_nodeType(njnr::eNodeType::TRANSLATION_UNIT);
   }
   TranslationUnitListNode::TranslationUnitListNode(std::shared_ptr<Varb> invardecl):
                             unit{invardecl},
                             trans_type{njnr::trans_unit_type::VARDECL}
   {
      set_nodeType(njnr::eNodeType::TRANSLATION_UNIT);
   }  // need to change actual class used this was placeholder

   const njnr::trans_unit_type TranslationUnitListNode::get_trans_unit_type(\
                                                           void) const
   {
      return trans_type;
   }
   const std::shared_ptr<Varb> TranslationUnitListNode::getVarDecl(void) const
   {
      std::shared_ptr<Varb> r{nullptr};
      if (trans_type == njnr::trans_unit_type::VARDECL)
      {
         if (nullptr != unit)
         {
            r = std::dynamic_pointer_cast<Varb>(unit);
         }
      }
      return r;
   }
   std::shared_ptr<Funcb> TranslationUnitListNode::getFunc(void) const
   {
      std::shared_ptr<Funcb> r{nullptr};
      if (trans_type == njnr::trans_unit_type::FUNCTION)
      {
         if (nullptr != unit)
         {
            r = std::dynamic_pointer_cast<Funcb>(unit);
         }
      }
      return r;
   }

   const std::string TranslationUnitListNode::toString() const
   {
      std::string r{ListNode::toString() + "\n TranslationUnit: trans type: "};

      switch (trans_type)
      {
        // Variable Declaration translation unit
        case njnr::trans_unit_type::VARDECL:
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
      if (NULL != unit)
      {
         switch (trans_type)
         {
            // Variable Declaration translation unit
            case njnr::trans_unit_type::VARDECL:
            case njnr::trans_unit_type::FUNCTION:  // Function translation unit
               r += unit->toString() + "\n";
               break;
           // Invalid translation unit type
           case njnr::trans_unit_type::INVALID:
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
      StmtListNode::StmtListNode(std::shared_ptr<Statement> instmt) : stmt{instmt}
      {
      set_nodeType(njnr::eNodeType::STMT);
      }
      std::shared_ptr<Statement> StmtListNode::getstmt(void)
      {
         return stmt;
      }
      void StmtListNode::setstmt(std::shared_ptr<Statement> instmt) { stmt = instmt; }

   const std::string StmtListNode::toString() const
   {
      std::string r{ListNode::toString() + "\n StmtListNode: stmt: "};

      if (NULL != stmt)
      {
         r += stmt->toString();
      }

      return r;
   }
