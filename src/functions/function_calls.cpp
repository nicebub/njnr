#include <config.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "debug.hpp"
#include "compiler.hpp"
#include "njnr.tab.hpp"
#include "symbol_table_stack.hpp"
#include "symbol_table_stackX.hpp"

namespace njnr
{
   std::shared_ptr<ReturnPacket> Compiler::block60_function_call_ident_lpar_rpar(\
                                                      njnr::Identifier inIdent)
   {
       std::shared_ptr<ReturnPacket> outPacket{new ReturnPacket{}};
       outPacket->setlval(false);
       std::shared_ptr<Funcb> tempb;
       S_TableEntryX tempE;
       std::shared_ptr<S_TableEntryX> tempE2;
       if ((tempb = reinterpret_pointer_cast<Funcb>(symbolTable->
                                            lookup(inIdent.getvalue()))) ==
                                            nullptr)
       {
           error("function undeclared, please declare functions before " \
                 "using them", "");
       }
       else
       {
           tempE2 = std::shared_ptr<S_TableEntryX>(new S_TableEntryX(*new std::string{inIdent.getvalue()},
                                     std::shared_ptr<Identifier>(new njnr::Identifier{inIdent}),
                                     njnr::type::IDENT));

           tempE = *static_pointer_cast<S_TableEntryX>(symbolTable->
                                                lookupB(inIdent.getvalue()));
               if (tempE.getGroup() == btype::FUNC)
               {
                   if (tempb->getreturntype() != type::VOID)
                   {
                       outPacket->setlval(true);
                   }
                   else
                   {
                       outPacket->setlval(false);
                   }
                   if (tempb->getnum_param() > 1 )
                   {
                       error("Function takes no parameters, only void in the " \
                             "declaration and definition", "");
                   }
                   if (tempb->getnum_param() == 1)
                   {
                       if (tempb->getparam_type()[0] != njnr::type::VOID)
                       {
                           error("Function takes no parameters, only void in " \
                                 "the declaration and definition", "");
                       }
                   }
                   outPacket->settype(tempb->getreturntype());
                   if (outPacket->gettype() == type::INT ||
                       outPacket->gettype() == type::FLOAT)
                   {
                       outPacket->setnumeric(true);
                   }
                   else
                   {
                       outPacket->setnumeric(false);
                   }
                   code_generator.gen_call(code_generator.genlabelw(
                                           inIdent.getvalue(),
                                           tempb->getlabel()), 0);
               }
               else
               {
                   error("Function call with an unknown function name", "");
               }
//           tempE2 = nullptr;
           return outPacket;
       }
       return outPacket;
   }

   std::shared_ptr<ReturnPacket> Compiler::block62_func_call_with_params_name_and_params_rpar(\
                                                std::shared_ptr<ReturnPacket>* nameAndparamptr)
   {
       std::shared_ptr<ReturnPacket> funcCallWparam{new ReturnPacket{}};
       funcCallWparam->setnumeric((* nameAndparamptr)->getnumeric());
       funcCallWparam->setlval(false);
       funcCallWparam->settype((* nameAndparamptr)->gettype());
       if ((* nameAndparamptr)->funcent != nullptr)
       {
           if ((static_pointer_cast<S_TableEntryX>((*nameAndparamptr)->
                                            funcent))->
                                            getGroup() == btype::FUNC)
           {
               if ((reinterpret_pointer_cast<Funcb>(
                               static_pointer_cast<S_TableEntryX>((*nameAndparamptr)->
                                            funcent)->
                                            getBinding()))->
                                            getreturntype() != type::VOID)
               {funcCallWparam->setnumeric(true);
               }
               else
               {
                   funcCallWparam->setnumeric(false);
               }
           }
           if ("scanf" ==
               static_pointer_cast<S_TableEntryX>((*nameAndparamptr)->funcent)->
                                                               getName())
           {
               code_generator.gen_call("$scanf", (*nameAndparamptr)->params);
           }
           else if ("printf" ==
                    static_pointer_cast<S_TableEntryX>((*nameAndparamptr)->
                                                funcent)->
                                                getName())
           {
               code_generator.gen_call("$printf", (*nameAndparamptr)->params);
           }
           else
           {
               if ((reinterpret_pointer_cast<Funcb>(
                      static_pointer_cast<S_TableEntryX>((*nameAndparamptr)->
                                                  funcent)->
                                                  getBinding()))->
                                                  getlabel() == 0)
               {
                   (reinterpret_pointer_cast<Funcb>(
                       static_pointer_cast<S_TableEntryX>((*nameAndparamptr)->
                                                   funcent)->
                                                   getBinding()))->
                                                   setlabel(
                                                    code_generator.getlabel());
               }
               code_generator.gen_call(
                        code_generator.genlabelw(
                            static_pointer_cast<S_TableEntryX>((*nameAndparamptr)->
                                                        funcent)->getName(),
                            (reinterpret_pointer_cast<Funcb>(
                                static_pointer_cast<S_TableEntryX>((*nameAndparamptr)->
                                                            funcent)->
                                                            getBinding()))->
                                                            getlabel()),
                            (reinterpret_pointer_cast<Funcb>(
                                static_pointer_cast<S_TableEntryX>((*nameAndparamptr)->
                                                            funcent)->
                                                            getBinding()))->
                                                            getnum_param());
           }
       }
       return funcCallWparam;
   }

