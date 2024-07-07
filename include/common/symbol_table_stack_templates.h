#ifndef SYMBOL_TABLE_STACK_TEMPLATES_H
#define SYMBOL_TABLE_STACK_TEMPLATES_H
// instantiated templates for use in code
template bool SymbolTable::install(S_TableEntry* element);
template S_TableEntry* SymbolTable::lookup(const std::string name);
#endif // SYMBOL_TABLE_STACK_TEMPLATES_H
