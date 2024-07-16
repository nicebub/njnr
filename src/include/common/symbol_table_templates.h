#ifndef SRC_INCLUDE_COMMON_SYMBOL_TABLE_TEMPLATES_H_
#define SRC_INCLUDE_COMMON_SYMBOL_TABLE_TEMPLATES_H_
// instantiated templates for use in code
#include <config.h>
#include <string>
#include "symbol_table_entry.hpp"
#include "operator.hpp"
template bool Table::install(std::string key, S_TableEntryX* value);
template bool Table::install(std::string key, TSOperatorType* value);
// get data for symbol
template void* Table::lookup(const std::string key);
// get data for symbol ?
template void* Table::lookupB(const std::string key);
// install key:value in table
template bool  Table::install(std::string key, void* value);
template S_TableEntryX* Table::lookup(const std::string n);
template TSOperatorType* Table::lookup(const std::string n);
template void*  Table::remove(std::string key);


#endif  // SRC_INCLUDE_COMMON_SYMBOL_TABLE_TEMPLATES_H_
