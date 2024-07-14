#include <config.h>
#include <map>
#include <string>

#include "symbol_table.hpp"
#include "compiler.hpp"     // currently for njnr::report()

using njnr::Table;

/**
 * @brief lookup key and return its value if found, otherwise nullptr
 * 
 * @tparam T -  type of 'value'
 * @param key - key for search
 * @return T -  value or nullptr
 */
template<typename T>T Table::lookup(const std::string key)
{
   /* iterator type */
   auto result{table.find(key)};

   /* if iterator doesn't point to end() then we found a <key:value> pair */
   if (result != table.end())
   {
      /* The iterators 'second' value, which is the 'value' in <key:value>
          pair */
      return static_cast<T>(result->second);
   }

   /* didn't find it */
   return nullptr;
}

/**
 * @brief lookup key and return its value if found, otherwise nullptr
 * 
 * @tparam T -  type of 'value'
 * @param key - key for search
 * @return T -  value or nullptr
 */
template<typename T>T Table::lookupB(const std::string key)
{
   try
   {
      /* at() throws std::out_of_range exception if key is not found */
      auto result{table.at(key)};
      return result;
   }
   catch(std::out_of_range& e)
   {
      /* didn't find it */
       report(logType::debug,
              "caught out of range - <key:value> not in table: <" + key +
              ":value>");
   }
   return nullptr;
}

/**
 * @brief if not already in symbol table, install <key:value> pair
 * 
 * @tparam T value type
 * @param key key for search and install
 * @param value value for install with key
 * @return true installed
 * @return false failed to install
 */
template<typename T>bool Table::install(std::string key, T value)
{
   bool answer{false};
   try
   {
      /* at() throws std::out_of_range exception if key is not found */
      table.at(key);

      /* didn't throw exception which means its already in table */
      report(logType::error,
             "error: symbol already declared in current scope");
   }
   catch(std::out_of_range& e)
   {
      /* didn't find it - we can install */
      report(logType::debug,
             "installing key: " + key +
             " value: " +
             " into table\n");

      table[key] = value;
      answer = true;
   }
   /*
   report(logType::debug,
          "through install function of symbol table. Printing symbol table tree"
         );
   printTree(symtab);
   */
   return answer;
}  // install key:value in table

/**
 * @brief remove element from table return its value(for usage/deletion?)
 *
 * @tparam T parameter type of 'value'
 * @param key key to loopup element
 * @return T -'value' of type T
 */
template<typename T>T Table::remove(std::string key)
{
   bool answer{answer};
   table.erase(key);
   report(logType::debug, "found element, removing it");
   /*
   report(logType::debug,
          "through install function of symbol table. Printing symbol table tree"
         );
   printTree(symtab);
   */
   return answer;
}  // install key:value in table

/**
 * @brief return whether the symbol table contains an element or not
 * 
 * @param key key to use to lookup
 * @return true exists
 * @return false doesn't exist
 */
bool Table::contains(const std::string key) const
{
   return table.contains(key);
}
/**
 * @brief returns whether or not symbol table is empty
 *
 * @return true
 * @return false
 */
bool  Table::isEmpty() const noexcept
{
   return table.empty();
}                          // return true if table is empty


/* number of symbols in table */
/**
 * @brief return integral count of number of <key:value> pairs are installed
 *         in the table
 * 
 * @return size
 */
bool  Table::count() const noexcept
{
   return table.size();
}

// developer supplied templates for use
#include "symbol_table_templates.h"
