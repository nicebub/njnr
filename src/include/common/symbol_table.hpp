#ifndef SRC_INCLUDE_COMMON_SYMBOL_TABLE_HPP_
#define SRC_INCLUDE_COMMON_SYMBOL_TABLE_HPP_

#include <config.h>
#include <map>
#include <string>

#include "type.hpp"

namespace njnr
{
   /**
    * @brief Used for Symbol Table
    * 
    */
class Table
{
   public:
      // Default Constructor
      Table() = default;
      // Destructor
      ~Table() { report(njnr::logType::debug, "running Table() Destructor"); };
      // get data for symbol
      template<typename T>std::shared_ptr<T> lookup(const std::string key);
      // get data for symbol ?
      template<typename T>std::shared_ptr<T> lookupB(const std::string key);
      // install key:value in table
      template<typename T>bool install(std::string key, T value);
      // remove from table
      template<typename T>std::shared_ptr<T> remove(std::string key);
      bool  contains(const std::string key) const;
      // return true if table is empty
      bool  isEmpty() const noexcept;
      bool  count() const noexcept;
   private:
      // string,std::shared_ptr<void> mapping
      std::map<std::string, std::shared_ptr<void>> table;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_COMMON_SYMBOL_TABLE_HPP_