   std::shared_ptr<ReturnPacket> Compiler::block63_name_and_params_ident_lpar_source(\
                                                      njnr::Identifier inPacket)
   {
       std::shared_ptr<ReturnPacket> inEntry{new ReturnPacket{}};
       std::shared_ptr<S_TableEntryX> s{new S_TableEntryX{}};
//       inEntry->funcent = nullptr;
       *s = *static_pointer_cast<S_TableEntryX>(symbolTable->
                                         lookupB(inPacket.getvalue()));
       inEntry->funcent = s;
   #ifdef DEBUG
       //  printTree(symbolTable);
   //  std::cerr <<  "this the name of function called and the " \
   //                "lookup value: "  <<
   //                inPacket.getvalue().c_str()) << std::endl;
       if ( symbolTable->lookupB(inPacket.getvalue()) == nullptr)
           std::cerr <<  "it was null\n";
       else
           std::cerr << "wasn't null\n";
   #endif
       if (inEntry->funcent != nullptr)
       {
           static_pointer_cast<S_TableEntryX>(inEntry->
                                       funcent)->setName(inPacket.getvalue());
       }
       return inEntry;
   }

   std::shared_ptr<ReturnPacket> Compiler::block64_name_and_params_ident_lpar_source_expr(\
                                                   njnr::Identifier inIdent,
                                                   std::shared_ptr<ReturnPacket>* inEntryptr,
                                                   std::shared_ptr<ReturnPacket>* inPacketptr)
   {
       std::shared_ptr<S_TableEntryX> tempE;
       std::shared_ptr<S_TableEntryX> tempE2;
       std::shared_ptr<ReturnPacket> outPacket{new ReturnPacket{}};
       std::shared_ptr<ReturnPacket> inPacket{*inPacketptr};
       std::shared_ptr<ReturnPacket> inEntry{*inEntryptr};
       outPacket->setlval(false);
       std::shared_ptr<Funcb> tempB;
       tempB = reinterpret_pointer_cast<Funcb>(symbolTable->
                                        lookup(inIdent.getvalue()));
       if (tempB == nullptr)
       {
           error("function undelcared, please declare " \
                 "functions before using them", "");
           error("1", "");
//           outPacket->funcent = nullptr;
       }
       else
       {
        std::shared_ptr<S_TableEntryX> s{new S_TableEntryX{}};
           // warning("just checking value of entry: \
           //                       %s",$<value.funcentvalue>$->name);
           tempE2 = std::shared_ptr<S_TableEntryX>(new S_TableEntryX(*new std::string{inIdent.getvalue()},
                                     std::shared_ptr<Identifier>(new njnr::Identifier{inIdent}),
                                     njnr::type::IDENT));
           *s = *static_pointer_cast<S_TableEntryX>(symbolTable->
                                             lookupB(inIdent.getvalue()));
           tempE = s;
           if ( tempE != nullptr)
           {
               if (tempE->getGroup() != btype::FUNC)
               {
                   error("function undeclared, please declare " \
                         "functions before using them", "");
                   error("2", "");
//                   outPacket->funcent = nullptr;
               }
               else
               {
                   if (tempB->getnum_param() == 0)
                   {
                       error("Paramter given for a function " \
                             "that takes no parameters.", "");
                   }
                   else if (tempB->getnum_param() == -1)
                   {
   #ifdef DEBUG
   //  fprintf(stderr,"SPRINTF OR PRINTF mismatch: FUNCTION NAME: %s\n",$1);
                       //  fprintf(stderr,"SPRINTF OR PRINTF: FUNCTION TYPE: " \
                       //                  "%d\n",(int)$4->type);
   //  fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
   //  fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
   //  fprintf(stderr,"SPRINTF OR PRINTF: $4 TYPE: %d\n",(int)$4->type);
   //  fprintf(stderr,"SPRINTF OR PRINTF: tempB->param_type[0] TYPE: %d\n"," \
   //                                           "(int)tempB->param_type[0]);
   #endif
                       if (inPacket->gettype() != tempB->getparam_type()[0])
                       {
                           error("parameter type is different in declaration " \
                                 "and in function call", "");
                       }
                       else
                       {
   //  code_generator.gen_instr_S("pushs",$<value.svalue>4);
                       }
                       outPacket->settype(tempB->getparam_type()[0]);
                       if (outPacket->gettype() == type::INT ||
                           outPacket->gettype() == type::FLOAT)
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
                       variableFetchWithNumericCheck(inPacket, false);

                       if ( !tempB->getparam_type().empty())
                       {
                           if (inPacket->gettype() != tempB->getparam_type()[0])
                           {
   #ifdef DEBUG
   //  fprintf(stderr,"Function mismatch 2: FUNCTION NAME: %s\n",$1);
   //  fprintf(stderr,"Function mismatch 2: FUNCTION TYPE: %d\n",(int)$4->type);
   //  fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
   //  fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
   #endif
                               if (tempB->getparam_type()[0] != type::INT &&
                                   tempB->getparam_type()[0] != type::FLOAT)
                                  error("Parameter type is different in " \
                                        "declaration and in function call", "");
                               else if (tempB->getparam_type()[0] == type::INT)
                               {
   #ifdef DEBUG
   //  fprintf(stderr,"Function mismatch 3: FUNCTION NAME: %s\n",$1);
   //  fprintf(stderr,"Function mismatch 3: FUNCTION TYPE: %d\n",(int)$4->type);
   //  fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
   //  fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
   #endif
                                   switch (inPacket->gettype())
                                   {
                                   case type::FLOAT:
                                 warning("Paramter expression will lose " \
                                         "data because of different type", "");
                                       break;
                                   case type::INT:
                                       break;
                                   default:
                                     error("Parameter type is different in " \
                                           "declaration and function call", "");
                                     break;
                                   }
                               }
                             else if (tempB->getparam_type()[0] == type::FLOAT)
                               {
   #ifdef DEBUG
   //  fprintf(stderr,"Function mismatch 4: FUNCTION NAME: %s\n",$1);
   #endif
                                   switch (inPacket->gettype())
                                   {
                                   case type::INT:
                                       warning("Parameter expression is " \
                                               "different type than in " \
                                               "declaration", "");
                                       break;
                                   case type::FLOAT:
                                       break;
                                   default:
                                       error("Parameter type is different " \
                                             "in declaration and function " \
                                             "call", "");
                                       break;
                                   }
                               }
                           }
                       }
                       outPacket->funcent = inEntry->funcent;
                       if (!tempB->getparam_type().empty())
                           outPacket->settype(tempB->getparam_type()[0]);
                       if (outPacket->gettype() == type::INT ||
                           outPacket->gettype() == type::FLOAT)
                           outPacket->setnumeric(true);
                       else
                           outPacket->setnumeric(false);
                       outPacket->params = 1;
                   }
               }
           }
           else
           {
               error("Function is undeclared", "");
           }
//           tempE2 = nullptr;
       }
       return outPacket;
   }

