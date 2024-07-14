#ifndef SYMBOL_TABLE_STACKX_H
#define SYMBOL_TABLE_STACKX_H

#include <config.h>
#include <string>

#include "type.hpp"               // for njnr::type
#include "symbol_table_stack.hpp" // for class SymbolTable
#include "symbol_table_entry.hpp" // for class S_TableEntry
#include "compiler.hpp"           // for class Compiler
namespace njnr
{
   /**
    * @brief extension to class for specifics
    * 
    */
   class SymbolTableX : public SymbolTable
   {
      public:
         SymbolTableX() = delete;
         SymbolTableX(Compiler& c) : SymbolTable{c}{};                       // Constructor
         virtual ~SymbolTableX() {};                               // Destructor

         /** TODO: rework */
         void install2(std::string val, njnr::type t);
         void installType(std::string val);
         void installHelper(std::string val, njnr::type t); // generic helper function used by all install functions below

         /* unsure about these functions below */
         S_TableEntryX* createFunc(std::string name, njnr::type returntype, List* paramlist); //FIXME: take in a ReturnPacket* instead?
         S_TableEntryX* createVar(std::string name, njnr::type t_type, int offset);           //FIXME: take in a ReturnPacket* instead?
         S_TableEntryX* createParam(std::string name, njnr::type t_type, int offset);         //FIXME: take in a ReturnPacket* instead?
   };
}
#endif // SYMBOL_TABLE_STACKX_H
