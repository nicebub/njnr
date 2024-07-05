#include <map>
#include <string>
#include <iostream>

#include "symbol_table.hpp"

using namespace njnr;

void* Table::lookup(const std::string key)
{
   auto result{table.find(key)};
   if(result != table.end())
   {
      return result->second;
   }
   return nullptr;
} // get data for symbol

void* Table::lookupB(const std::string key)
{
   try
   {
      auto result{table.at(key)};
      return result;
   }
   catch(std::out_of_range& e)
   {
       // not in table
       std::cout << "caught out of range\n";
   }
   return nullptr;
} // get data for symbol ?

bool Table::install(std::string key, void* value)
{
   bool answer{false};
   try
   {
      table.at(key);
      std::cerr << "error: symbol already declared in current scope\n";
   }
   catch(std::out_of_range& e)
   {
      std::cout << "caught out of range, does not exist:" << key << " installing into table\n";
      table[key] = value;
      answer = true;
   }
   //std::cout << "through install function of symbol table. Printing symbol table tree\n";
   // printTree(symtab);

   return answer;
} // install key:value in table

bool  Table::isEmpty() const noexcept
{
   return table.empty();
}                          // return true if table is empty

/* number of symbols in table */
bool  Table::count() const noexcept
{
   return table.size();   
}