   std::shared_ptr<ReturnPacket> Compiler::block65_name_and_params_name_and_params_comma_expr(\
                                     std::shared_ptr<ReturnPacket>* innameAndparamPacketptr,
                                     std::shared_ptr<ReturnPacket>* inexprPacketptr)
   {
       std::shared_ptr<ReturnPacket> outPacket{new ReturnPacket{}};
       std::shared_ptr<ReturnPacket> innameAndparamPacket{*innameAndparamPacketptr};
       std::shared_ptr<ReturnPacket> inexprPacket{*inexprPacketptr};

       std::shared_ptr<S_TableEntryX> tempE;
       std::shared_ptr<S_TableEntryX> tempE2;
       outPacket->setlval(false);
       std::shared_ptr<Funcb> tempB;
       if (innameAndparamPacket->funcent == nullptr)
       {
           error("function undelcared, please declare functions " \
                 "before using them", "");
           error("3", "");
       }
       else
       {
           outPacket->funcent = innameAndparamPacket->funcent;
           tempE2 = std::shared_ptr<S_TableEntryX>(new S_TableEntryX(*new std::string{
                          static_pointer_cast<S_TableEntryX>(innameAndparamPacket->
                                                      funcent)->
                                                      getName()},
                                     innameAndparamPacket->funcent,
                                     njnr::type::IDENT));

           tempB = reinterpret_pointer_cast<Funcb>(symbolTable->
                                           lookup(
                             static_pointer_cast<S_TableEntryX>(innameAndparamPacket->
                                                         funcent)->
                                                         getName()));
           std::shared_ptr<S_TableEntryX> s{new S_TableEntryX{}};
           *s = *static_pointer_cast<S_TableEntryX>(symbolTable->
                                             lookupB(
                              static_pointer_cast<S_TableEntryX>(innameAndparamPacket->
                                                          funcent)->
                                                          getName()));
           tempE = s;
           if (tempE  !=nullptr)
           {
               if (tempE->getGroup() != btype::FUNC)
               {
                   error("function undeclared, please declare " \
                         "functions before using them", "");
                   error("4", "");
               }
               else
               {
                   if (tempB->getnum_param() ==0)
                   {
                   }
                   else if (tempB->getnum_param() == -1)
                   {
                       outPacket->settype(tempB->
                                getparam_type()[innameAndparamPacket->params]);
                       if (outPacket->gettype() == type::INT ||
                           outPacket->gettype() == type::FLOAT)
                       {
                           outPacket->setnumeric(true);
                       }
                       else
                       {
                           outPacket->setnumeric(false);
                       }
                       outPacket->params = innameAndparamPacket->params +1;
                       outPacket->funcent = innameAndparamPacket->funcent;
                       if (static_pointer_cast<S_TableEntryX>(outPacket->funcent)->
                                                                  getName() !=
                           "scanf")
                       {
                           variableFetchWithNumericCheck(inexprPacket, false);
                       }
                   }
                   else if (innameAndparamPacket->params < tempB->
                                                           getnum_param())
                   {
                       if (inexprPacket->gettype() !=
                           tempB->getparam_type()[innameAndparamPacket->params])
                       {
   #ifdef DEBUG
   //  fprintf(stderr,"Function mismatch before warning: FUNCTION NAME:" \
   //                   " %s\n", innameAndparamPacket->getname());
   #endif

                           warning("Parameter type is different in " \
                                   "declaration and in function call", "");
                           variableFetch(inexprPacket, false);
                           if (tempB->getparam_type()[innameAndparamPacket->
                                                      params] ==
                               type::FLOAT) {;}
                           else if (tempB->
                                    getparam_type()[innameAndparamPacket->
                                    params ]==
                                    type::INT) {;}
                       }
                       else
                       {
                           variableFetch(inexprPacket, false);
                       }
                       outPacket->settype(tempB->
                                         getparam_type()[innameAndparamPacket->
                                         params]);
                       if (outPacket->gettype() == type::INT ||
                           outPacket->gettype() == type::FLOAT)
                           outPacket->setnumeric(true);
                       else
                           outPacket->setnumeric(false);
                       outPacket->params = innameAndparamPacket->params +1;
                       outPacket->funcent = innameAndparamPacket->funcent;
                   }
                   else
                   {
                       error("Too many parameters given for " \
                             "function in function call.", "");
                   }
               }
           }
           else
           {
               error("Function is undeclared", "");
           }
//           tempE2 = nullptr;
       }
       return outPacket;
   }

