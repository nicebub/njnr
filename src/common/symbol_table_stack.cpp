#include <map>
#include <deque>
#include <string>
#include <iostream>

#include "type.hpp"
#include "symbol_table_entry.hpp"
#include "symbol_table.hpp"
#include "symbol_table_stack.hpp"

using namespace njnr;

// Constructor
SymbolTable::SymbolTable(Compiler& c) : compiler{c}, stack{Table{}} {}

// Destructor
SymbolTable::~SymbolTable() {}

void SymbolTable::install(S_TableEntry* entry)
{
   stack.front().install<S_TableEntry*>(entry->getKey(), entry);
}

void SymbolTable::installIdentifier(std::string val)
{
   installHelper(val, njnr::type::IDENT);
}

void SymbolTable::installStrConstant(std::string val)
{
   installHelper(val, njnr::type::STR);
}

void SymbolTable::installIntConstant(std::string val)
{
   installHelper(val, njnr::type::INT);
}

void SymbolTable::installFloatConstant(std::string val)
{
   installHelper(val, njnr::type::FLOAT);
}

void SymbolTable::installCharConstant(std::string val)
{
   installHelper(val, njnr::type::CHAR);
}

void SymbolTable::installHelper(std::string val, njnr::type t)
{
   S_TableEntry* s{new S_TableEntry{}};
   s->setName(val);
   s->setType(t);
   stack.front().install<S_TableEntry*>(val, s);
}

// install a symbol in the symbol table
void* SymbolTable::lookup(const std::string name)
{
   void* res = nullptr;
   auto tbl = stack.begin();
   for(; tbl != stack.end(); tbl++)
   {
      res = tbl->lookup<void*>(name);
      if(nullptr != res)
      {
         // found element in the symbol table stack, exit loop and return it
         break;
      }
   }

   // output error if we went through whole stack without finding an element
   if(tbl == stack.end())
   {
      std::cout << "member not found in symbol table stack" << std::endl;
   }

   return res;
}

// look up a symbol in scope and return its value
void* SymbolTable::lookupB(const std::string name)
{
   return stack.front().lookupB<void*>(name);
}

// look up a symbol in scope and return its table entry
bool SymbolTable::inCurrentScope(const std::string name)
{
   return stack.front().lookup<void*>(name) ? true : false;
}

// true if symbol is in current scope
void SymbolTable::openscope()
{
   stack.push_front(Table{});
}

// open a new stack/lifetime scope
void SymbolTable::closescope()
{
   stack.pop_front();
}

// close the topmost stack/lifetime scope
//  static SymbolTable* createTree(Compiler& compiler,int Stacksize);
/*
void SymbolTable::addtosymtab(type mytype, List* myList)
{
}

//FIXME: take in a ReturnPacket* instead?
void SymbolTable::addtosymtab(const std::string key, void* value, njnr::type ttype)
{
}
*/
int SymbolTable::getleveldif(std::string name)
{
   return 0;
}

S_TableEntry* SymbolTable::createFunc(std::string name, type returntype, List* paramlist)
{
   S_TableEntry* temp{nullptr};
   bool elip{false};

   if( name.empty() )
   {
       compiler.error("name not found\n","");
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

S_TableEntry* SymbolTable::createVar(std::string name, type t_type, int offset)
{
   Varb* tBindingV{new Varb{}};

   tBindingV->settype(t_type);
   tBindingV->setoffset(offset);
   tBindingV->setvalue(name);

   S_TableEntry* result{new S_TableEntry{name,tBindingV, njnr::type::VOID}};
   return result;
}

S_TableEntry* SymbolTable::createParam(std::string name, type t_type, int offset)
{
   Paramb* tBindingP{new Paramb{}};

   tBindingP->settype(t_type);
   tBindingP->setoffset(offset);

   S_TableEntry* temp{new S_TableEntry{name,tBindingP, njnr::type::VOID}};
   return temp;
}
