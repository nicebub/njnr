#ifndef SRC_INCLUDE_VARIABLEBINDING_HPP_
#define SRC_INCLUDE_VARIABLEBINDING_HPP_

#include <config.h>
#include <string>

#include "cpptypes.hpp"
#include "Identifier.hpp"

namespace njnr
{
class Varb : public Identifier
{
   public:
      Varb();
      virtual ~Varb();
      const std::string toString() const;
   private:
};
}  // namespace njnr
#endif  // SRC_INCLUDE_VARIABLEBINDING_HPP_
