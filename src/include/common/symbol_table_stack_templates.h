#ifndef SRC_INCLUDE_COMMON_SYMBOL_TABLE_STACK_TEMPLATES_H_
#define SRC_INCLUDE_COMMON_SYMBOL_TABLE_STACK_TEMPLATES_H_
#include <config.h>
#include <string>
#include "symbol_table_entry.hpp"
#include "operator.hpp"
// instantiated templates for use in code
template bool SymbolTable::install(std::shared_ptr<njnr::S_TableEntryX> element);
template bool SymbolTable::install(std::shared_ptr<njnr::TSOperatorType> element);
template std::shared_ptr<njnr::S_TableEntryX> SymbolTable::lookup(const std::string name);
template std::shared_ptr<njnr::TSOperatorType> SymbolTable::lookup(const std::string name);
template std::shared_ptr<njnr::S_TableEntryX>  SymbolTable::remove(std::string key);
#endif  // SRC_INCLUDE_COMMON_SYMBOL_TABLE_STACK_TEMPLATES_H_
