#include <config.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "debug.hpp"
#include "Compiler.hpp"
#include "njnr.tab.hpp"
#include "List.hpp"
#include "ListNode.hpp"
#include "ReturnPacket.hpp"
#include "Statement.hpp"

using namespace njnr;

   const std::string Statement::toString() const
   {
    /**
         statement_type stype;
         std::shared_ptr<ReturnPacket> stmt;
         type         rettype;
     */
      std::string r = ReturnPacket::toString();
   //      statement_type stype;
//         std::shared_ptr<ReturnPacket> stmt;
//         type         rettype;
         r += "stmt type: ";
         if (nullptr != expr)
         {
            switch (stype)
            {
               case njnr::statement_type::DOUNTIL:
                  r += "DOUNTIL";
                  break;
               case njnr::statement_type::DOWHILE:
                  r += "DOWHILE";
                  break;
               case njnr::statement_type::FOR:
                  r += "FOR";
                  break;
               case njnr::statement_type::FOREACH:
                  r += "FOREACH";
                  break;
               case njnr::statement_type::IF:
                  r += "IF";
                  break;
               case njnr::statement_type::IFELSE:
                  r += "IFELSE";
                  break;
               case njnr::statement_type::LOOP:
                  r += "LOOP";
                  break;
               case njnr::statement_type::RETURN:
                  r += "RETURN";
                  break;
               case njnr::statement_type::SWITCH:
                  r += "SWITCH";
                  break;
               case njnr::statement_type::UNTIL:
                  r += "UNTIL";
                  break;
               case njnr::statement_type::WHILE:
                  r += "WHILE";
                  break;
               case njnr::statement_type::INVALID:
               default:
                  r += "INVALID";
                  break;
            }
            if (rettype == njnr::type::CHECK)
            {
               r += "Set to Check: ...\n";
               r += printCheckReturn();
               if (expr->gettype() == njnr::type::CHECK)
               {
                  r += "INTERNAL ERROR\n";
               }
            }
            else
            {
               r += Compiler::getStringFromType(rettype);
            }
         }
      return r;
   }

   Statement::Statement() : ReturnPacket{},
                            stype{njnr::statement_type::INVALID},
                            expr{nullptr},
                            rettype{njnr::type::VOID}
 {}

   Statement::~Statement()
   {
      report(njnr::logType::debug,
             "running Statement() Destructor");
      report(njnr::logType::debug, this->toString());
   }

   statement_type Statement::getstype()
   {
      return stype;
   }

   void Statement::setstype(statement_type t)
   {
      stype = t;
   }

   void Statement::setexpr(std::shared_ptr<ReturnPacket> expr)
   {
      this->expr = expr;
   }

   std::shared_ptr<ReturnPacket> Statement::getexpr()
   {
      return expr;
   }

   type Statement::getrettype()
   {
       return rettype;
   }

   void Statement::setrettype(njnr::type t)
   {
       rettype = t;
   }

std::string Statement::printCheckReturn(void) const
{  std::string r{};
    r = "Checking return type ....\n";
    switch (expr->gettype())
    {
        case njnr::type::CHAR:
           r += "CHAR: ";
           r += dynamic_pointer_cast<Constant>(expr)->toString() +
                "\n";
           break;
        case njnr::type::CHECK:
           r +="Check\n";
           break;
        case njnr::type::FLOAT:
           r += "FLOAT: ";
           r += dynamic_pointer_cast<Constant>(expr)->toString() + "\n";
           break;
        case njnr::type::IDENT:
           r += "IDENT: ";
           r += dynamic_pointer_cast<Identifier>(expr)->toString() + "\n";
           break;
        case njnr::type::INT:
           r += "INT: ";
           r += dynamic_pointer_cast<Constant>(expr)->toString() + "\n";
           break;
        case njnr::type::REFFLOAT:
           r += "REFFLOAT: ";
//           r += dynamic_cast<CharConstant*>(expr)->toString() + "\n";
           break;
        case njnr::type::REFINT:
           r += "REFINT: ";
//           r += dynamic_cast<CharConstant*>(expr)->toString() + "\n";
           break;
        case njnr::type::REFSTR:
           r += "REFSTR: ";
//           r += dynamic_cast<CharConstant*>(expr)->toString() + "\n";
           break;
        case njnr::type::STMT:
           r += "STMT: ";
           r += dynamic_pointer_cast<Statement>(expr)->toString() + "\n";
           break;
        case njnr::type::STR:
           r += "STR: ";
           r += dynamic_pointer_cast<Constant>(expr)->toString() + "\n";
           break;
        case njnr::type::VOID:
           r += "VOID: ";
           break;
        default:
           r += "INVALID";
           break;
    }
   return r;
}
