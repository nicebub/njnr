#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "debug.hpp"
#include "compiler.hpp"
#include "njnr.tab.hpp"

using namespace njnr;
namespace njnr
{
void Compiler::dealwithstmtlist(List* stmtlist)
{
    if(nullptr != stmtlist)
    {
 		std::cout << "list size: " << stmtlist->size() << std::endl;
	    for(auto element: *stmtlist)
	    {
		   StmtListNode* s = dynamic_cast<StmtListNode*>(element);
		   if(nullptr != s)
   	          std::cout << "statement type: " << static_cast<int>(s->getstmt()->getstype()) << std::endl;
	    }
    }
}
   void Compiler::block29_stmt_expr_semi()
   {
   }

   Statement* Compiler::block30_stmt_return_semi()
   {
      Statement* outPacket{nullptr};

      outPacket = new Statement{};
      outPacket->settype(njnr::type::STMT);
      outPacket->setstype(njnr::statement_type::RETURN);
      outPacket->setrettype(njnr::type::VOID);

      return outPacket;
   }
   Statement* Compiler::block31_stmt_return_expr_semi(ReturnPacket* inPacket)
   {
      Statement* outStatement{nullptr};

      outStatement = new Statement{};
      outStatement->settype(type::STMT);
      outStatement->setstype(statement_type::RETURN);
      outStatement->setstmt(inPacket);
      outStatement->setrettype(njnr::type::CHECK);

      return outStatement;
   }

   ReturnPacket* Compiler::block32_stmt_while_source()
   {
       ReturnPacket* inPacket{new ReturnPacket{}};
       inPacket->m_pair.one=  othercounter;
       othercounter++;
       inPacket->m_pair.two =  othercounter;
       othercounter++;

       code_generator.gen_label(code_generator.genlabelw("",inPacket->m_pair.one));
       return inPacket;
   }
   void Compiler::block33_stmt_while_source_expr_semi_source_lpar_expr_rpar(ReturnPacket* insourcePacket, ReturnPacket* inexprPacket)
   {
       variableFetchWithNumericCheck(inexprPacket,true);
   }

   void Compiler::block34_5_stmt_helper(int one, int two)
   {
       code_generator.gen_label(code_generator.genlabelw("",two));
   }
   void Compiler::while_and_if_reducer(ReturnPacket* insourcePacket, ReturnPacket* inexprPacket, int number, std::string while_or_if)
   {
       ReturnPacket* inPacket{inexprPacket};
       if(! inPacket->getnumeric())
       {
           error("non numeric expression in " + while_or_if + " statement","");
           return;
       }
       else if(inPacket->gettype() != njnr::type::INT)
       {
           error("expression in " + while_or_if + " statement is not an integer","");
           return;
       }
       if(while_or_if == "while")
       {
           block34_5_stmt_helper(insourcePacket->m_pair.one,insourcePacket->m_pair.two);
       }
       else
       {
           code_generator.gen_label(code_generator.genlabelw("",number));
       }
   }
   void Compiler::block34_stmt_while_source_expr_semi_source_lpar_expr_rpar_source_stmt(ReturnPacket* insourcePacket, ReturnPacket* inexprPacket)
   {
       while_and_if_reducer(insourcePacket,inexprPacket,0,"while");
   }

   void Compiler::block35_stmt_ifexprstmt_else(ReturnPacket* insourcePacket)
   {
       block34_5_stmt_helper(insourcePacket->m_pair.two,insourcePacket->m_pair.one);
   }

   void Compiler::block36_7_stmt_helper(ReturnPacket* insourcePacket, int number)
   {
       while_and_if_reducer(nullptr,insourcePacket,number,"if"); //FIXME: need to acutally put in a value perhaps for inexprPacketptr
   }

   void Compiler::block36_stmt_ifexprstmt_else_source_stmt(ReturnPacket* inPacket)
   {
       block36_7_stmt_helper(inPacket,inPacket->m_pair.two);
   }

   void Compiler::block37_stmt_ifexprstmt(ReturnPacket* inPacket)
   {
       block36_7_stmt_helper(inPacket,inPacket->m_pair.one);
   }

   struct Pair Compiler::block38_ifexprstmt_if_lpar_expr_source(ReturnPacket* inexprPacket)
   {

       struct Pair rvalue;

       rvalue.one= othercounter;
       othercounter++;
       rvalue.two= othercounter;
       othercounter++;

       variableFetchWithNumericCheck(inexprPacket,true);
       return rvalue;
   }


}
