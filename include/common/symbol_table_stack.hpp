#ifndef SYMBOL_TABLE_STACK_H
#define SYMBOL_TABLE_STACK_H

#include <map>
#include <deque>
#include <string>

#include "type.hpp"
#include "symbol_table_entry.hpp"
#include "symbol_table.hpp"
#include "compiler.hpp"

namespace njnr
{
   class SymbolTable
   {
      public:
         SymbolTable(Compiler&);                       // Constructor
         ~SymbolTable();                               // Destructor
         template <typename T>bool install(T element);
         void installHelper(std::string val, njnr::type t); // generic helper function used by all install functions below

//         void install(S_TableEntry* entry);            // install a symbol in the symbol table
         void installIdentifier(std::string val);
         void installStrConstant(std::string val);     // install a symbol in the symbol table
         void installIntConstant(std::string val);     // install a symbol in the symbol table
         void installFloatConstant(std::string val);   // install a symbol in the symbol table
         void installCharConstant(std::string val);    // install a symbol in the symbol table

         void* lookup(const std::string name);         // look up a symbol in scope and return its value
         void* lookupB(const std::string name);        // look up a symbol in scope and return its table entry

         void openscope();                             // open a new stack/lifetime scope
         void closescope();                            // close the topmost stack/lifetime scope

         bool inCurrentScope(const std::string name);  // true if symbol is in current scope
         int getleveldif(std::string name);            // level difference from root

         S_TableEntry* createFunc(std::string name, type returntype, List* paramlist); //FIXME: take in a ReturnPacket* instead?
         S_TableEntry* createVar(std::string name, type t_type, int offset);           //FIXME: take in a ReturnPacket* instead?
         S_TableEntry* createParam(std::string name, type t_type, int offset);         //FIXME: take in a ReturnPacket* instead?

//         void addtosymtab(type mytype, List* myList);                                //FIXME: take in a ReturnPacket* instead?
//         void addtosymtab(const std::string key, void* value, njnr::type ttype);
//         void printTree() const;                       // print symbol table tree
         //   static SymbolTable* createTree(Compiler& compiler,int Stacksize);
      private:
         Compiler& compiler;
         std::deque<Table> stack;  //Stack of Binary Search Trees
   };
}
#endif // SYMBOL_TABLE_STACK_H
