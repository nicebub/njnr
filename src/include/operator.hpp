#ifndef SRC_INCLUDE_OPERATOR_HPP_
#define SRC_INCLUDE_OPERATOR_HPP_

#include <config.h>
#include <string>
#include "type.hpp"

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

      virtual ~TSOperatorType() {}

      virtual const njnr::type getType() const noexcept
      {
         return njnr::type::OPERATOR;
      }

      const TSOperatorType& operator=(const TSOperatorType& t) = delete;

      /* return the key for the table entry */
      std::string getKey(void) const noexcept {return typeValue;}
};
}  // namespace njnr
#endif  // SRC_INCLUDE_OPERATOR_HPP_
