#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <map>
#include <string>

#include "symbol_table_entry.hpp"
#include "type.hpp"

namespace njnr
{
   /* Generic Symbol Table class */
   class Table
   {
      public:
//         Table();                                    // Default Constructor
//         ~Table();                                   // Destructor
         void* lookup(const std::string& key);         // get data for symbol
         void* lookupB(const std::string& key);        // get data for symbol ?
         bool  install(std::string& key, void* value); // install key:value in table
         bool  isEmpty() noexcept;                     // return true if table is empty
      private:
         std::map<std::string, S_TableEntry> table;    // string,void* mapping
   };
}
#endif // SYMBOL_TABLE_H
