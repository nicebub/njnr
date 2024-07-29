#ifndef SRC_INCLUDE_TSTYPE_HPP_
#define SRC_INCLUDE_TSTYPE_HPP_

#include <config.h>
#include <string>

#include "TSAbstractType.hpp"

namespace njnr
{
/**
 * @brief Generic lower-level implementation of Abstract Class Interface
 *         TSAbstractType
 * 
 */
class TSType : public TSAbstractType
{
   public:
      TSType() : TSAbstractType("GenericType__NA__()"),
                                isNumeric{false},
                                isLval{false} {};

      explicit TSType(const std::string typeValue) :
                   TSAbstractType("GenericType" + typeValue + "()"),
                   isNumeric{false},
                   isLval{false} {};


      TSType(const std::string typeValue,
             const bool isNumeric,
             const bool isLval = false) :
             TSAbstractType("GenericType" + typeValue + "()"),
             isNumeric{isNumeric},
             isLval{isLval} {};

      virtual ~TSType()
      {
         report(njnr::logType::debug,
                "running TSType() Destructor");
         report(njnr::logType::debug, this->toString());
         report(njnr::logType::debug, "isnumeric" + isNumeric);
         report(njnr::logType::debug, "isLval" + isLval);
      }

      virtual const bool getNumeric()          const noexcept
      {
         return isNumeric;
      }
      virtual const bool getLVal()             const noexcept
      {
         return isLval;
      }

      virtual const std::string toString()     const noexcept
      {
         return typeValue;
      }
      virtual const std::string getTypeValue() const noexcept
      {
         return typeValue;
      }
      virtual const njnr::type getType()       const noexcept
      {
         return njnr::type::VOID;
      }

      virtual TSType& operator=(const TSType& t)
      {
         if (const_cast<TSType*>(&t) != this)
         {
            this->typeValue = t.typeValue;
            this->isNumeric = t.isNumeric;
            this->isLval = t.isLval;
         }
         return *this;
      }

   private:
      bool isNumeric;
      bool isLval;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_TSTYPE_HPP_
