#ifndef SRC_INCLUDE_PARAMETERBINDING_HPP_
#define SRC_INCLUDE_PARAMETERBINDING_HPP_

#include <config.h>
#include <string>

#include "type.hpp"
#include "ReturnPacket.hpp"

namespace njnr
{
class ParameterBinding : public ReturnPacket
{
   public:
      ParameterBinding();
      virtual ~ParameterBinding();
      const std::string toString() const;
   private:
};
}  // namespace njnr
#endif  // SRC_INCLUDE_PARAMETERBINDING_HPP_
