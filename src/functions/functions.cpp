#include <config.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <memory>

#include "debug.hpp"
#include "Statement.hpp"
#include "Compiler.hpp"
#include "njnr.tab.hpp"
#include "symbol_table_stack.hpp"
#include "symbol_table_stackX.hpp"

namespace njnr
{
   std::shared_ptr<FunctionBinding> Compiler::create_full_function(std::shared_ptr<FunctionHeader> funcheader,
                                         std::shared_ptr<List> funcbody)
   {
    /**
     *    FunctionHeader
     *      std::string   name;       // fn name
      std::shared_ptr<njnr::List>   paramlist;  // list of parameters the fn accept as input
      njnr::type    returntype; // return type(if any) of fn
      njnr::type    ttype;      // type of fn?(TBD)

     * 
     */
    //   std::shared_ptr<FunctionBinding> out{nullptr};
    //   out = new FunctionBinding{};
      std::shared_ptr<FunctionBinding> out(new FunctionBinding());
      if (nullptr != out)
      {
         out->setfuncbody_list(funcbody);
         if (nullptr != funcheader)
         {
            out->setfuncheader(funcheader);
            out->setreturntype(funcheader->returntype);
         }
      }
      checkfunctionReturnValues(out);
      return out;
   }

   void Compiler::block2_func_funcheader_source(\
                                 std::shared_ptr<FunctionHeader> inFuncHeaderptr)
   {
       auto templabel{mainlabel};
       if (is_function_decl_or_def_accurate(inFuncHeaderptr, false))
       {
           symbolTable->openscope();
           if ((inFuncHeaderptr)->name != "main")
           {
               templabel = currentFunc->getlabel();
               install_parameters_into_symbol_table_curren_scope(\
                                                       inFuncHeaderptr);
           }
           code_generator.gen_label(code_generator.
                                    genlabelw((inFuncHeaderptr)->
                                    name,
                                    templabel));
       }
   }
   void Compiler::block3_func_funcheader_source_funcbody()
   {
       symbolTable->closescope();
   }

   void Compiler::block4_func_funcheader_semi(std::shared_ptr<FunctionHeader> inFuncHeader)
   {
       njnr::S_TableEntryX found = *static_pointer_cast<S_TableEntryX>(symbolTable->
                                                         lookupB(inFuncHeader->
                                                                 name));
           auto tempEntry =  symbolTable->createFunc(inFuncHeader->name,
                                                     inFuncHeader->returntype,
                                                     inFuncHeader->paramlist);
           symbolTable->install(tempEntry);
       is_function_decl_or_def_accurate(inFuncHeader, true);
   }

   void Compiler::block5_funcheader_error_semi(std::shared_ptr<FunctionHeader> inFuncHeaderptr)
   {
    /*
       std::shared_ptr<FunctionHeader> inFuncHeader{inFuncHeaderptr};
       if (inFuncHeader != nullptr)
       {
           inFuncHeader = nullptr;
       }
       */
   }

   std::shared_ptr<FunctionHeader>  Compiler::
                    funcheader_returntype_ident_lpar_paramdef_rpar_helper(\
                                                   std::string inIdent_original,
                                                   std::shared_ptr<List> inParamdeflist = nullptr,
                                                   njnr::type inreturntype = njnr::type::VOID)
   {
      njnr::Identifier inIdent{inIdent_original};
      std::shared_ptr<FunctionHeader> retFuncHeader{nullptr};

      retFuncHeader             = std::shared_ptr<FunctionHeader>(new FunctionHeader{});
      if (nullptr != retFuncHeader)
      {
         retFuncHeader->returntype = inreturntype;
         retFuncHeader->name       = inIdent.getName();
         if (inParamdeflist == nullptr)
         {
            report(njnr::logType::info, "-INFO--> parameters list is nullptr");
         }
         else
         {
            std::cout << "parameter count: " +
                         std::to_string(inParamdeflist->size()) +
                         "\n";
//            std::cout << "found parameters: " + inParamdeflist->toString();
         }

         retFuncHeader->paramlist = nullptr;

         if (inParamdeflist)
         {
            retFuncHeader->paramlist  = inParamdeflist;
         }
         /* FIXME: NEED TO REINCORPORATE THIS BACK IN. Somehow lists provide a type? where and why?
         if(inParamdeflist->gettype() == type::VOID)
         {
            retFuncHeader->ttype = type::VOID;
         }
         */
      }
      else
      {
        report(njnr::logType::error, "error in new");
      }
      return retFuncHeader;
   }
   void Compiler::block25_funcbody_lcbra_decls_source()
   {
//       auto temp{mainlocal};
       if (currentFunc->getName() == "main")
       {
           mainlocal = offset_counter-5;
//           temp = mainlocal;
       }
       else
       {
           switch (currentFunc->getparam_type()[0])
           {
           case njnr::type::VOID:
               currentFunc->setlocalcount(offset_counter - 5);
               break;
           default:
               currentFunc->setlocalcount(offset_counter - 5 -
                                          currentFunc->getnum_param());
              break;
          }
//          temp = currentFunc->getlocalcount();
      }
  }
   std::shared_ptr<FunctionBinding> Compiler::create_and_return_a_fn_body_statement_element(\
                                                       std::shared_ptr<Statement> stmt)
   {
       if (NULL != stmt)
       {
          if (stmt->getstype() == statement_type::RETURN)
          {
              std::cout << "found a return statement of type " <<
                           static_cast<int>(stmt->getrettype()) <<
                           std::endl;
              this->returnTypes.appendList(stmt->getrettype());
          }
       }

      return nullptr;
   }
   std::shared_ptr<FunctionBinding> Compiler::add_statement_to_fn_body_and_return(std::shared_ptr<List> func,
                                                        std::shared_ptr<Statement> stmt)
   {
       if (stmt->getstype() == statement_type::RETURN)
       {
           std::cout << "attaching found a return statement of type " <<
                        static_cast<int>(stmt->getrettype()) <<
                        std::endl;
           this->returnTypes.appendList(stmt->getrettype());
       }

      return nullptr;
   }
   std::shared_ptr<List> Compiler::getfinished(void)
   {
    return finished;
   }

   njnr::type Compiler::getReturnTypeFromStatement(std::shared_ptr<Statement> stmt)
   {
      njnr::type retType{njnr::type::VOID};

      if (nullptr != stmt)
      {
         if (stmt->getexpr() != nullptr)
         {
            retType = stmt->getexpr()->gettype();
            if (njnr::type::IDENT == retType)
            {
                report(njnr::logType::debug, "need to get data into symbol table "\
                             "so we can read " \
                             "it here and get this identifiers data type");
                retType = njnr::type::INT;
            }
         }
      }
      else
      {
        report(njnr::logType::debug, "NULL argument given");
      }

      return retType;
   }


}  // namespace njnr
