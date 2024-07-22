#include <config.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "debug.hpp"
#include "compiler.hpp"
#include "njnr.tab.hpp"
#include "symbol_table_stack.hpp"
#include "symbol_table_stackX.hpp"

using njnr::ReturnPacket;
using njnr::Compiler;
using njnr::Operator;
using njnr::reltype;
using njnr::Constant;
using njnr::S_TableEntryX;
using njnr::Identifier;
using njnr::btype;
using njnr::Varb;
using njnr::Paramb;
using njnr::List;

   std::shared_ptr<ReturnPacket> Compiler::block40_expr_equalexpr_equal_equalexpr(\
                         std::shared_ptr<ReturnPacket> inequalexprPacketptr,
                         std::shared_ptr<ReturnPacket> inotherequalexprPacketptr)
   {
      std::shared_ptr<ReturnPacket> outPacket{nullptr};
      std::shared_ptr<ReturnPacket> inequalexprPacket{inequalexprPacketptr};
      std::shared_ptr<ReturnPacket> inotherequalexprPacket{inotherequalexprPacketptr};

      if (!inequalexprPacket->getlval() )
      {
         error("Cannot make assignment. Left hand side is not a correct lval",
               "");
         return outPacket;
      }
   // else if( ! inotherequalexprPacket->getnumeric() )
   // {
   //    error("Cannot make assignment, Right hand side is not numeric.","");
   //    return outPacket;
   // }
       // conversion to integer not needed
       variableFetchWithNumericCheck(inotherequalexprPacket, false);

       if ( inequalexprPacket->gettype() == inotherequalexprPacket->gettype() )
       {
           outPacket = std::shared_ptr<ReturnPacket>(new ReturnPacket{true, inequalexprPacket->gettype(),
                                        true, 0});
           normalStore(inequalexprPacket->gettype());
       }
       else if (inequalexprPacket->gettype() == njnr::type::INT &&
               inotherequalexprPacket->gettype() == type::FLOAT)
       {
           variableStore(njnr::type::INT);
           outPacket = std::shared_ptr<ReturnPacket>(new ReturnPacket{true, njnr::type::INT, true, 0});
       }
       else if (inequalexprPacket->gettype() == njnr::type::FLOAT &&
               inotherequalexprPacket->gettype() == njnr::type::INT)
       {
           variableStore(njnr::type::FLOAT);
           outPacket = std::shared_ptr<ReturnPacket>(new ReturnPacket{true, njnr::type::FLOAT, true, 0});
       }
       return outPacket;
   }

   void Compiler::block42_equalexpr_relexpr_eqop_source(\
                                       std::shared_ptr<ReturnPacket> relexprPacketptr)
   {
       variableFetchWithNumericCheck(relexprPacketptr, false);
   }

   std::shared_ptr<ReturnPacket> Compiler::block43_equalexpr_relexpr_helper(\
                                                   njnr::reltype ineqop,
                                                   std::string need_letter_b)
   {
       warning("expressons are of different type, data may be lost", "");
       switch (ineqop)
       {
       case reltype::NEQ:
           break;
       case reltype::EQEQ:
           break;
       default:
           break;
       }

       return std::shared_ptr<ReturnPacket>(new ReturnPacket{false, njnr::type::INT, true, 0});
   }
   std::shared_ptr<ReturnPacket> Compiler::block43_equalexpr_relexpr_eqop_source_relexpr(\
                          Operator* ineqop, std::shared_ptr<ReturnPacket> relexprPacketptr,
                          std::shared_ptr<ReturnPacket> otherrelexprPacketptr)
   {
       std::shared_ptr<ReturnPacket> outPacket{new ReturnPacket{}};
       std::shared_ptr<ReturnPacket> relexprPacket{relexprPacketptr};
       std::shared_ptr<ReturnPacket> otherrelexprPacket{otherrelexprPacketptr};

       variableFetchWithNumericCheck(otherrelexprPacketptr, false);
       outPacket->setlval(false);
       if (relexprPacket->getnumeric() && otherrelexprPacket->getnumeric() )
       {
           outPacket->setnumeric(true);
           outPacket->settype(njnr::type::INT);
           if ( relexprPacket->gettype() == otherrelexprPacket->gettype() )
           {
               outPacket->settype(njnr::type::INT);
               /* FIXME(nicebub): broken */
               switch (reltype::NEQ)
               {
               case reltype::NEQ:
                   if (relexprPacket->gettype() == njnr::type::INT)
                   {}
                   else if (relexprPacket->gettype() == njnr::type::FLOAT)
                   {}
                   break;
               case reltype::EQEQ:
                   if (relexprPacket->gettype() == njnr::type::INT){}
                   else if (relexprPacket->gettype() == njnr::type::FLOAT)
                   {}
                   break;
               default:
                   break;
               }
           }
           else if (relexprPacket->gettype() == njnr::type::INT &&
                   otherrelexprPacket->gettype()== njnr::type::FLOAT)
           {
//               outPacket = block43_equalexpr_relexpr_helper(ineqop, "b");
           }
           else if (relexprPacket->gettype() == njnr::type::FLOAT &&
                   otherrelexprPacket->gettype() == njnr::type::INT)
           {
//               outPacket = block43_equalexpr_relexpr_helper(ineqop, "");
           }
       }
       else
       {
           error("non numeric in operation", "");
           // should be false right?
           outPacket->setnumeric(false);
       }
       return outPacket;
   }

   void Compiler::block45_relexpr_simpleexpr_relop_source(\
                                 std::shared_ptr<ReturnPacket> insimplePacketptr)
   {
       variableFetchWithNumericCheck(insimplePacketptr, false);
   }
   std::shared_ptr<ReturnPacket> Compiler::block46_relexpr_simpleexpr_relop_helper(\
                  njnr::reltype inrelop, std::string need_letter_b)
   {
       warning("expressons are of different type, data may be lost", "");

       switch (inrelop)
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
       return std::shared_ptr<ReturnPacket>(new ReturnPacket{false, njnr::type::INT, true, 0});
   }
   std::shared_ptr<ReturnPacket> Compiler::block46_relexpr_simpleexpr_relop_source_simpleexpr(\
                               std::shared_ptr<ReturnPacket> simpleexprPacketptr,
                               Operator* inrelop,
                               std::shared_ptr<ReturnPacket> othersimpleexprPacketptr)
   {
       std::shared_ptr<ReturnPacket> outPacket{new ReturnPacket{}};
       std::shared_ptr<ReturnPacket> simpleexprPacket{simpleexprPacketptr};
       std::shared_ptr<ReturnPacket> othersimpleexprPacket{othersimpleexprPacketptr};

       variableFetchWithNumericCheck(othersimpleexprPacketptr, false);
       outPacket->setlval(false);
       if (simpleexprPacket->getnumeric() &&
           othersimpleexprPacket->getnumeric() )
       {
           outPacket->setnumeric(true);
           outPacket->settype(njnr::type::INT);
           if (simpleexprPacket->gettype() ==
               othersimpleexprPacket->gettype() )
           {
               outPacket->settype(njnr::type::INT);
               /** FIXME(nicebub): broken */
               switch (reltype::LES)
               {
               case reltype::LES:
                   if (simpleexprPacket->gettype() == type::INT){}
                   else if (simpleexprPacket->gettype() == njnr::type::FLOAT)
                   {}
                   break;
               case reltype::LEQ:
                   if (simpleexprPacket->gettype() == type::INT){}
                   else if (simpleexprPacket->gettype() == njnr::type::FLOAT)
                   {}
                   break;
               case reltype::GRE:
                   if (simpleexprPacket->gettype() == type::INT){}
                   else if (simpleexprPacket->gettype() == njnr::type::FLOAT)
                   {}
                   break;
               case reltype::GEQ:
                   if (simpleexprPacket->gettype() == type::INT){}
                   else if (simpleexprPacket->gettype() == njnr::type::FLOAT)
                   {}
                   break;
               default:
                   break;
               }
           }
           else if (simpleexprPacket->gettype() == njnr::type::INT &&
                   othersimpleexprPacket->gettype() == njnr::type::FLOAT)
           {
//               outPacket = block46_relexpr_simpleexpr_relop_helper(inrelop,
//                                                                   "b");
           }
           else if (simpleexprPacket->gettype() == type::FLOAT &&
                   othersimpleexprPacket->gettype() == njnr::type::INT)
           {
//               outPacket = block46_relexpr_simpleexpr_relop_helper(\
//                             inrelop, "");
           }
       }
       else
       {
           error("non numeric in operation", "");
           outPacket->setnumeric(false);
       }
       return outPacket;
   }
   void Compiler::block48_simpleexpr_simpleexpr_addop_source(\
                                          std::shared_ptr<ReturnPacket> insimplePacketptr)
   {
       variableFetchWithNumericCheckAndLvalCheck(insimplePacketptr, false);
   }
   std::shared_ptr<ReturnPacket> Compiler::block49_simpleexpr_addop_helper(\
                                                  njnr::reltype inaddop,
                                                  std::string need_letter_b)
   {
       warning("expressons are of different type, data may be lost", "");
       switch (inaddop)
       {
       case reltype::PLS:
           break;
       case reltype::MIN:
           break;
       default:
           break;
       }
       return std::shared_ptr<ReturnPacket>(new ReturnPacket{false, njnr::type::FLOAT, true, 0});
   }

   std::shared_ptr<ReturnPacket> Compiler::block49_simpleexpr_simpleexpr_addop_source_term(\
                                  std::shared_ptr<ReturnPacket> simpleexprPacketptr,
                                  Operator* inaddop,
                                  std::shared_ptr<ReturnPacket> termPacketptr)
   {
       std::shared_ptr<ReturnPacket> outPacket{new ReturnPacket{}};
       std::shared_ptr<ReturnPacket> simpleexprPacket{simpleexprPacketptr};
       std::shared_ptr<ReturnPacket> termPacket{termPacketptr};

       variableFetchWithNumericCheck(termPacketptr, false);
       outPacket->setlval(false);
       if (simpleexprPacket->getnumeric() && termPacket->getnumeric())
       {
           outPacket->setnumeric(true);
           if ( simpleexprPacket->gettype() == termPacket->gettype() )
           {
               outPacket->settype(simpleexprPacket->gettype());
               /* FIXME(nicebub): broken */
               switch (reltype::PLS)
               {
               case reltype::PLS:
                   if (simpleexprPacket->gettype() == njnr::type::INT){}
                   else if (simpleexprPacket->gettype() == njnr::type::FLOAT)
                   {}
                   break;
               case reltype::MIN:
                   if (simpleexprPacket->gettype() == njnr::type::INT){}
                   else if (simpleexprPacket->gettype() == njnr::type::FLOAT)
                   {}
                   break;
               default:
                   break;
               }
           }
           else if (simpleexprPacket->gettype() == njnr::type::INT
                   && termPacket->gettype() == njnr::type::FLOAT)
           {
//               outPacket = block49_simpleexpr_addop_helper(inaddop, "b");
           }
           else if (simpleexprPacket->gettype() == njnr::type::FLOAT
                   && termPacket->gettype() == njnr::type::INT)
           {
//               outPacket = block49_simpleexpr_addop_helper(inaddop, "");
           }
       }
       else
       {
           error("non numeric in operation", "");
           outPacket->setnumeric(false);
       }
       return outPacket;
   }

   void Compiler::block51_term_term_mulop_source(std::shared_ptr<ReturnPacket> inPacketptr)
   {
       variableFetchWithNumericCheckAndLvalCheck(inPacketptr, false);
   }

   std::shared_ptr<ReturnPacket> Compiler::block52_term_mulop_helper(njnr::reltype inmulop,
                                                     std::string need_letter_b)
   {
       warning("expressons are of different type, data may be lost", "");
       switch (inmulop)
       {
       case reltype::DIV:
           break;
       case reltype::MULT:
           break;
       default:
           break;
       }
       return std::shared_ptr<ReturnPacket>(new ReturnPacket{false, njnr::type::FLOAT, true, 0});
   }
   std::shared_ptr<ReturnPacket> Compiler::block52_term_term_mulop_source_factor(\
                                     std::shared_ptr<ReturnPacket> intermPacketptr,
                                     Operator* inmulop,
                                     std::shared_ptr<ReturnPacket> infactorPacketptr)
   {
       std::shared_ptr<ReturnPacket> outtermPacket{new ReturnPacket{}};
       std::shared_ptr<ReturnPacket> intermPacket{intermPacketptr};
       std::shared_ptr<ReturnPacket> infactorPacket{infactorPacketptr};
       variableFetchWithNumericCheck(infactorPacketptr, false);
       outtermPacket->setlval(false);
       if (intermPacket->getnumeric() && infactorPacket->getnumeric())
       {
           outtermPacket->setnumeric(true);
           if (intermPacket->gettype() == infactorPacket->gettype() )
           {
               outtermPacket->settype(intermPacket->gettype());
               /* FIXME(nicebub): broken */
               switch (reltype::DIV)
               {
               case reltype::DIV:
                   if (intermPacket->gettype()== njnr::type::INT)
                   {
                   }
                   else if (intermPacket->gettype()== njnr::type::FLOAT)
                   {
                   }
                   break;
               case reltype::MULT:
                   if (intermPacket->gettype()== njnr::type::INT)
                   {
                   }
                   else if (intermPacket->gettype()== njnr::type::FLOAT)
                   {
                   }
                   break;
               default:
                   break;
               }
           }
           else if (intermPacket->gettype() == njnr::type::INT
                   && infactorPacket->gettype()== njnr::type::FLOAT)
           {
//               outtermPacket = block52_term_mulop_helper(inmulop, "b");
           }
           else if (intermPacket->gettype() == njnr::type::FLOAT &&
                    infactorPacket->gettype() == njnr::type::INT)
           {
//               outtermPacket =  block52_term_mulop_helper(inmulop, "");
           }
       }
       else
       {
           error("non numeric in operation", "");
           outtermPacket->setnumeric(false);
       }
       return outtermPacket;
   }

   std::shared_ptr<ReturnPacket> Compiler::block54_factor_constant(std::shared_ptr<Constant> inConstant)
   {
      return static_pointer_cast<ReturnPacket>(inConstant);
   }

   std::shared_ptr<ReturnPacket> Compiler::block55_factor_ident(njnr::Identifier inIdent)
   {
      std::shared_ptr<ReturnPacket>  outPacket{nullptr};
      std::shared_ptr<S_TableEntryX> resultLookup{nullptr};
      bool gen_code = false;
//      int  gen_type = 0;

      outPacket = std::shared_ptr<Identifier>(new Identifier{inIdent});
      if (true == gen_code)
      {
         if (inIdent.getvalue() != "main")
         {
           #ifdef DEBUG
            //  fprintf(stderr,"the name of the identifier here is:  %s\n",
            //     (char*)$<value.svalue>1);
           #endif
            std::shared_ptr<S_TableEntryX> s{new S_TableEntryX{}};
            *s = *static_pointer_cast<S_TableEntryX>(symbolTable->
                                              lookupB(inIdent.getvalue()));
            resultLookup = s;
            if (nullptr != resultLookup)
            {
               outPacket->settype((static_pointer_cast<S_TableEntryX>(resultLookup->
                                                   getBinding()))->getType());
               outPacket->setlval(true);
               if (outPacket->gettype() == njnr::type::INT |
                  outPacket->gettype() == njnr::type::FLOAT)
               {
                  outPacket->setnumeric(true);
               }
               if (symbolTable->inCurrentScope(inIdent.getvalue()))
               {
               }
               else
               {
                  switch (resultLookup->getGroup())
                  {
                     case btype::VAR:
                     {
                       #ifdef DEBUG
                        // char temp_char = (char)(*outPacket)->gettype();
                        // if((*outPacket)->gettype() !=  nullptr)
                        //   fprintf(stderr,"type is: %s\n", &temp_char);
                        // if(resultLookup->getBinding()->gettype() !=
                        //     nullptr) fprintf(stderr,"type is: %d\n",
                        //                    resultLookup->getBinding()->gettype());
                       #endif
                        int level_diff {symbolTable->
                                        getleveldif(inIdent.getvalue())};
                        if (level_diff != -1)
                        {
                        }
                        else
                        {
                           debugprint(
                              "error, somehow level difference was -1\n",
                              "");
                        }
                        break;
                     }

                     case btype::PARAM:
                       #ifdef DEBUG
                        std::cerr << "type is: " <<
                                     static_cast<int>(outPacket->gettype()) <<
                                     std::endl;
                       #endif
                        break;

                     default:
                        error("Variable is unknown or undelcared", "");
                        break;
                  }
               }
            }
            else
            {
               outPacket->settype(type::VOID);
               error("Variable is unknown or undelcared, " \
                     "couldn't be found in symbol table'", "");
            }
         }
         else
         {
            error("Main is not a variable name", "");
         }
      }
      return outPacket;
   }

   std::shared_ptr<ReturnPacket> Compiler::block57_factor_addop_factor_uminus(\
                                        Operator* inop,
                                        std::shared_ptr<ReturnPacket> inPacketptr)
   {
       std::shared_ptr<ReturnPacket> outPacket{new ReturnPacket{}};
       std::shared_ptr<ReturnPacket> inPacket{inPacketptr};
       if (inPacket->getnumeric())
       {
           /* FIXME(nicebub): broken */
           switch (njnr::reltype::MIN)
           {
           case njnr::reltype::MIN:
               variableFetchWithNumericCheck(inPacketptr, false);
               switch (inPacket->gettype())
               {
               case type::INT:
                   break;
               case type::FLOAT:
                   break;
               default:
                   break;
               }
               break;
           case njnr::reltype::PLS:
               variableFetchWithNumericCheck(inPacketptr, false);
               break;
           default:
               break;
           }
       }
       outPacket->setlval(false);
       outPacket->settype(inPacket->gettype() );
       if (inPacket->getnumeric())
       {
           outPacket->setnumeric(true);
       }
       else
       {
           error("cannot change sign of non numeric expression", "");
       }
       return outPacket;
   }

   std::shared_ptr<ReturnPacket> Compiler::block58_factor_adof_ident(njnr::Identifier inPacket)
   {
       std::shared_ptr<ReturnPacket> outPacket{new ReturnPacket{}};
       std::shared_ptr<S_TableEntryX> tempE;  // , *tempE2;
       if (inPacket.getvalue() != "main")
       {
           if (symbolTable->lookup(inPacket.getvalue()) == nullptr)
               error("variable undeclared, " \
                     "please declare variables before using them", "");
           else
           {
            std::shared_ptr<S_TableEntryX> s{new S_TableEntryX{}};
            *s = *static_pointer_cast<S_TableEntryX>(symbolTable->
                                               lookupB(inPacket.getvalue()));
               tempE = s;
               if (tempE != nullptr)
               {
                   if (tempE->getGroup() == btype::VAR ||
                       tempE->getGroup() == btype::PARAM)
                   {
                       switch (tempE->getGroup())
                       {
                       case btype::VAR:
                           outPacket->
                               settype((static_pointer_cast<Varb>((tempE->
                                                           getBinding())))->
                                                           gettype());
   #ifdef DEBUG
   //  std::cerr << "type is: "  << (int)outPacket->gettype()) << std::endl;
   #endif
                           outPacket->setlval(false);
                           if ((reinterpret_pointer_cast<Varb>(tempE->getBinding()))->
                                                      gettype() == type::INT ||
                               (reinterpret_pointer_cast<Varb>(tempE->getBinding()))->
                                                      gettype() == type::FLOAT)
                               outPacket->setnumeric(true);
                           if (symbolTable->inCurrentScope(inPacket.getvalue()))
                           {
                           }
                           else
                           {
                               int level_diff{symbolTable->
                                              getleveldif(inPacket.getvalue())};
                               if (level_diff != -1)
                               {
                               }
                               else
                               {
                                   debugprint("error level differince was -1\n",
                                              "");
                               }
                               // do something else
                           }
                           break;
                       case btype::PARAM:
                           outPacket->settype((reinterpret_pointer_cast<Paramb>(tempE->
                                                   getBinding()))->gettype());
   #ifdef DEBUG
   //  std::cerr <<  "type is: " <<  (int)outPacket->gettype()) << std::endl;
   #endif
                           outPacket->setlval(false);
                           if ((reinterpret_pointer_cast<Paramb>(tempE->
                                                      getBinding()))->
                                                      gettype() == type::INT ||
                               (reinterpret_pointer_cast<Paramb>(tempE->
                                                       getBinding()))->
                                                       gettype() == type::FLOAT)
                               outPacket->setnumeric(true);
                           if (symbolTable->inCurrentScope(inPacket.getvalue()))
                           {
                           }
                           else
                           {
                               // do something else
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
                   error("Variable is unknown or undelcared", "");
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


   std::shared_ptr<List> Compiler::block69_identlist_ident(njnr::Identifier inIdent)
   {
       return List::mklist(std::shared_ptr<Identifier>(new Identifier{inIdent}));
   }

   std::shared_ptr<List> Compiler::block70_identlist_comma_ident(std::shared_ptr<List> inIdentListptr,
                                                 njnr::Identifier inIdent)
   {
       return std::shared_ptr<List>((inIdentListptr)->appendList(std::shared_ptr<Identifier>(new Identifier{inIdent})));
   }