   /**
    * @brief
    *
    * @param t
    * @return std::string
    */
   std::string Compiler::mapNjnrTypeToString(njnr::type t)
   {
      std::string s{""};
      switch (t)
      {
         case njnr::type::STR:
            s = "string";
            break;
         case njnr::type::INT:
            s = "int";
            break;
         case njnr::type::FLOAT:
            s = "float";
            break;
         case njnr::type::CHAR:
            s = "char";
            break;
        default:
            break;
      }
      return s;
   }

   /**
    * @brief
    *
    * @param p
    * @param s
    * @return Operator*
    */
   Operator* Compiler::createOperator(njnr::reltype p,
                                      std::string s)
   {
      Operator* n{new Operator(nullptr)};

      n->setType(TSOperatorType(s));

      typeTable->install2(s, njnr::type::OPERATOR);
      return n;
   }

   /**
    * @brief
    *
    * @param p
    * @param t
    * @return std::shared_ptr<Constant>
    */
   std::shared_ptr<Constant> Compiler::createConstant(njnr::type p,
                                      std::string t)
   {
      std::string s{mapNjnrTypeToString(p)};

      typeTable->install2(s, p);

      std::shared_ptr<Constant> n{new Constant{t, p}};
      constantTable->install2(t, p);

//      n->setType(TSOperatorType(s));
//      typeTable->install2(s, njnr::type::OPERATOR);
      return n;
   }
}  // namespace njnr
