#ifndef SRC_INCLUDE_VARIABLEBINDING_HPP_
#define SRC_INCLUDE_VARIABLEBINDING_HPP_

#include <config.h>
#include <string>

#include "Identifier.hpp"

namespace njnr
{
class VariableBinding : public Identifier
{
   public:
      VariableBinding();
      virtual ~VariableBinding();
      const std::string toString() const;
   private:
};
}  // namespace njnr
#endif  // SRC_INCLUDE_VARIABLEBINDING_HPP_
