#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "debug.hpp"
#include "compiler.hpp"
#include "njnr.tab.hpp"

using namespace njnr;
namespace njnr
{

   void Compiler::block1_start_trans_unit()
   {
       code_generator.gen_label("main");
       code_generator.gen_call(code_generator.genlabelw("main",mainlabel),0);

   }

   Funcb* Compiler::create_full_function(funcheadertype* funcheader, List* funcbody)
   {
      Funcb* out{nullptr};
      out = new Funcb{};
      out->setreturntype(funcheader->returntype);

      return nullptr;
   }

   void Compiler::block2_func_funcheader_source(funcheadertype** inFuncHeaderptr)
   {
       auto templabel{mainlabel};
       if(is_function_decl_or_def_accurate(inFuncHeaderptr,false))
       {
           mysymtab->openscope();
           if((*inFuncHeaderptr)->name != "main")
           {
               templabel = currentFunc->getlabel();
               install_parameters_into_symbol_table_curren_scope(inFuncHeaderptr);
           }
           code_generator.gen_label(code_generator.genlabelw((*inFuncHeaderptr)->name, templabel ));
       }
   }
   void Compiler::block3_func_funcheader_source_funcbody()
   {
       mysymtab->closescope();
   }

   void Compiler::block4_func_funcheader_semi(funcheadertype* inFuncHeader)
   {
       auto found = mysymtab->lookupB(inFuncHeader->name);
       if(  found  == nullptr )
       {
           auto tempEntry =  mysymtab->createFunc(	inFuncHeader->name,
                                                   inFuncHeader->returntype,
                                                   inFuncHeader->paramlist
                                                 );
           mysymtab->install(tempEntry);
           return;
       }
       is_function_decl_or_def_accurate(&inFuncHeader,true);
   }

   void Compiler::block5_funcheader_error_semi(funcheadertype** inFuncHeaderptr)
   {
       funcheadertype* inFuncHeader{*inFuncHeaderptr};
       if(inFuncHeader !=nullptr)
       {
           delete inFuncHeader;
           inFuncHeader = nullptr;
       }
   }

