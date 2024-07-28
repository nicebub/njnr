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

namespace njnr
{
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
