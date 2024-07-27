#ifndef SRC_INCLUDE_COMMON_SYMBOL_TABLE_STACKX_HPP_
#define SRC_INCLUDE_COMMON_SYMBOL_TABLE_STACKX_HPP_

#include <config.h>
#include <string>

#include "type.hpp"                // for njnr::type
#include "ParameterBinding.hpp"
#include "symbol_table_stack.hpp"  // for class SymbolTable
#include "symbol_table_entry.hpp"  // for class S_TableEntry
#include "Compiler.hpp"            // for class Compiler

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
      explicit SymbolTableX(Compiler* c) : SymbolTable{c} {}
      // Destructor
      virtual ~SymbolTableX()
      {
         report(njnr::logType::debug,
                "running SymbolTableX() Destructor");
      }

         /** TODO: rework */
         void install2(std::string val, njnr::type t);
         void installType(std::string val);
         // generic helper function used by all install functions below
         void installHelper(std::string val, njnr::type t);

      /* unsure about these functions below */
      // FIXME: take in a ReturnPacket* instead?
      std::shared_ptr<S_TableEntryX> createFunc(std::string name,
                                                njnr::type returntype,
                                                std::shared_ptr<List> paramlist);
      // FIXME: take in a ReturnPacket* instead?
      std::shared_ptr<S_TableEntryX> createVar(std::string name, njnr::type t_type, int offset);
      // FIXME: take in a ReturnPacket* instead?
      std::shared_ptr<S_TableEntryX> createParam(std::string name, njnr::type t_type,
                                 int offset);
};
}  // namespace njnr
#endif  // SRC_INCLUDE_COMMON_SYMBOL_TABLE_STACKX_HPP_
