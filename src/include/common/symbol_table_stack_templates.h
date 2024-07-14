#ifndef SYMBOL_TABLE_STACK_TEMPLATES_H
#define SYMBOL_TABLE_STACK_TEMPLATES_H
#include <config.h>
#include "symbol_table_entry.hpp"
#include "operator.hpp"
// instantiated templates for use in code
template bool SymbolTable::install(S_TableEntryX* element);
template bool SymbolTable::install(TSOperatorType* element);
template S_TableEntryX* SymbolTable::lookup(const std::string name);
template TSOperatorType* SymbolTable::lookup(const std::string name);
#endif // SYMBOL_TABLE_STACK_TEMPLATES_H
