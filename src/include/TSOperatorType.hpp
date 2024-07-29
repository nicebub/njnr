#ifndef SRC_INCLUDE_TSOPERATORTYPE_HPP_
#define SRC_INCLUDE_TSOPERATORTYPE_HPP_

#include <config.h>
#include <string>
#include "type.hpp"
#include "TSType.hpp"

namespace njnr
{
class TSOperatorType : public TSType
{
   public:
      TSOperatorType() : TSType("operator__NA__()") {}

      explicit TSOperatorType(const std::string op) : TSType("operator"+op+"()")
      {}

      TSOperatorType(const std::string op,
                     const bool isNumeric,
                     const bool isLval = false) : TSType("operator" + op + "()",
                                                       isNumeric,
                                                       isLval) {}

      virtual ~TSOperatorType()
      {
         report(njnr::logType::debug,
                "running TSOperatorType() Destructor");
      }

      virtual const njnr::type getType() const noexcept
      {
         return njnr::type::OPERATOR;
      }

      virtual TSOperatorType& operator=(const TSOperatorType& t) = default;
//      const TSOperatorType& operator=(const TSOperatorType& t){};

      /* return the key for the table entry */
      std::string getKey(void) const noexcept {return typeValue;}
};
}  // namespace njnr
#endif  // SRC_INCLUDE_TSOPERATORTYPE_HPP_
