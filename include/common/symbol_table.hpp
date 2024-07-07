#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <map>
#include <string>

namespace njnr
{
   /**
    * @brief Used for Symbol Table
    * 
    */
   class Table
   {
      public:
         Table() = default;                                           // Default Constructor
         ~Table() = default;                                          // Destructor
         template<typename T>T lookup(const std::string key);         // get data for symbol
         template<typename T>T lookupB(const std::string key);        // get data for symbol ?
         template<typename T>bool install(std::string key, T value) ; // install key:value in table
         template<typename T>T remove(std::string key);               // remove from table
         bool  contains(const std::string key) const;
         bool  isEmpty() const noexcept;                              // return true if table is empty
         bool  count() const noexcept;
      private:
         std::map<std::string, void*> table;                          // string,void* mapping
   };
}
#endif // SYMBOL_TABLE_H
