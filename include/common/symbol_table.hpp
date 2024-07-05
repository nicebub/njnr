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
         Table() = default;                                    // Default Constructor
         ~Table() = default;                                   // Destructor
         void* lookup(const std::string& key);         // get data for symbol
         S_TableEntry lookupB(const std::string& key);        // get data for symbol ?
         bool  install(std::string& key, void* value, njnr::type t); // install key:value in table
         bool  remove(std::string& key);               // remove from table
         bool  isEmpty() const noexcept;                     // return true if table is empty
         bool  count() const noexcept;
      private:
         std::map<std::string, S_TableEntry> table;    // string,void* mapping
   };
}
#endif // SYMBOL_TABLE_H
