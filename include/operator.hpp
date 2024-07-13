#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include "type.hpp"

namespace njnr
{
   class TSOperatorType : public TSType
   {
      public:
         TSOperatorType() : TSType("", njnr::type::OPERATOR, true, false), op{""} {};

         TSOperatorType(const std::string& op) : TSType(op, njnr::type::OPERATOR, true, false), op{op} {};

         TSOperatorType(const std::string& op,
                        bool isNumeric=false,
                        bool isLval = false) : TSType(op,
                                                      njnr::type::OPERATOR,
                                                      isNumeric,
                                                      isLval), op{op} {};

         const TSOperatorType& operator=(const TSOperatorType& t) = delete;
         virtual ~TSOperatorType() {};
         virtual const std::string toString() noexcept;
         virtual const std::string getTypeValue() const noexcept;
         virtual const njnr::type getType() const noexcept;
      private:
         const std::string& op;
   };
}

#endif // OPERATOR_HPP
