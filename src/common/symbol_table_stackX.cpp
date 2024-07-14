#include <config.h>
#include <map>
#include <deque>
#include <string>

#include "type.hpp"                // for njnr::type
#include "symbol_table_entry.hpp"  // for class S_TableEntry
#include "symbol_table.hpp"        // for class Table
#include "symbol_table_stackX.hpp" // for class SymbolTableX
#include "compiler.hpp"            // for njnr::report()
#include "operator.hpp"            // for TSOperatorType()
using namespace njnr;

void SymbolTableX::install2(std::string val, njnr::type t)
{
   installHelper(val, t);
}

void SymbolTableX::installHelper(std::string val, njnr::type t)
{
   if(njnr::type::OPERATOR == t)
   {
      TSOperatorType* o = new TSOperatorType(val);
      stack.front().install<TSOperatorType*>(val, o);
   }
   else
   {
      S_TableEntryX* s{new S_TableEntryX{}};
      s->setName(val);
      s->setType(t);
      stack.front().install<S_TableEntryX*>(val, s);
   }
}



// close the topmost stack/lifetime scope
//  static SymbolTableX* createTree(Compiler& compiler,int Stacksize);
/*
void SymbolTableX::addtosymtab(type mytype, List* myList)
{
}

//FIXME: take in a ReturnPacket* instead?
void SymbolTableX::addtosymtab(const std::string key, void* value, njnr::type ttype)
{
}
*/

S_TableEntryX* SymbolTableX::createFunc(std::string name, type returntype, List* paramlist)
{
   S_TableEntryX* temp{nullptr};
   bool elip{false};

   if( name.empty() )
   {
       report(njnr::logType::error,
              "name not found");
   }
   else
   {
      Funcb* tBinding{new Funcb{returntype}};
      tBinding->setvalue(name);

      if(paramlist!=nullptr )
      {
         tBinding->setnum_param(paramlist->size());
      }
      if(tBinding->getnum_param() >0)
      {
         for(auto &element : *paramlist)
         {
            PListNode* n_element{dynamic_cast<PListNode*>(element)};
            tBinding->getparam_type().push_back(n_element->gettype());
            if( n_element->getval() == "..." )
            {
                elip = true;
            }
            else
            {
                elip=false;
            }
         }
         if(elip == true)
         {
            tBinding->setactual_num(tBinding->getnum_param());
            tBinding->setnum_param(-1);
         }
      }

      temp = new S_TableEntryX{name,tBinding,njnr::type::VOID};
   }
   return temp;
}

S_TableEntryX* SymbolTableX::createVar(std::string name, type t_type, int offset)
{
   Varb* tBindingV{new Varb{}};

   tBindingV->settype(t_type);
   tBindingV->setoffset(offset);
   tBindingV->setvalue(name);

   S_TableEntryX* result{new S_TableEntryX{name,tBindingV, njnr::type::VOID}};
   return result;
}

S_TableEntryX* SymbolTableX::createParam(std::string name, type t_type, int offset)
{
   Paramb* tBindingP{new Paramb{}};

   tBindingP->settype(t_type);
   tBindingP->setoffset(offset);

   S_TableEntryX* temp{new S_TableEntryX{name,tBindingP, njnr::type::VOID}};
   return temp;
}
