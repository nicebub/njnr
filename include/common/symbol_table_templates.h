#ifndef SYMBOL_TABLE_TEMPLATES_H
#define SYMBOL_TABLE_TEMPLATES_H
// instantiated templates for use in code
#include "symbol_table_entry.hpp"
template bool Table::install(std::string key, S_TableEntry* value);
template void* Table::lookup(const std::string key);         // get data for symbol
template void* Table::lookupB(const std::string key);        // get data for symbol ?
template bool  Table::install(std::string key, void* value); // install key:value in table
template S_TableEntry* Table::lookup(const std::string n);


#endif // SYMBOL_TABLE_TEMPLATES_H
