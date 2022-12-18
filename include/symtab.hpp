#ifndef _SYMTAB_H
#define _SYMTAB_H

#include <search.h>
#include <cstdio>
#include <map>
#include <deque>

#include "list.hpp"
#include "type.hpp"
#include "compiler.hpp"
#include "cpptypes.hpp"

using namespace njnr;

namespace njnr
{
   /* Compiler class defined elsewhere.  Needed below */
   class Compiler;

   /* An entry in a Hash Table */
   class TableEntry
   {
      public:
         TableEntry();
         TableEntry(std::string name);
         TableEntry(std::string name, ReturnPacket* binding, btype self);
         virtual ~TableEntry();
         TableEntry(const TableEntry& in);
         TableEntry& operator=(const TableEntry& in);
         std::string getName() const;
         void setName(std::string name);
         ReturnPacket* getBinding();
         btype getself() const;
         const std::string toString() const;
      private:
         std::string name;
         ReturnPacket* binding;
         btype self;
   };

   /* Hash Table class */
   class Table
   {
      public:
         Table();
         ~Table();
         ReturnPacket* lookup(const std::string name);
         TableEntry* lookupB(const std::string name);
         bool install(TableEntry * temp);
         bool empty() noexcept;
      private:
         std::map<std::string,TableEntry*> table;
   };

   using stable = std::map<std::string,ReturnPacket*,btype>;


   /* Symbol Table Class */
   class SymbolTable
   {
      public:
         SymbolTable();                    // Default Constructor
         SymbolTable(Compiler& compiler);  // Constructor that takes a compiler object - they point to each other
         ~SymbolTable();                   // Deconstructor
         void printTree() const;                       // print symbol table tree
         void install(TableEntry* entry);              // install a symbol in the symbol table
         ReturnPacket* lookup(const std::string name); // look up a symbol in scope and return its value
         TableEntry* lookupB(const std::string name);  // look up a symbol in scope and return its table entry
         bool inCscope(const std::string name);  // true if symbol is in current scope
         void openscope();  // open a new stack/lifetime scope
         void closescope(); // close the topmost stack/lifetime scope
         //		static SymbolTable* createTree(Compiler& compiler,int Stacksize);
         void addtosymtab(type mytype, List* myList);                                //FIXME: take in a ReturnPacket* instead?
         int getleveldif(std::string name);
         TableEntry* createFunc(std::string name, type returntype, List* paramlist); //FIXME: take in a ReturnPacket* instead?
         TableEntry* createVar(std::string name, type t_type, int offset);           //FIXME: take in a ReturnPacket* instead?
         TableEntry* createParam(std::string name, type t_type, int offset);         //FIXME: take in a ReturnPacket* instead?
      private:
         Compiler& compiler;
         std::deque<Table*> stack;  //Stack of Binary Search Trees
         int actualStacksize;       //used to keep size and top of stack
         int Stacksize;             //default of 100
   };
}
#endif
