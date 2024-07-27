#ifndef SRC_INCLUDE_RETURNPACKET_HPP_
#define SRC_INCLUDE_RETURNPACKET_HPP_

#include <config.h>
#include <string>
#include <memory>

#include "type.hpp"
#include "BaseData.hpp"

namespace njnr
{
class ReturnPacket : public BaseData
{
   public:
      ReturnPacket();
      ReturnPacket(bool lval, njnr::type ttype, bool ifnum, int offset);
      virtual ~ReturnPacket()
      {
         report(njnr::logType::debug,
               "running ReturnPacket() Destructor");
         report(njnr::logType::debug, "params" + params);
         report(njnr::logType::debug, "offset" + offset);
         report(njnr::logType::debug, "lval" + lval);
         report(njnr::logType::debug, "numeric" + numeric);
         report(njnr::logType::debug, "ttype" + std::to_string(static_cast<int>(ttype)));
         funcent = nullptr;
      }
      const bool getlval() const;
      void setlval(const bool in);
      const njnr::type gettype() const;
      void settype(const njnr::type in);
      const bool getnumeric() const;
      void setnumeric(const bool in);
      int getoffset() const;
      void setoffset(const int in);
      const std::string toString() const;

      struct Pair m_pair;
      std::shared_ptr<void> funcent;
      int params;
   protected:
      int offset;
      bool lval;
      bool numeric;
      njnr::type ttype;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_RETURNPACKET_HPP_
