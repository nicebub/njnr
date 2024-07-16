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
   ReturnPacket* Compiler::block60_function_call_ident_lpar_rpar(\
                                                      njnr::Identifier inIdent)
   {
       ReturnPacket* outPacket{new ReturnPacket{}};
       outPacket->setlval(false);
       Funcb* tempb;
       S_TableEntryX tempE;
       S_TableEntryX*tempE2;
       if ((tempb = reinterpret_cast<Funcb*>(symbolTable->
                                            lookup(inIdent.getvalue()))) ==
                                            nullptr)
       {
           error("function undeclared, please declare functions before " \
                 "using them", "");
       }
       else
       {
           tempE2 = new S_TableEntryX(*new std::string{inIdent.getvalue()},
                                     new njnr::Identifier{inIdent},
                                     njnr::type::IDENT);

           tempE = *static_cast<S_TableEntryX*>(symbolTable->
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
           delete tempE2;
           tempE2 = nullptr;
           return outPacket;
       }
       return outPacket;
   }

   ReturnPacket* Compiler::block62_func_call_with_params_name_and_params_rpar(\
                                                ReturnPacket** nameAndparamptr)
   {
       ReturnPacket* funcCallWparam{new ReturnPacket{}};
       funcCallWparam->setnumeric((* nameAndparamptr)->getnumeric());
       funcCallWparam->setlval(false);
       funcCallWparam->settype((* nameAndparamptr)->gettype());
       if ((* nameAndparamptr)->funcent != nullptr)
       {
           if ((static_cast<S_TableEntryX*>((*nameAndparamptr)->
                                            funcent))->
                                            getGroup() == btype::FUNC)
           {
               if ((reinterpret_cast<Funcb*>(
                               static_cast<S_TableEntryX*>((*nameAndparamptr)->
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
               static_cast<S_TableEntryX*>((*nameAndparamptr)->funcent)->
                                                               getName())
           {
               code_generator.gen_call("$scanf", (*nameAndparamptr)->params);
           }
           else if ("printf" ==
                    static_cast<S_TableEntryX*>((*nameAndparamptr)->
                                                funcent)->
                                                getName())
           {
               code_generator.gen_call("$printf", (*nameAndparamptr)->params);
           }
           else
           {
               if ((reinterpret_cast<Funcb*>(
                      static_cast<S_TableEntryX*>((*nameAndparamptr)->
                                                  funcent)->
                                                  getBinding()))->
                                                  getlabel() == 0)
               {
                   (reinterpret_cast<Funcb*>(
                       static_cast<S_TableEntryX*>((*nameAndparamptr)->
                                                   funcent)->
                                                   getBinding()))->
                                                   setlabel(
                                                    code_generator.getlabel());
               }
               code_generator.gen_call(
                        code_generator.genlabelw(
                            static_cast<S_TableEntryX*>((*nameAndparamptr)->
                                                        funcent)->getName(),
                            (reinterpret_cast<Funcb*>(
                                static_cast<S_TableEntryX*>((*nameAndparamptr)->
                                                            funcent)->
                                                            getBinding()))->
                                                            getlabel()),
                            (reinterpret_cast<Funcb*>(
                                static_cast<S_TableEntryX*>((*nameAndparamptr)->
                                                            funcent)->
                                                            getBinding()))->
                                                            getnum_param());
           }
       }
       return funcCallWparam;
   }

   ReturnPacket* Compiler::block63_name_and_params_ident_lpar_source(\
                                                      njnr::Identifier inPacket)
   {
       ReturnPacket* inEntry{new ReturnPacket{}};
       S_TableEntryX* s{new S_TableEntryX{}};
       inEntry->funcent = nullptr;
       *s = *static_cast<S_TableEntryX*>(symbolTable->
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
           static_cast<S_TableEntryX*>(inEntry->
                                       funcent)->setName(inPacket.getvalue());
       }
       return inEntry;
   }

   ReturnPacket* Compiler::block64_name_and_params_ident_lpar_source_expr(\
                                                   njnr::Identifier inIdent,
                                                   ReturnPacket** inEntryptr,
                                                   ReturnPacket** inPacketptr)
   {
       S_TableEntryX*tempE, *tempE2;
       ReturnPacket* outPacket{new ReturnPacket{}};
       ReturnPacket* inPacket{*inPacketptr};
       ReturnPacket* inEntry{*inEntryptr};
       outPacket->setlval(false);
       Funcb* tempB;
       tempB = reinterpret_cast<Funcb*>(symbolTable->
                                        lookup(inIdent.getvalue()));
       if (tempB == nullptr)
       {
           error("function undelcared, please declare " \
                 "functions before using them", "");
           error("1", "");
           outPacket->funcent = nullptr;
       }
       else
       {
        S_TableEntryX* s{new S_TableEntryX{}};
           // warning("just checking value of entry: \
           //                       %s",$<value.funcentvalue>$->name);
           tempE2 = new S_TableEntryX(*new std::string{inIdent.getvalue()},
                                     new njnr::Identifier{inIdent},
                                     njnr::type::IDENT);
           *s = *static_cast<S_TableEntryX*>(symbolTable->
                                             lookupB(inIdent.getvalue()));
           tempE = s;
           if ( tempE != nullptr)
           {
               if (tempE->getGroup() != btype::FUNC)
               {
                   error("function undeclared, please declare " \
                         "functions before using them", "");
                   error("2", "");
                   outPacket->funcent = nullptr;
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
           delete tempE2;
           tempE2 = nullptr;
       }
       return outPacket;
   }

   ReturnPacket* Compiler::block65_name_and_params_name_and_params_comma_expr(\
                                     ReturnPacket** innameAndparamPacketptr,
                                     ReturnPacket** inexprPacketptr)
   {
       ReturnPacket* outPacket{new ReturnPacket{}};
       ReturnPacket* innameAndparamPacket{*innameAndparamPacketptr};
       ReturnPacket* inexprPacket{*inexprPacketptr};

       S_TableEntryX*tempE, *tempE2;
       outPacket->setlval(false);
       Funcb* tempB;
       if (innameAndparamPacket->funcent == nullptr)
       {
           error("function undelcared, please declare functions " \
                 "before using them", "");
           error("3", "");
       }
       else
       {
           outPacket->funcent = innameAndparamPacket->funcent;
           tempE2 = new S_TableEntryX(*new std::string{
                          static_cast<S_TableEntryX*>(innameAndparamPacket->
                                                      funcent)->
                                                      getName()},
                                     innameAndparamPacket->funcent,
                                     njnr::type::IDENT);

           tempB = reinterpret_cast<Funcb*>(symbolTable->
                                           lookup(
                             static_cast<S_TableEntryX*>(innameAndparamPacket->
                                                         funcent)->
                                                         getName()));
           S_TableEntryX* s{new S_TableEntryX{}};
           *s = *static_cast<S_TableEntryX*>(symbolTable->
                                             lookupB(
                              static_cast<S_TableEntryX*>(innameAndparamPacket->
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
                       if (static_cast<S_TableEntryX*>(outPacket->funcent)->
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
           delete tempE2;
           tempE2 = nullptr;
       }
       return outPacket;
   }

}  // namespace njnr
