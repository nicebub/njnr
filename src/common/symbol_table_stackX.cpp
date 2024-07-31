#include <config.h>
#include <map>
#include <deque>
#include <string>

#include "List.hpp"
#include "ListNode.hpp"
#include "ParameterListNode.hpp"
#include "type.hpp"                 // for njnr::type
#include "symbol_table_entry.hpp"   // for class S_TableEntry
#include "symbol_table.hpp"         // for class Table
#include "symbol_table_stackX.hpp"  // for class SymbolTableX
#include "Compiler.hpp"             // for njnr::report()
#include "Operator.hpp"             // for TSOperatorType()
using njnr::SymbolTableX;

void SymbolTableX::install2(std::string val, njnr::type t)
{
   installHelper(val, t);
}

void SymbolTableX::installHelper(std::string val, njnr::type t)
{
   if (njnr::type::OPERATOR == t)
   {
      std::shared_ptr<TSOperatorType> o{new TSOperatorType(val)};
      stack.front().install<std::shared_ptr<TSOperatorType>>(val, o);
   }
   else
   {
      std::shared_ptr<S_TableEntryX> s{new S_TableEntryX{}};
      s->setName(val);
      s->setType(t);
      stack.front().install<std::shared_ptr<S_TableEntryX>>(val, s);
   }
}



// close the topmost stack/lifetime scope
//  static SymbolTableX* createTree(Compiler& compiler,int Stacksize);
/*
void SymbolTableX::addtosymtab(type mytype, std::shared_ptr<List> myList)
{
}

//FIXME: take in a ReturnPacket* instead?
void SymbolTableX::addtosymtab(const std::string key,
                               std::shared_ptr<void> value,
                               njnr::type ttype)
{
}
*/

std::shared_ptr<S_TableEntryX> SymbolTableX::createFunc(std::string name,
                                                        type returntype,
                                                        std::shared_ptr<List> paramlist = nullptr)
{
   std::shared_ptr<S_TableEntryX> temp{nullptr};
   bool elip{false};

   if ( name.empty() )
   {
       report(njnr::logType::error,
              "name not found");
   }
   else
   {
      std::shared_ptr<FunctionBinding> tBinding{new FunctionBinding{returntype}};
      tBinding->setName(name);

      if (paramlist != nullptr )
      {
         tBinding->setnum_param(paramlist->size());
      }
      if (tBinding->getnum_param() > 0)
      {
         for (auto element : *paramlist)
         {
            if (element != nullptr)
            {
               std::shared_ptr<ParameterListNode> n_element{dynamic_pointer_cast<ParameterListNode>(element)};
               if (nullptr != n_element)
               {
                  tBinding->getparam_type().push_back(n_element->gettype());
                  if ( n_element->getval() == "..." )
                  {
                      elip = true;
                  }
                  else
                  {
                      elip = false;
                  }
               }
            }
         }
         if (elip == true)
         {
            tBinding->setactual_num(tBinding->getnum_param());
            tBinding->setnum_param(-1);
         }
      }

      temp = std::shared_ptr<S_TableEntryX>(new S_TableEntryX{name, tBinding, njnr::type::VOID});
   }
   return temp;
}

std::shared_ptr<S_TableEntryX> SymbolTableX::createVar(std::string name, type t_type,
                                       int offset)
{
   std::shared_ptr<VariableBinding> tBindingV{new VariableBinding{}};

   tBindingV->settype(t_type);
   tBindingV->setoffset(offset);
   tBindingV->setName(name);

   std::shared_ptr<S_TableEntryX> result{
                                          std::shared_ptr<S_TableEntryX>(
                                           new S_TableEntryX(
                                                             name,
                                                             tBindingV,
                                                             njnr::type::VOID
                                                            )
                                          )
                                        };
   return result;
}

std::shared_ptr<S_TableEntryX> SymbolTableX::createParam(std::string name, type t_type,
                                         int offset)
{
   std::shared_ptr<ParameterBinding> tBindingP{new ParameterBinding{}};

   tBindingP->settype(t_type);
   tBindingP->setoffset(offset);

   std::shared_ptr<S_TableEntryX> temp{
                                         new S_TableEntryX{name,
                                                           tBindingP,
                                                           njnr::type::VOID}
                                      };
   return temp;
}
