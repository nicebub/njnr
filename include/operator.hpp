#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include "type.hpp"

namespace njnr
{
   class TSOperatorType : public TSType
   {
      public:
         TSOperatorType() = delete;
         TSOperatorType(const std::string& op);
         TSOperatorType(const TSOperatorType& t) = delete;
         const TSOperatorType& operator=(const TSOperatorType& t) = delete;
         virtual ~TSOperatorType() {};
         virtual const std::string toString() noexcept;
         virtual const bool getLVal() const noexcept;
         virtual const bool getNumeric() const noexcept;
         virtual const njnr::type getType() const noexcept;
         virtual const std::string getTypeValue() const noexcept;
      private:
         const std::string& op;
   };
}

#endif // OPERATOR_HPP
