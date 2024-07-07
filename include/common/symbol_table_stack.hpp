#ifndef SYMBOL_TABLE_STACK_H
#define SYMBOL_TABLE_STACK_H

#include <deque>
#include <string>

#include "symbol_table.hpp"       // for class Table
#include "compiler.hpp"           // for class Compiler

namespace njnr
{
   class SymbolTable
   {
      public:
         SymbolTable() = delete;
         SymbolTable(Compiler&);                       // Constructor
         virtual ~SymbolTable();                               // Destructor
         template <typename T>bool install(T element);
         template <typename T>T lookup(const std::string name);         // look up a symbol in scope and return its value
         template <typename T>T lookupB(const std::string name);        // look up a symbol in scope and return its table entry
         void openscope();                             // open a new stack/lifetime scope
         void closescope();                            // close the topmost stack/lifetime scope
         bool inCurrentScope(const std::string name);  // true if symbol is in current scope

         /* deprecated and want to phase out */
         void* lookup(const std::string name);         // look up a symbol in scope and return its value
         void* lookupB(const std::string name);        // look up a symbol in scope and return its table entry

         /** TODO: implement */
         int getleveldif(const std::string name) const;            // level difference from root
         void printTree() const;                                   // print symbol table tree
      protected:
         std::deque<Table> stack;  //Stack of 'Symbol' Tables
      private:
         Compiler& compiler;       // reference to compiler that instantiate this instance
   };
}
#endif // SYMBOL_TABLE_STACK_H
