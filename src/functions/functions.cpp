#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "debug.hpp"
#include "compiler.hpp"
#include "njnr.tab.hpp"
#include "symbol_table_stack.hpp"
using namespace njnr;
namespace njnr
{
   Funcb* Compiler::create_full_function(funcheadertype* funcheader, List* funcbody)
   {
    /**
     *    funcheadertype
     *      std::string   name;       // fn name
      njnr::List*   paramlist;  // list of parameters the fn accept as input
      njnr::type    returntype; // return type(if any) of fn
      njnr::type    ttype;      // type of fn?(TBD)

     * 
     */
      Funcb* out{nullptr};
      out = new Funcb{};
      if(nullptr != out)
      {
         out->setfuncbody_list(funcbody);
         if(nullptr != funcheader)
         {
            out->setfuncheader(funcheader);
            out->setreturntype(funcheader->returntype);
         }
      }
      checkfunctionReturnValues(out);
      return out;
   }

   void Compiler::block2_func_funcheader_source(funcheadertype** inFuncHeaderptr)
   {
       auto templabel{mainlabel};
       if(is_function_decl_or_def_accurate(inFuncHeaderptr,false))
       {
           symbolTable->openscope();
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
       symbolTable->closescope();
   }

   void Compiler::block4_func_funcheader_semi(funcheadertype* inFuncHeader)
   {
       njnr::S_TableEntry* found = symbolTable->lookupB(inFuncHeader->name);
       if(  found  == nullptr )
       {
           auto tempEntry =  symbolTable->createFunc( inFuncHeader->name,
                                                   inFuncHeader->returntype,
                                                   inFuncHeader->paramlist
                                                 );
           symbolTable->install(tempEntry);
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
         if(inParamdeflist == nullptr)
         {
            std::cout << "notification: parameters list is nullptr\n";
         }
         else
         {
            std::cout << "parameter count: " + std::to_string(inParamdeflist->size()) + "\n";
//            std::cout << "found parameters: " + inParamdeflist->toString();
         }
         retFuncHeader->paramlist  = inParamdeflist;
         /* FIXME: NEED TO REINCORPORATE THIS BACK IN. Somehow lists provide a type? where and why?
         if(inParamdeflist->gettype() == type::VOID)
         {
            retFuncHeader->ttype = type::VOID;
         }
         */
      }
      else
      {
        std::cerr << "error in new\n";
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
   Funcb* Compiler::create_and_return_a_fn_body_statement_element(Statement* stmt)
   {
       if(NULL != stmt)
       {
          if(stmt->getstype() == statement_type::RETURN)
          {
              std::cout << "found a return statement of type " << static_cast<int>(stmt->getrettype()) << std::endl;
              this->returnTypes.appendList(stmt->getrettype());
          }
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
   List* Compiler::getfinished(void)
   {
    return finished;
   }

   njnr::type Compiler::getReturnTypeFromStatement(Statement* stmt)
   {
      njnr::type retType{njnr::type::VOID};

      if(nullptr != stmt)
      {
         if(stmt->getexpr() != nullptr)
         {
            retType = stmt->getexpr()->gettype();
            if(njnr::type::IDENT == retType)
            {
                std::cout << "need to get data into symbol table so we can read it here and get this identifiers data type\n";
                retType = njnr::type::INT;
            }
         }
      }
      else
      {
        std::cerr << "NULL argument given\n";
      }

      return retType;
   }


}