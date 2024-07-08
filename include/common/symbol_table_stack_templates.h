#ifndef SYMBOL_TABLE_STACK_TEMPLATES_H
#define SYMBOL_TABLE_STACK_TEMPLATES_H
#include "symbol_table_entry.hpp"
// instantiated templates for use in code
template bool SymbolTable::install(S_TableEntryX* element);
template S_TableEntryX* SymbolTable::lookup(const std::string name);
#endif // SYMBOL_TABLE_STACK_TEMPLATES_H