   funcheadertype*  Compiler::funcheader_returntype_ident_lpar_paramdef_rpar_helper(njnr::Identifier inIdent,
                                                                                    List* inParamdeflist,
                                                                                    njnr::type inreturntype)
   {
      funcheadertype* retFuncHeader{nullptr};

      retFuncHeader             = new funcheadertype;
      if(nullptr != retFuncHeader)
      {
         retFuncHeader->returntype = inreturntype;
         retFuncHeader->name       = inIdent.getvalue();
         retFuncHeader->paramlist  = inParamdeflist;
         /* FIXME: NEED TO REINCORPORATE THIS BACK IN. Somehow lists provide a type? where and why?
         if(inParamdeflist->gettype() == type::VOID)
         {
            retFuncHeader->ttype = type::VOID;
         }
         */
      }
      return retFuncHeader;
   }
   void Compiler::block25_funcbody_lcbra_decls_source()
   {
//       auto temp{mainlocal};
       if(currentFunc->getvalue() == "main")
       {
           mainlocal = offset_counter-5;
//           temp = mainlocal;
       }
       else
       {
           switch(currentFunc->getparam_type()[0])
           {
           case njnr::type::VOID:
               currentFunc->setlocalcount( offset_counter - 5);
               break;
           default:
               currentFunc->setlocalcount( offset_counter - 5 - currentFunc->getnum_param());
              break;
          }
//          temp = currentFunc->getlocalcount();
      }
  }
   
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
   Funcb* Compiler::create_and_return_a_fn_body_statement_element(Statement* stmt)
   {
       if(stmt->getstype() == statement_type::RETURN)
       {
           std::cout << "found a return statement of type " << static_cast<int>(stmt->getrettype()) << std::endl;
           this->returnTypes.appendList(stmt->getrettype());
       }

      return nullptr;
   }
   Funcb* Compiler::add_statement_to_fn_body_and_return(List* func, Statement* stmt)
   {
       if(stmt->getstype() == statement_type::RETURN)
       {
           std::cout << "attaching found a return statement of type " << static_cast<int>(stmt->getrettype()) << std::endl;
           this->returnTypes.appendList(stmt->getrettype());
       }

      return nullptr;
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

   void Compiler::variableFetch(ReturnPacket* inPacket, bool conversionNeeded)
   {
       if( inPacket->getlval())
       {
           const static std::string fetch{"fetch"};
           switch(inPacket->gettype())
           {

           case type::INT:
               break;

           case type::FLOAT:

           default:
               if(conversionNeeded)
               {
               }
               break;
           }
       }
   }
   void Compiler::variableFetchWithNumericCheck(ReturnPacket* inPacket, bool conversionNeeded)
   {
       if(inPacket->getnumeric() )
       {
           variableFetch(inPacket,conversionNeeded);
       }
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

   void Compiler::normalStore(njnr::type intype)
   {
       switch(intype)
       {
       case(njnr::type::INT):
           break;
       case(njnr::type::FLOAT):
           break;
       default:
           break;
       }
   }
   void Compiler::variableStore(njnr::type intype)
   {
       static std::string instruction{""};
       static std::string letter{""};
       switch(intype)
       {
       case njnr::type::INT:
           instruction = "int";
           letter = "I";
           break;
       case njnr::type::FLOAT:
           instruction = "flt";
           letter = "R";
           break;
       default:
           break;
       }
       warning("expressons are of different type, data may be lost","");

   }
   ReturnPacket* Compiler::block40_expr_equalexpr_equal_equalexpr(ReturnPacket** inequalexprPacketptr,ReturnPacket** inotherequalexprPacketptr)
   {
       ReturnPacket* outPacket{nullptr};
       ReturnPacket* inequalexprPacket{*inequalexprPacketptr};
       ReturnPacket* inotherequalexprPacket{*inotherequalexprPacketptr};

       if( ! inequalexprPacket->getlval() )
       {
           error("Cannot make assignment. Left hand side is not a correct lval","");
           return outPacket;
       }
   //    else if( ! inotherequalexprPacket->getnumeric() )
   //    {
   //        error("Cannot make assignment, Right hand side is not numeric.","");
   //        return outPacket;
   //    }
       variableFetchWithNumericCheck(inotherequalexprPacket,false); //conversion to integer not needed

       if( inequalexprPacket->gettype() == inotherequalexprPacket->gettype() )
       {
           outPacket = new ReturnPacket{true,inequalexprPacket->gettype(),true,0};
           normalStore(inequalexprPacket->gettype());
       }
       else if(inequalexprPacket->gettype() == njnr::type::INT &&
               inotherequalexprPacket->gettype() == type::FLOAT)
       {
           variableStore(njnr::type::INT);
           outPacket = new ReturnPacket{true,njnr::type::INT,true,0};
       }
       else if(inequalexprPacket->gettype() == njnr::type::FLOAT &&
               inotherequalexprPacket->gettype() == njnr::type::INT)
       {
           variableStore(njnr::type::FLOAT);
           outPacket = new ReturnPacket{true,njnr::type::FLOAT,true,0};
       }
       return outPacket;
   }

   void Compiler::block42_equalexpr_relexpr_eqop_source(ReturnPacket** relexprPacketptr)
   {
       variableFetchWithNumericCheck(*relexprPacketptr,false);
   }

   ReturnPacket* Compiler::block43_equalexpr_relexpr_helper(njnr::eqtype ineqop, std::string need_letter_b)
   {
       warning("expressons are of different type, data may be lost","");
       switch(ineqop)
       {
       case eqtype::NEQ:
           break;
       case eqtype::EQEQ:
           break;
       default:
           break;
       }

       return new ReturnPacket{false,njnr::type::INT,true,0};
   }
   ReturnPacket* Compiler::block43_equalexpr_relexpr_eqop_source_relexpr(njnr::eqtype ineqop, ReturnPacket** relexprPacketptr, ReturnPacket** otherrelexprPacketptr)
   {
       ReturnPacket * outPacket{new ReturnPacket{}};
       ReturnPacket * relexprPacket{* relexprPacketptr};
       ReturnPacket * otherrelexprPacket{* otherrelexprPacketptr};

       variableFetchWithNumericCheck(*otherrelexprPacketptr,false);
       outPacket->setlval(false);
       if(relexprPacket->getnumeric() && otherrelexprPacket->getnumeric() )
       {
           outPacket->setnumeric(true);
           outPacket->settype(njnr::type::INT);
           if( relexprPacket->gettype() == otherrelexprPacket->gettype() )
           {
               outPacket->settype( njnr::type::INT);
               switch(ineqop)
               {
               case eqtype::NEQ:
                   if(relexprPacket->gettype() == njnr::type::INT){}
                   else if(relexprPacket->gettype() == njnr::type::FLOAT){}
                   break;
               case eqtype::EQEQ:
                   if(relexprPacket->gettype() == njnr::type::INT){}
                   else if(relexprPacket->gettype() == njnr::type::FLOAT){}
                   break;
               default:
                   break;
               }
           }
           else if(relexprPacket->gettype() == njnr::type::INT &&
                   otherrelexprPacket->gettype()== njnr::type::FLOAT)
           {
               outPacket = block43_equalexpr_relexpr_helper(ineqop,"b");
           }
           else if(relexprPacket->gettype() == njnr::type::FLOAT &&
                   otherrelexprPacket->gettype() == njnr::type::INT)
           {
               outPacket = block43_equalexpr_relexpr_helper(ineqop,"");
           }
       }
       else
       {
           error("non numeric in operation","");
           outPacket->setnumeric(false);  //should be false right?
       }
       return outPacket;
   }

   void Compiler::block45_relexpr_simpleexpr_relop_source(ReturnPacket** insimplePacketptr)
   {
       variableFetchWithNumericCheck(*insimplePacketptr,false);
   }
   ReturnPacket* Compiler::block46_relexpr_simpleexpr_relop_helper(njnr::reltype inrelop, std::string need_letter_b)
   {
       warning("expressons are of different type, data may be lost","");

       switch(inrelop)
       {
       case reltype::LES:
           break;
       case reltype::LEQ:
           break;
       case reltype::GRE:
           break;
       case reltype::GEQ:
           break;
       default:
           break;
       }
       return new ReturnPacket{false,njnr::type::INT,true,0};
   }
   ReturnPacket* Compiler::block46_relexpr_simpleexpr_relop_source_simpleexpr(ReturnPacket** simpleexprPacketptr, njnr::reltype inrelop, ReturnPacket** othersimpleexprPacketptr)
   {
       ReturnPacket * outPacket{new ReturnPacket{}};
       ReturnPacket * simpleexprPacket{*simpleexprPacketptr};
       ReturnPacket * othersimpleexprPacket{*othersimpleexprPacketptr};

       variableFetchWithNumericCheck(*othersimpleexprPacketptr,false);
       outPacket->setlval(false);
       if(simpleexprPacket->getnumeric() && othersimpleexprPacket->getnumeric() )
       {
           outPacket->setnumeric(true);
           outPacket->settype( njnr::type::INT);
           if( simpleexprPacket->gettype() == othersimpleexprPacket->gettype() )
           {
               outPacket->settype( njnr::type::INT);
               switch(inrelop)
               {
               case reltype::LES:
                   if(simpleexprPacket->gettype() == type::INT){}
                   else if(simpleexprPacket->gettype() == type::FLOAT){}
                   break;
               case reltype::LEQ:
                   if(simpleexprPacket->gettype() == type::INT){}
                   else if(simpleexprPacket->gettype() == type::FLOAT){}
                   break;
               case reltype::GRE:
                   if(simpleexprPacket->gettype() == type::INT){}
                   else if(simpleexprPacket->gettype() == type::FLOAT){}
                   break;
               case reltype::GEQ:
                   if(simpleexprPacket->gettype() == type::INT){}
                   else if(simpleexprPacket->gettype() == type::FLOAT){}
                   break;
               default:
                   break;
               }
           }
           else if(simpleexprPacket->gettype() == njnr::type::INT &&
                   othersimpleexprPacket->gettype() == type::FLOAT)
           {
               outPacket = block46_relexpr_simpleexpr_relop_helper(inrelop,"b");
           }
           else if(simpleexprPacket->gettype() == type::FLOAT &&
                   othersimpleexprPacket->gettype() == type::INT)
           {
               outPacket = block46_relexpr_simpleexpr_relop_helper(inrelop,"");
           }
       }
       else
       {
           error("non numeric in operation","");
           outPacket->setnumeric(false);
       }
       return outPacket;
   }

   void Compiler::variableFetchWithNumericCheckAndLvalCheck(ReturnPacket* insimplePacket, bool conversionNeeded)
   {
       if(insimplePacket->getlval())
       {
           variableFetchWithNumericCheck(insimplePacket,conversionNeeded);
       }
   }

   void Compiler::block48_simpleexpr_simpleexpr_addop_source(ReturnPacket** insimplePacketptr)
   {
       variableFetchWithNumericCheckAndLvalCheck(*insimplePacketptr,false);
   }
   ReturnPacket* Compiler::block49_simpleexpr_addop_helper(njnr::addtype inaddop,std::string need_letter_b)
   {
       warning("expressons are of different type, data may be lost","");
       switch(inaddop)
       {
       case addtype::PLS:
           break;
       case addtype::MIN:
           break;
       default:
           break;
       }
       return new ReturnPacket{false,njnr::type::FLOAT,true,0};
   }

   ReturnPacket* Compiler::block49_simpleexpr_simpleexpr_addop_source_term(ReturnPacket** simpleexprPacketptr, njnr::addtype inaddop, ReturnPacket** termPacketptr)
   {
       ReturnPacket * outPacket{new ReturnPacket{}};
       ReturnPacket * simpleexprPacket{*simpleexprPacketptr};
       ReturnPacket * termPacket{*termPacketptr};

       variableFetchWithNumericCheck(*termPacketptr,false);
       outPacket->setlval(false);
       if(simpleexprPacket->getnumeric() && termPacket->getnumeric())
       {
           outPacket->setnumeric(true);
           if( simpleexprPacket->gettype() == termPacket->gettype() )
           {
               outPacket->settype( simpleexprPacket->gettype());
               switch(inaddop)
               {
               case addtype::PLS:
                   if(simpleexprPacket->gettype() == type::INT){}
                   else if(simpleexprPacket->gettype() == type::FLOAT){}
                   break;
               case addtype::MIN:
                   if(simpleexprPacket->gettype() == type::INT){}
                   else if(simpleexprPacket->gettype() == type::FLOAT){}
                   break;
               default:
                   break;
               }
           }
           else if(simpleexprPacket->gettype() == njnr::type::INT
                   && termPacket->gettype() == type::FLOAT)
           {
               outPacket = block49_simpleexpr_addop_helper(inaddop,"b");
           }
           else if(simpleexprPacket->gettype() == njnr::type::FLOAT
                   && termPacket->gettype() == type::INT)
           {
               outPacket = block49_simpleexpr_addop_helper(inaddop,"");
           }
       }
       else
       {
           error("non numeric in operation","");
           outPacket->setnumeric(false);
       }
       return outPacket;
   }

   void Compiler::block51_term_term_mulop_source(ReturnPacket** inPacketptr)
   {
       variableFetchWithNumericCheckAndLvalCheck(*inPacketptr,false);
   }

   ReturnPacket* Compiler::block52_term_mulop_helper(njnr::multype inmulop,std::string need_letter_b)
   {
       warning("expressons are of different type, data may be lost","");
       switch(inmulop)
       {
       case multype::DIV:
           break;
       case multype::MULT:
           break;
       default:
           break;
       }
       return new ReturnPacket{false,njnr::type::FLOAT,true,0};
   }
   ReturnPacket* Compiler::block52_term_term_mulop_source_factor(ReturnPacket** intermPacketptr, njnr::multype inmulop,ReturnPacket** infactorPacketptr)
   {
       ReturnPacket* outtermPacket{new ReturnPacket{}};
       ReturnPacket* intermPacket{*intermPacketptr};
       ReturnPacket* infactorPacket{*infactorPacketptr};
       variableFetchWithNumericCheck(*infactorPacketptr,false);
       outtermPacket->setlval(false);
       if(intermPacket->getnumeric() && infactorPacket->getnumeric())
       {
           outtermPacket->setnumeric(true);
           if( intermPacket->gettype() == infactorPacket->gettype() )
           {
               outtermPacket->settype(  intermPacket->gettype() );
               switch(inmulop)
               {
               case multype::DIV:
                   if(intermPacket->gettype()== type::INT)
                   {
                   }
                   else if(intermPacket->gettype()== type::FLOAT)
                   {
                   }
                   break;
               case multype::MULT:
                   if(intermPacket->gettype()== type::INT)
                   {
                   }
                   else if(intermPacket->gettype()== type::FLOAT)
                   {
                   }
                   break;
               default:
                   break;
               }
           }
           else if(intermPacket->gettype() == type::INT
                   && infactorPacket->gettype()== type::FLOAT)
           {
               outtermPacket = block52_term_mulop_helper(inmulop,"b");
           }
           else if(intermPacket->gettype() == type::FLOAT && infactorPacket->gettype() == type::INT)
           {
               outtermPacket =  block52_term_mulop_helper(inmulop,"");
           }
       }
       else
       {
           error("non numeric in operation","");
           outtermPacket->setnumeric(false);
       }
       return outtermPacket;
   }

   ReturnPacket* Compiler::block54_factor_constant(Constant* inConstant)
   {
      bool need_gen = false;
//      int  gen_type = 0;

      if(true == need_gen)
      {
         switch(inConstant->gettype())
         {
            case type::INT:
               break;
            case type::FLOAT:
               break;
            case type::STR:
               break;
            default:
               error("constant is not a correct type of constant","");
               break;
         }
      }
   
      return inConstant;
   }

   ReturnPacket* Compiler::block55_factor_ident(njnr::Identifier inIdent)
   {
      ReturnPacket*  outPacket{nullptr};
      TableEntry *resultLookup{nullptr};
      bool gen_code = false;
//      int  gen_type = 0;

      outPacket = new Identifier{inIdent};
      if(true == gen_code)
      {
         if(inIdent.getvalue() != "main")
         {
           #ifdef DEBUG
            //				fprintf(stderr,"the name of the identifier here is:  %s\n", (char*)$<value.svalue>1);
           #endif

            if( (nullptr != (resultLookup =  mysymtab->lookupB(inIdent.getvalue()))))
            {
               outPacket->settype(resultLookup->getBinding()->gettype());
               outPacket->setlval(true);
               if(resultLookup->getBinding()->gettype() == type::INT || resultLookup->getBinding()->gettype() == type::FLOAT)
               {
                  outPacket->setnumeric(true);
               }
               if(mysymtab->inCscope(inIdent.getvalue()))
               {
               }
               else
               {
                  switch(resultLookup->getself())
                  {
                     case btype::VAR:
                     {
                       #ifdef DEBUG
                        // char temp_char = (char)(*outPacket)->gettype();
                        // if((*outPacket)->gettype() !=  nullptr) fprintf(stderr,"type is: %s\n", &temp_char);
                        // if(resultLookup->getBinding()->gettype() != nullptr) fprintf(stderr,"type is: %d\n", resultLookup->getBinding()->gettype());
                       #endif
                        int level_diff {mysymtab->getleveldif(inIdent.getvalue())};
                        if(level_diff != -1)
                        {
                        }
                        else
                        {
                           debugprint("error, somehow level difference was -1\n","");
                        }
                        break;
                     }

                     case btype::PARAM:
                       #ifdef DEBUG
                        std::cerr << "type is: " <<  (int)outPacket->gettype() << std::endl ;
                       #endif
                        break;

                     default:
                        error("Variable is unknown or undelcared","");
                        break;
                  }
               }
            }
            else
            {
               outPacket->settype(type::VOID);
               error("Variable is unknown or undelcared, couldn't be found in symbol table'","");
            }
         }
         else
         {
            error("Main is not a variable name","");
         }
      }
      return outPacket;
   }

   ReturnPacket* Compiler::block57_factor_addop_factor_uminus(njnr::addtype inop, ReturnPacket** inPacketptr)
   {
       ReturnPacket* outPacket{new ReturnPacket{}};
       ReturnPacket* inPacket{*inPacketptr};
       if(inPacket->getnumeric())
       {
           switch(inop)
           {
           case njnr::addtype::MIN:
               variableFetchWithNumericCheck(*inPacketptr,false);
               switch(inPacket->gettype())
               {
               case type::INT:
                   break;
               case type::FLOAT:
                   break;
               default:
                   break;
               }
               break;
           case njnr::addtype::PLS:
               variableFetchWithNumericCheck(*inPacketptr,false);
               break;
           default:
               break;
           }
       }
       outPacket->setlval(false);
       outPacket->settype(inPacket->gettype() );
       if(inPacket->getnumeric())
       {
           outPacket->setnumeric(true);
       }
       else
       {
           error("cannot change sign of non numeric expression","");
       }
       return outPacket;
   }

   ReturnPacket* Compiler::block58_factor_adof_ident(njnr::Identifier inPacket)
   {
       ReturnPacket* outPacket{new ReturnPacket{}};
       TableEntry*tempE; //, *tempE2;
       if( inPacket.getvalue() != "main")
       {
           if( mysymtab->lookup(inPacket.getvalue()) == nullptr)
               error("variable undeclared, please declare variables before using them","");
           else
           {
               tempE =	mysymtab->lookupB(inPacket.getvalue());
               if(tempE != nullptr)
               {
                   if(tempE->getself() == btype::VAR || tempE->getself() == btype::PARAM)
                   {
                       switch(tempE->getself())
                       {
                       case btype::VAR:
                           outPacket->settype(((Varb*)(tempE->getBinding()))->gettype());
   #ifdef DEBUG
   //						std::cerr << "type is: "  << (int)outPacket->gettype()) << std::endl;
   #endif
                           outPacket->setlval(false);
                           if(((Varb*)(tempE->getBinding()))->gettype() == type::INT || ((Varb*)(tempE->getBinding()))->gettype() == type::FLOAT)
                               outPacket->setnumeric(true);
                           if(mysymtab->inCscope(inPacket.getvalue()))
                           {
                           }
                           else
                           {
                               int level_diff{mysymtab->getleveldif(inPacket.getvalue())};
                               if(level_diff != -1)
                               {
                               }
                               else
                               {
                                   debugprint("error level differince was -1\n","");
                               }
                               //do something else
                           }
                           break;
                       case btype::PARAM:
                           outPacket->settype( ((Paramb*)(tempE->getBinding()))->gettype());
   #ifdef DEBUG
   //						std::cerr <<  "type is: " <<  (int)outPacket->gettype()) << std::endl;
   #endif
                           outPacket->setlval(false);
                           if(((Paramb*)(tempE->getBinding()))->gettype() == type::INT || ((Paramb*)(tempE->getBinding()))->gettype() == type::FLOAT)
                               outPacket->setnumeric(true);
                           if(mysymtab->inCscope(inPacket.getvalue()))
                           {
                           }
                           else
                           {
                               //do something else
                           }
                           break;
                       default:
                           break;
                       }
                   }
                   else
                       error("Variable is unknown or undelcared", "");
               }
               else
               {
                   outPacket->setlval(false);
                   outPacket->setnumeric(false);
                   outPacket->settype(type::VOID);
                   error("Variable is unknown or undelcared","");
               }
           }
           return outPacket;
       }
       else
       {
           error("Main is not a variable name", "");
       }
       return outPacket;
   }

   ReturnPacket* Compiler::block60_function_call_ident_lpar_rpar(njnr::Identifier inIdent)
   {
       ReturnPacket* outPacket{new ReturnPacket{}};
       outPacket->setlval(false);
       Funcb* tempb;
       TableEntry* tempE;
       TableEntry*tempE2;
       if((tempb=(Funcb*) mysymtab->lookup(inIdent.getvalue())) == nullptr)
       {
           error("function undeclared, please declare functions before using them","");
       }
       else
       {
           tempE2 = new TableEntry{inIdent.getvalue()};
           tempE =	mysymtab->lookupB(inIdent.getvalue());
           if( tempE !=nullptr)
           {
               if(tempE->getself() == btype::FUNC)
               {
                   if(tempb->getreturntype() != type::VOID)
                   {
                       outPacket->setlval(true);
                   }
                   else
                   {
                       outPacket->setlval(false);
                   }
                   if(tempb->getnum_param() > 1 )
                   {
                       error("Function takes no parameters, only void in the declaration and definition","");
                   }
                   if(tempb->getnum_param() == 1)
                   {
                       if(tempb->getparam_type()[0] != njnr::type::VOID)
                       {
                           error("Function takes no parameters, only void in the declaration and definition","");
                       }
                   }
                   outPacket->settype( tempb->getreturntype());
                   if(outPacket->gettype() == type::INT || outPacket->gettype() == type::FLOAT)
                   {
                       outPacket->setnumeric(true);
                   }
                   else
                   {
                       outPacket->setnumeric(false);
                   }
                   code_generator.gen_call(code_generator.genlabelw(inIdent.getvalue(), tempb->getlabel()), 0);
               }
               else
               {
                   error("Function call with an unknown function name", "");
               }
           }
           else
           {
               error("fuction undeclared","");
           }
           delete tempE2;
           tempE2=nullptr;
           return outPacket;
       }
       return outPacket;
   }

   ReturnPacket* Compiler::block62_func_call_with_params_name_and_params_rpar(ReturnPacket** nameAndparamptr)
   {
       ReturnPacket* funcCallWparam{new ReturnPacket{}};
       funcCallWparam->setnumeric((* nameAndparamptr)->getnumeric());
       funcCallWparam->setlval(false);
       funcCallWparam->settype((* nameAndparamptr)->gettype());
       if((* nameAndparamptr)->funcent!=nullptr)
       {
           if(((* nameAndparamptr)->funcent)->getself() == btype::FUNC)
           {
               if( ((Funcb*)(((* nameAndparamptr)->funcent)->getBinding()))->getreturntype() != type::VOID)
               {
                   funcCallWparam->setnumeric(true);
               }
               else
               {
                   funcCallWparam->setnumeric(false);
               }
           }
           if( "scanf" == (*nameAndparamptr)->funcent->getName())
           {
               code_generator.gen_call("$scanf",(*nameAndparamptr)->params);
           }
           else if("printf" ==  (*nameAndparamptr)->funcent->getName())
           {
               code_generator.gen_call("$printf",(*nameAndparamptr)->params);
           }
           else
           {
               if( ((Funcb*)((*nameAndparamptr)->funcent->getBinding()))->getlabel()==0)
               {
                   ((Funcb*)((*nameAndparamptr)->funcent->getBinding()))->setlabel(code_generator.getlabel());
               }
               code_generator.gen_call( code_generator.genlabelw((*nameAndparamptr)->funcent->getName(),
                                        ((Funcb*)((*nameAndparamptr)->funcent->getBinding()))->getlabel()),
                                        ((Funcb*)((*nameAndparamptr)->funcent->getBinding()))->getnum_param());
           }
       }
       return funcCallWparam;
   }

   ReturnPacket* Compiler::block63_name_and_params_ident_lpar_source(njnr::Identifier inPacket)
   {
       ReturnPacket* inEntry{new ReturnPacket{}};

       inEntry->funcent = nullptr;
       inEntry->funcent =  mysymtab->lookupB(inPacket.getvalue());
   #ifdef DEBUG
       //	printTree(mysymtab);
   //	std::cerr <<  "this the name of function called and the lookup value: "  << inPacket.getvalue().c_str()) << std::endl;
       if( mysymtab->lookupB(inPacket.getvalue())==nullptr)
           std::cerr <<  "it was null\n";
       else
           std::cerr << "wasn't null\n";
   #endif
       if (inEntry->funcent != nullptr)
       {
           inEntry->funcent->setName(inPacket.getvalue());
       }
       return inEntry;
   }

   ReturnPacket* Compiler::block64_name_and_params_ident_lpar_source_expr(njnr::Identifier inIdent, ReturnPacket** inEntryptr, ReturnPacket** inPacketptr)
   {
       TableEntry*tempE, *tempE2;
       ReturnPacket* outPacket{new ReturnPacket{}};
       ReturnPacket* inPacket{*inPacketptr};
       ReturnPacket* inEntry{*inEntryptr};
       outPacket->setlval(false);
       Funcb* tempB;
       tempB = (Funcb*) mysymtab->lookup(inIdent.getvalue());
       if(tempB ==nullptr)
       {
           error("function undelcared, please declare functions before using them","");
           error("1","");
           outPacket->funcent=nullptr;
       }
       else
       {
           //warning("just checking value of entry: %s",$<value.funcentvalue>$->name);
           tempE2 = new TableEntry{inIdent.getvalue()};
           tempE = mysymtab->lookupB(inIdent.getvalue());
           if( tempE !=nullptr)
           {
               if(tempE->getself() != btype::FUNC)
               {
                   error("function undeclared, please declare functions before using them", "");
                   error("2","");
                   outPacket->funcent=nullptr;
               }
               else
               {
                   if(tempB->getnum_param() ==0)
                   {
                       error("Paramter given for a function that takes no parameters.","");
                   }
                   else if(tempB->getnum_param() == -1)
                   {
   #ifdef DEBUG
   //					fprintf(stderr,"SPRINTF OR PRINTF mismatch: FUNCTION NAME: %s\n",$1);
                       //				fprintf(stderr,"SPRINTF OR PRINTF: FUNCTION TYPE: %d\n",(int)$4->type);
   //					fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
   //					fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
   //					fprintf(stderr,"SPRINTF OR PRINTF: $4 TYPE: %d\n",(int)$4->type);
   //					fprintf(stderr,"SPRINTF OR PRINTF: tempB->param_type[0] TYPE: %d\n",(int)tempB->param_type[0]);
   #endif
                       if(inPacket->gettype() != tempB->getparam_type()[0])
                       {
                           error("parameter type is different in declaration and in function call","");
                       }
                       else
                       {
   //							code_generator.gen_instr_S("pushs",$<value.svalue>4);
                       }
                       outPacket->settype(tempB->getparam_type()[0]);
                       if(outPacket->gettype() == type::INT || outPacket->gettype() == type::FLOAT)
                       {
                           outPacket->setnumeric(true);
                       }
                       else
                       {
                           outPacket->setnumeric(false);
                       }
                       outPacket->funcent = inEntry->funcent;
                       outPacket->params = 1;
                   }
                   else
                   {
                       variableFetchWithNumericCheck(inPacket,false);

                       if( ! tempB->getparam_type().empty())
                       {
                           if(inPacket->gettype() != tempB->getparam_type()[0])
                           {
   #ifdef DEBUG
   //							fprintf(stderr,"Function mismatch 2: FUNCTION NAME: %s\n",$1);
   //							fprintf(stderr,"Function mismatch 2: FUNCTION TYPE: %d\n",(int)$4->type);
   //							fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
   //							fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
   #endif
                               if(tempB->getparam_type()[0]!= type::INT && tempB->getparam_type()[0]!= type::FLOAT)
                                   error("Parameter type is different in declaration and in function call","");
                               else if(tempB->getparam_type()[0]== type::INT)
                               {
   #ifdef DEBUG
   //								fprintf(stderr,"Function mismatch 3: FUNCTION NAME: %s\n",$1);
   //								fprintf(stderr,"Function mismatch 3: FUNCTION TYPE: %d\n",(int)$4->type);
   //								fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
   //								fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
   #endif
                                   switch(inPacket->gettype())
                                   {
                                   case type::FLOAT:
                                       warning("Paramter expression will lose data because of different type","");
                                       break;
                                   case type::INT:
                                       break;
                                   default:
                                       error("Parameter type is different in declaration and function call","");
                                       break;
                                   }
                               }
                               else if(tempB->getparam_type()[0]== type::FLOAT)
                               {
   #ifdef DEBUG
   //								fprintf(stderr,"Function mismatch 4: FUNCTION NAME: %s\n",$1);
   #endif
                                   switch(inPacket->gettype())
                                   {
                                   case type::INT:
                                       warning("Parameter expression is different type than in declaration","");
                                       break;
                                   case type::FLOAT:
                                       break;
                                   default:
                                       error("Parameter type is different in declaration and function call","");
                                       break;
                                   }
                               }
                           }
                       }
                       outPacket->funcent=inEntry->funcent;
                       if(! tempB->getparam_type().empty())
                           outPacket->settype(tempB->getparam_type()[0]);
                       if(outPacket->gettype() == type::INT || outPacket->gettype() == type::FLOAT)
                           outPacket->setnumeric(true);
                       else
                           outPacket->setnumeric(false);
                       outPacket->params=1;
                   }
               }
           }
           else
           {
               error("Function is undeclared","");
           }
           delete tempE2;
           tempE2=nullptr;
       }
       return outPacket;
   }

   ReturnPacket* Compiler::block65_name_and_params_name_and_params_comma_expr(ReturnPacket** innameAndparamPacketptr, ReturnPacket** inexprPacketptr)
   {
       ReturnPacket* outPacket{new ReturnPacket{}};
       ReturnPacket* innameAndparamPacket{*innameAndparamPacketptr};
       ReturnPacket* inexprPacket{*inexprPacketptr};

       TableEntry*tempE, *tempE2;
       outPacket->setlval( false);
       Funcb* tempB;
       if(innameAndparamPacket->funcent == nullptr)
       {
           error("function undelcared, please declare functions before using them","");
           error("3","");
       }
       else
       {
           outPacket->funcent = innameAndparamPacket->funcent;
           tempE2 = new TableEntry{innameAndparamPacket->funcent->getName()};

           tempB= (Funcb*) mysymtab->lookup( innameAndparamPacket->funcent->getName());
           if( (tempE=  mysymtab->lookupB(innameAndparamPacket->funcent->getName()))!=nullptr)
           {
               if(tempE->getself() != btype::FUNC)
               {
                   error("function undeclared, please declare functions before using them", "");
                   error("4","");
               }
               else
               {
                   if(tempB->getnum_param() ==0)
                   {
                   }
                   else if(tempB->getnum_param() == -1)
                   {
                       outPacket->settype( tempB->getparam_type()[innameAndparamPacket->params] );
                       if(outPacket->gettype() == type::INT || outPacket->gettype() == type::FLOAT)
                       {
                           outPacket->setnumeric(true);
                       }
                       else
                       {
                           outPacket->setnumeric(false);
                       }
                       outPacket->params = innameAndparamPacket->params +1;
                       outPacket->funcent= innameAndparamPacket->funcent;
                       if(outPacket->funcent->getName() != "scanf")
                       {
                           variableFetchWithNumericCheck(inexprPacket,false);
                       }
                   }
                   else if( innameAndparamPacket->params < tempB->getnum_param())
                   {
                       if(inexprPacket->gettype() != tempB->getparam_type()[innameAndparamPacket->params])
                       {
   #ifdef DEBUG
   //						fprintf(stderr,"Function mismatch before warning: FUNCTION NAME: %s\n", innameAndparamPacket->getname());
   #endif
   
                           warning("Parameter type is different in declaration and in function call","");
                           variableFetch(inexprPacket,false);
                           if(tempB->getparam_type()[innameAndparamPacket->params]== type::FLOAT)
                           {
                           }
                           else if(tempB->getparam_type()[innameAndparamPacket->params]== type::INT)
                           {
                           }
                       }
                       else
                       {
                           variableFetch(inexprPacket,false);
                       }
                       outPacket->settype( tempB->getparam_type()[innameAndparamPacket->params] );
                       if(outPacket->gettype() == type::INT || outPacket->gettype() == type::FLOAT)
                           outPacket->setnumeric(true);
                       else
                           outPacket->setnumeric(false);
                       outPacket->params= innameAndparamPacket->params +1;
                       outPacket->funcent= innameAndparamPacket->funcent;
                   }
                   else
                   {
                       error("Too many parameters given for function in function call.","");
                   }
               }
           }
           else
           {
               error("Function is undeclared","");
           }
           delete tempE2;
           tempE2=nullptr;
       }
       return outPacket;
   }

   List* Compiler::block69_identlist_ident(njnr::Identifier inIdent)
   {
       return List::mklist(&inIdent);
   }

   List* Compiler::block70_identlist_comma_ident(List** inIdentListptr, njnr::Identifier inIdent)
   {
       return (*inIdentListptr)->appendList(&inIdent);
   }
}
