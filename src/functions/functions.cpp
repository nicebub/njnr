#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "debug.hpp"
#include "compiler.hpp"
#include "njnr.tab.hpp"

using namespace njnr;
namespace njnr
{
   Funcb* Compiler::create_full_function(funcheadertype* funcheader, List* funcbody)
   {
      Funcb* out{nullptr};
      out = new Funcb{};
      out->setreturntype(funcheader->returntype);

      return out;
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
   
}