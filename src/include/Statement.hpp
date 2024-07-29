#ifndef SRC_INCLUDE_STATEMENT_HPP_
#define SRC_INCLUDE_STATEMENT_HPP_

#include <config.h>
#include <string>
#include <memory>

#include "type.hpp"
#include "ReturnPacket.hpp"

namespace njnr
{
//   class S_TableEntry;
class Statement : public ReturnPacket
{
   public:
      Statement();
      statement_type getstype();
      std::shared_ptr<ReturnPacket> getexpr();
      void setexpr(std::shared_ptr<ReturnPacket> expr);
      void setstype(statement_type t);
      virtual ~Statement();
      type getrettype();
      void setrettype(njnr::type t);
      const std::string toString() const;
      std::string printCheckReturn(void) const;
   private:
      statement_type stype;
      std::shared_ptr<ReturnPacket>  expr;
      njnr::type     rettype;
};
}  // namespace njnr
#endif // SRC_INCLUDE_STATEMENT_HPP_
