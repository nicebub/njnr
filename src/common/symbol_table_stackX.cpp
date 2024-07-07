#include <map>
#include <deque>
#include <string>
#include <iostream>

#include "type.hpp"
#include "symbol_table_entry.hpp"
#include "symbol_table.hpp"
#include "symbol_table_stackX.hpp"

using namespace njnr;

void SymbolTableX::installIdentifier(std::string val)
{
   installHelper(val, njnr::type::IDENT);
}

void SymbolTableX::installStrConstant(std::string val)
{
   installHelper(val, njnr::type::STR);
}

void SymbolTableX::installIntConstant(std::string val)
{
   installHelper(val, njnr::type::INT);
}

void SymbolTableX::installFloatConstant(std::string val)
{
   installHelper(val, njnr::type::FLOAT);
}

void SymbolTableX::installCharConstant(std::string val)
{
   installHelper(val, njnr::type::CHAR);
}

void SymbolTableX::installHelper(std::string val, njnr::type t)
{
   S_TableEntry* s{new S_TableEntry{}};
   s->setName(val);
   s->setType(t);
   stack.front().install<S_TableEntry*>(val, s);
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

S_TableEntry* SymbolTableX::createFunc(std::string name, type returntype, List* paramlist)
{
   S_TableEntry* temp{nullptr};
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

      temp = new S_TableEntry{name,tBinding,njnr::type::VOID};
   }
   return temp;
}

S_TableEntry* SymbolTableX::createVar(std::string name, type t_type, int offset)
{
   Varb* tBindingV{new Varb{}};

   tBindingV->settype(t_type);
   tBindingV->setoffset(offset);
   tBindingV->setvalue(name);

   S_TableEntry* result{new S_TableEntry{name,tBindingV, njnr::type::VOID}};
   return result;
}

S_TableEntry* SymbolTableX::createParam(std::string name, type t_type, int offset)
{
   Paramb* tBindingP{new Paramb{}};

   tBindingP->settype(t_type);
   tBindingP->setoffset(offset);

   S_TableEntry* temp{new S_TableEntry{name,tBindingP, njnr::type::VOID}};
   return temp;
}
