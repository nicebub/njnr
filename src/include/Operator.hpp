#ifndef SRC_INCLUDE_OPERATOR_HPP_
#define SRC_INCLUDE_OPERATOR_HPP_

#include <config.h>
#include <string>
#include "type.hpp"
#include "TSType.hpp"
#include "TSOperatorType.hpp"

namespace njnr
{
class Operator
{
   public:
      Operator() : leftside{nullptr}, rightside{nullptr}, tType{} {}
      explicit Operator(std::shared_ptr<void> l,
                        std::shared_ptr<void> r = nullptr) :
                                                        leftside{l},
                                                        rightside{r},
                                                        tType{}
                                                        {}
      std::shared_ptr<void> getLeftSide() { return leftside; }
      void setLeftSide(std::shared_ptr<void> l) { leftside = l; }
      std::shared_ptr<void> getRightSide() { return rightside; }
      void setRightSide(std::shared_ptr<void> r) { rightside = r; }
      njnr::type getType() { return tType.getType(); }
      void setType(TSOperatorType t) { tType = t; }
   private:
      std::shared_ptr<void> leftside;
      std::shared_ptr<void> rightside;
      TSOperatorType tType;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_OPERATOR_HPP_
