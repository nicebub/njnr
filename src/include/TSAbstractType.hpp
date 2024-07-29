#ifndef SRC_INCLUDE_TSABSTRACTTYPE_HPP_
#define SRC_INCLUDE_TSABSTRACTTYPE_HPP_

#include <config.h>
#include <string>

#include "type.hpp"

namespace njnr
{
/**
 * @brief Type System Type Abstract Class Interface
 * 
 */
class TSAbstractType
{
   public:
      TSAbstractType() : typeValue{"AbstractType__NA__()"} {};

      explicit TSAbstractType(const std::string typeValue) :
                                 typeValue{"AbstractType" + typeValue+"()"} {}

      virtual                     ~TSAbstractType()
      {
         report(njnr::logType::debug,
                "running TSAbstractType() destructor");
         report(njnr::logType::debug, "typeValue" + typeValue);
      }

      virtual   const bool             getNumeric()    const noexcept = 0;
      virtual   const bool                getLVal()    const noexcept = 0;

      virtual   const std::string        toString()    const noexcept = 0;
      virtual   const std::string    getTypeValue()    const noexcept = 0;
      virtual   const njnr::type          getType()    const noexcept = 0;
      virtual TSAbstractType& operator=(const TSAbstractType& t)
      {
         if (const_cast<TSAbstractType*>(&t) != this)
         {
            this->typeValue = t.typeValue;
         }
         return *this;
      }

   protected:
      std::string typeValue;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_TSABSTRACTTYPE_HPP_
