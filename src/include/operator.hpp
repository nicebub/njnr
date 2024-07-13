#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include <config.h>
#include "type.hpp"

namespace njnr
{
   class TSOperatorType : public TSType
   {
      public:

         TSOperatorType() : TSType("operator__NA__()") {};

         TSOperatorType(const std::string op) : TSType("operator"+op+"()") {};

         TSOperatorType(const std::string op,
                        const bool isNumeric,
                        const bool isLval=false) : TSType("operator"+op+"()",
                                                          isNumeric,
                                                          isLval) {};

         virtual ~TSOperatorType() {};

         virtual const njnr::type getType() const noexcept {return njnr::type::OPERATOR;};

         const TSOperatorType& operator=(const TSOperatorType& t) = delete;

         /* return the key for the table entry */
         std::string getKey(void) const noexcept {return typeValue;};
   };
}

#endif // OPERATOR_HPP
