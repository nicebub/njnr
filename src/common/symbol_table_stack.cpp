#include <map>
#include <deque>
#include <string>
#include <iostream>

#include "type.hpp"
#include "symbol_table_entry.hpp"
#include "symbol_table.hpp"
#include "symbol_table_stack.hpp"

using namespace njnr;

SymbolTable::SymbolTable(Compiler& c) : compiler{c}, stack{}
{
   stack.push_back(Table{});
}
// Default Constructor
//      SymbolTable(Compiler& compiler);  // Constructor that takes a compiler object - they point to each other
SymbolTable::~SymbolTable()
{
}
// Deconstructor
//      void printTree() const;                       // print symbol table tree
void SymbolTable::install(S_TableEntry* entry)
{
   std::string key{entry->getKey()};
   stack.front().install(key, entry->getValue(), entry->getType());
}

void SymbolTable::install(std::string val)
{
   stack.front().install(val, val, njnr::type::STR);
}
void SymbolTable::install(int val)
{
   std::string key{val};
   stack.front().install(key, val, njnr::type::INT);
}
void SymbolTable::install(float val)
{
   std::string key{val};
   stack.front().install(key, val, njnr::type::FLOAT);
}
void SymbolTable::install(char val)
{
   std::string key{val};
   stack.front().install(key, val, njnr::type::CHAR);
}

// install a symbol in the symbol table
void* SymbolTable::lookup(const std::string name)
{
   return stack.front().lookup(name);
}
// look up a symbol in scope and return its value
S_TableEntry* SymbolTable::lookupB(const std::string name)
{
   return static_cast<S_TableEntry*>(stack.front().lookupB(name));
}
// look up a symbol in scope and return its table entry
bool SymbolTable::inCurrentScope(const std::string name)
{
   return stack.front().lookup(name) ? true : false;
}
// true if symbol is in current scope
void SymbolTable::openscope()
{
   Table newTable{};
   stack.push_front(newTable);
}
// open a new stack/lifetime scope
void SymbolTable::closescope()
{
   stack.pop_front();
}
// close the topmost stack/lifetime scope
//  static SymbolTable* createTree(Compiler& compiler,int Stacksize);
void SymbolTable::addtosymtab(type mytype, List* myList)
{
}
//FIXME: take in a ReturnPacket* instead?
void SymbolTable::addtosymtab(const std::string key, void* value, njnr::type ttype)
{
}
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

