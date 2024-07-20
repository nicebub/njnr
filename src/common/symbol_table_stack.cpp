#include <config.h>
#include <map>
#include <deque>
#include <string>

#include "symbol_table.hpp"
#include "symbol_table_stack.hpp"

using njnr::SymbolTable;
using njnr::SymbolTableX;
/**
 * @brief install element of type T in top symbol table
 * 
 * @tparam T type of element installing into symbol table
 * @param element element to install
 * @return true installed
 * @return false wasn't installed
 */
template <typename T>bool SymbolTable::install(T element)
{
   stack.front().install<T>(element->getKey(), element);
   return true;
}

/**
 * @brief Construct a new Symbol Table:: Symbol Table object
 * 
 * @param c reference to compiler that instantiates this symbol table
 */
SymbolTable::SymbolTable(Compiler& c) : stack{Table{}}, compiler{c} {}

/**
 * @brief Destroy the Symbol Table:: Symbol Table object
 * 
 */
SymbolTable::~SymbolTable()
{
   report(njnr::logType::debug,
          "running SymbolTable() Destructor");
}

/**
 * @brief lookup a <key:value> pair in topmost symbol table in stack
 * 
 * @param name key to lookup <key:value> pair
 * @return void* if return type is void* returns 'value'
 */
void* SymbolTable::lookup(const std::string name)
{
   void* res = nullptr;
   auto tbl = stack.begin();
   for (; tbl != stack.end(); tbl++)
   {
      res = tbl->lookup<void*>(name);
      if (nullptr != res)
      {
         // found element in the symbol table stack, exit loop and return it
         break;
      }
   }

   // output error if we went through whole stack without finding an element
   if (tbl == stack.end())
   {
      report(logType::debug,
             "member not found in symbol table stack");
   }

   return res;
}

template<typename T>T SymbolTable::lookup(const std::string name)
{
   T res = nullptr;
   auto tbl = stack.begin();
   for (; tbl != stack.end(); tbl++)
   {
      res = tbl->lookup<T>(name);
      if (nullptr != res)
      {
         // found element in the symbol table stack, exit loop and return it
         break;
      }
   }

   // output error if we went through whole stack without finding an element
   if (tbl == stack.end())
   {
      report(logType::debug,
             "member not found in symbol table stack");
   }

   return res;
}

/**
 * @brief lookup symbol of <key:value> with 'name' = 'key' in topmost
 *         symbol table on stack
 * 
 * @param name key name of <key:value> pair
 * @return void* return 'value' is type of 'value' is void*
 */
void* SymbolTable::lookupB(const std::string name)
{
   return stack.front().lookupB<void*>(name);
}


/**
 * @brief return whether a symbol can be found in the topmost symbol table on the
 *         stack
 * 
 * @param name key to lookup
 * @return true found
 * @return false not found
 */
bool SymbolTable::inCurrentScope(const std::string name)
{
   return stack.front().contains(name) ? true : false;
}

/**
 * @brief open a new scope by pushing an empty symbol table onto the stack and making
 *         it the current symbol table
 *
 */
void SymbolTable::openscope()
{
   stack.push_front(Table{});
}

/**
 * @brief close the existing current scope by destroying the topmost symbol table
 *         make the next one in the list the current symbol table(scope) unless
 *         it was the only symbol table and now the stack is empty
 *
 */
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
int SymbolTable::getleveldif(const std::string name) const
{
   return 0;
}
/**
 * @brief print stack of symbol tables
 * 
 */
void SymbolTable::printTree() const
{
   report(logType::debug, "tree");
}

/**
 * @brief remove element from top table return its value(for usage/deletion?)
 *
 * @tparam T parameter type of 'value'
 * @param key key to loopup element
 * @return T -'value' of type T
 */
template<typename T>T SymbolTable::remove(std::string key)
{
   T x{nullptr};
   try
   {
      x = reinterpret_cast<S_TableEntryX*>(stack.front().remove<void*>(key));
      if (nullptr != x)
      {
         report(logType::debug, "found element topmost table, removing it");
      }
      else
      {
         report(logType::debug, "didn't find element, can't remove it");
      }
   }
   catch(std::out_of_range& e)
   {
      report(logType::debug, "element, already removed");
   }
   report(logType::debug, "leaving try-catch");
   /*
   report(logType::debug,
          "through install function of symbol table. Printing symbol table tree"
         );
   printTree(symtab);
   */
   return x;
}  // install key:value in table


#include "symbol_table_stack_templates.h"
