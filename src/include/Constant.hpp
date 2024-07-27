#ifndef SRC_INCLUDE_CONSTANT_HPP_
#define SRC_INCLUDE_CONSTANT_HPP_

#include <config.h>
#include <string>

#include "cpptypes.hpp"
#include "type.hpp"
#include "ReturnPacket.hpp"

namespace njnr
{
class Constant : public ReturnPacket
{
   public:
      Constant();
      Constant(bool lval, njnr::type ttype, bool ifnum, int offset);
      Constant(std::string val, njnr::type t);
      virtual ~Constant()
      {
         report(njnr::logType::debug,
                "running Constant() Destructor");
         report(njnr::logType::debug, "val" + val);
         report(njnr::logType::debug, "typ" + static_cast<int>(typ));
      }
      std::string getValue() const;
      void setValue(const std::string in);
      njnr::type getType() const;
      void setType(const njnr::type t);
      //  ReturnPacket
   private:
      std::string val;
      njnr::type typ;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_CONSTANT_HPP_
