#ifndef SRC_INCLUDE_COMMON_SYMBOL_TABLE_STACKX_HPP_
#define SRC_INCLUDE_COMMON_SYMBOL_TABLE_STACKX_HPP_

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
      // Constructor
      explicit SymbolTableX(Compiler& c) : SymbolTable{c} {}
      // Destructor
      virtual ~SymbolTableX() {}

      /** TODO: rework */
      void installIdentifier(std::string val);
      // install a symbol in the symbol table
      void installStrConstant(std::string val);
      // install a symbol in the symbol table
      void installIntConstant(std::string val);
      // install a symbol in the symbol table
      void installFloatConstant(std::string val);
      // install a symbol in the symbol table
      void installCharConstant(std::string val);
      void installType(std::string val);
      // generic helper function used by all install functions below
      void installHelper(std::string val, njnr::type t);

      /* unsure about these functions below */
      // FIXME: take in a ReturnPacket* instead?
      S_TableEntryX* createFunc(std::string name,
                                njnr::type returntype, List* paramlist);
      // FIXME: take in a ReturnPacket* instead?
      S_TableEntryX* createVar(std::string name, njnr::type t_type, int offset);
      // FIXME: take in a ReturnPacket* instead?
      S_TableEntryX* createParam(std::string name, njnr::type t_type,
                                 int offset);
};
}  // namespace njnr
#endif  // SRC_INCLUDE_COMMON_SYMBOL_TABLE_STACKX_HPP_
