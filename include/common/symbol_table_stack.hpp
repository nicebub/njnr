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
         SymbolTable(Compiler&);                    // Default Constructor
//         SymbolTable(Compiler& compiler);  // Constructor that takes a compiler object - they point to each other
         ~SymbolTable();                   // Deconstructor
//         void printTree() const;                       // print symbol table tree
         void install(S_TableEntry* entry);              // install a symbol in the symbol table

         void install(std::string val);              // install a symbol in the symbol table
         void install(int val);              // install a symbol in the symbol table
         void install(float val);              // install a symbol in the symbol table
         void install(char val);              // install a symbol in the symbol table

         void* lookup(const std::string name); // look up a symbol in scope and return its value
         S_TableEntry* lookupB(const std::string name);  // look up a symbol in scope and return its table entry
         bool inCurrentScope(const std::string name);  // true if symbol is in current scope
         void openscope();  // open a new stack/lifetime scope
         void closescope(); // close the topmost stack/lifetime scope
         //   static SymbolTable* createTree(Compiler& compiler,int Stacksize);
         void addtosymtab(type mytype, List* myList);                                //FIXME: take in a ReturnPacket* instead?
         void addtosymtab(const std::string key, void* value, njnr::type ttype);
         int getleveldif(std::string name);
         S_TableEntry* createFunc(std::string name, type returntype, List* paramlist); //FIXME: take in a ReturnPacket* instead?
         S_TableEntry* createVar(std::string name, type t_type, int offset);           //FIXME: take in a ReturnPacket* instead?
         S_TableEntry* createParam(std::string name, type t_type, int offset);         //FIXME: take in a ReturnPacket* instead?
      private:
         Compiler& compiler;
         std::deque<Table> stack;  //Stack of Binary Search Trees
   };

}


#endif // SYMBOL_TABLE_STACK_H