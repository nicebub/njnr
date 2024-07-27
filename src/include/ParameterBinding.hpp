#ifndef SRC_INCLUDE_PARAMETERBINDING_HPP_
#define SRC_INCLUDE_PARAMETERBINDING_HPP_

#include <config.h>
#include <string>

#include "cpptypes.hpp"
#include "type.hpp"
#include "ReturnPacket.hpp"

namespace njnr
{
class Paramb : public ReturnPacket
{
   public:
      Paramb();
      virtual ~Paramb();
      const std::string toString() const;
   private:
};
}  // namespace njnr
#endif  // SRC_INCLUDE_PARAMETERBINDING_HPP_
