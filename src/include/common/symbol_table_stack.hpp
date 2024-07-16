#ifndef SRC_INCLUDE_COMMON_SYMBOL_TABLE_STACK_HPP_
#define SRC_INCLUDE_COMMON_SYMBOL_TABLE_STACK_HPP_

#include <config.h>
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
      explicit SymbolTable(Compiler&);                       // Constructor
      virtual ~SymbolTable();                               // Destructor
      template <typename T>bool install(T element);
      // look up a symbol in scope and return its value
      template <typename T>T lookup(const std::string name);
      // look up a symbol in scope and return its table entry
      template <typename T>T lookupB(const std::string name);

      template<typename T>T remove(std::string key);

      // open a new stack/lifetime scope
      void openscope();
      // close the topmost stack/lifetime scope
      void closescope();
      // true if symbol is in current scope
      bool inCurrentScope(const std::string name);

      /* deprecated and want to phase out */
      // look up a symbol in scope and return its value
      void* lookup(const std::string name);
      // look up a symbol in scope and return its table entry
      void* lookupB(const std::string name);

      /** TODO: implement */
      // level difference from root
      int getleveldif(const std::string name) const;
      // print symbol table tree
      void printTree() const;
   protected:
      // Stack of 'Symbol' Tables
      std::deque<Table> stack;
   private:
      // reference to compiler that instantiate this instance
      Compiler& compiler;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_COMMON_SYMBOL_TABLE_STACK_HPP_
