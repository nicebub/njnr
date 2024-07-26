#include <config.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "debug.hpp"
#include "compiler.hpp"
#include "njnr.tab.hpp"
#include "List.hpp"
#include "ListNode.hpp"
namespace njnr
{
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

void Compiler::dealwithstmtlist(std::shared_ptr<List> stmtlist)
{
    if (nullptr != stmtlist)
    {
       std::cout << "list size: " << stmtlist->size() << std::endl;
       for (auto element : *stmtlist)
       {
         std::shared_ptr<StmtListNode> s = dynamic_pointer_cast<StmtListNode>(element);
         if (nullptr != s)
                std::cout << "statement type: " << static_cast<int>(s->
                                                              getstmt()->
                                                              getstype()) <<
                                                              std::endl;
       }
    }
}
   void Compiler::block29_stmt_expr_semi()
   {
   }

   std::shared_ptr<Statement> Compiler::stmt_return_expr_semi(std::shared_ptr<ReturnPacket> expr)
   {
      std::shared_ptr<Statement> statement{nullptr};

      statement = std::shared_ptr<Statement>(new Statement{});
      if (nullptr != statement)
      {
         statement->settype(type::STMT);
         statement->setstype(statement_type::RETURN);
         if (nullptr != expr)
         {
            statement->setrettype(njnr::type::INT);
         }
         else
         {
            statement->setrettype(njnr::type::VOID);
            expr = std::shared_ptr<ReturnPacket>(new ReturnPacket{});
         }

         statement->setexpr(expr);
      }

      return statement;
   }

   std::shared_ptr<ReturnPacket> Compiler::block32_stmt_while_source()
   {
       std::shared_ptr<ReturnPacket> inPacket{new ReturnPacket{}};
       inPacket->m_pair.one =  othercounter;
       othercounter++;
       inPacket->m_pair.two =  othercounter;
       othercounter++;

       code_generator.gen_label(code_generator.genlabelw("",
                                                inPacket->m_pair.one));
       return inPacket;
   }
   void Compiler::block33_stmt_while_source_expr_semi_source_lpar_expr_rpar(\
                    std::shared_ptr<ReturnPacket> insourcePacket,
                    std::shared_ptr<ReturnPacket> inexprPacket)
   {
       variableFetchWithNumericCheck(inexprPacket, true);
   }

   void Compiler::block34_5_stmt_helper(int one, int two)
   {
       code_generator.gen_label(code_generator.genlabelw("", two));
   }
   void Compiler::while_and_if_reducer(std::shared_ptr<ReturnPacket> insourcePacket,
                                       std::shared_ptr<ReturnPacket> inexprPacket,
                                       int number,
                                       std::string while_or_if)
   {
       std::shared_ptr<ReturnPacket> inPacket{inexprPacket};
       if (!inPacket->getnumeric())
       {
           error("non numeric expression in " + while_or_if +
                 " statement", "");
           return;
       }
       else if (inPacket->gettype() != njnr::type::INT)
       {
           error("expression in " + while_or_if +
                 " statement is not an integer",
                 "");
           return;
       }
       if (while_or_if == "while")
       {
           block34_5_stmt_helper(insourcePacket->m_pair.one,
                                 insourcePacket->m_pair.two);
       }
       else
       {
           code_generator.gen_label(code_generator.genlabelw("", number));
       }
   }
   void Compiler::
        block34_stmt_while_source_expr_semi_source_lpar_expr_rpar_source_stmt(\
                                         std::shared_ptr<ReturnPacket> insourcePacket,
                                         std::shared_ptr<ReturnPacket> inexprPacket)
   {
       while_and_if_reducer(insourcePacket, inexprPacket, 0, "while");
   }

   void Compiler::block35_stmt_ifexprstmt_else(std::shared_ptr<ReturnPacket> insourcePacket)
   {
       block34_5_stmt_helper(insourcePacket->m_pair.two,
                             insourcePacket->m_pair.one);
   }

   void Compiler::block36_7_stmt_helper(std::shared_ptr<ReturnPacket> insourcePacket,
                                        int number)
   {
      // FIXME(nicebub): need to acutally put in a value perhaps for
      //                 inexprPacketptr
       while_and_if_reducer(nullptr, insourcePacket, number, "if");
   }

   void Compiler::block36_stmt_ifexprstmt_else_source_stmt(\
                                           std::shared_ptr<ReturnPacket> inPacket)
   {
       block36_7_stmt_helper(inPacket, inPacket->m_pair.two);
   }

   void Compiler::block37_stmt_ifexprstmt(std::shared_ptr<ReturnPacket> inPacket)
   {
       block36_7_stmt_helper(inPacket, inPacket->m_pair.one);
   }

   struct Pair Compiler::block38_ifexprstmt_if_lpar_expr_source(\
                                            std::shared_ptr<ReturnPacket> inexprPacket)
   {
       struct Pair rvalue;

       rvalue.one = othercounter;
       othercounter++;
       rvalue.two = othercounter;
       othercounter++;

       variableFetchWithNumericCheck(inexprPacket, true);
       return rvalue;
   }


}  // namespace njnr
