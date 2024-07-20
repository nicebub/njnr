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

class Operator
{
   public:
      Operator() : leftside{nullptr}, rightside{nullptr}, tType{} {}
      explicit Operator(void* l, void* r = nullptr) : leftside{l},
                                                      rightside{r},
                                                      tType{}
                                                      {}
      void* getLeftSide() { return leftside; }
      void setLeftSide(void* l) { leftside = l; }
      void* getRightSide() { return rightside; }
      void setRightSide(void* r) { rightside = r; }
      njnr::type getType() { return tType.getType(); }
      void setType(TSOperatorType t) { tType = t; }
   private:
      void* leftside;
      void* rightside;
      TSOperatorType tType;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_OPERATOR_HPP_
