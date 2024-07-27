#ifndef SRC_INCLUDE_CPPTYPES_HPP_
#define SRC_INCLUDE_CPPTYPES_HPP_

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

class Translation_Unit : public ReturnPacket
{
   public:
      Translation_Unit();
//      Translation_Unit(std::shared_ptr<Funcb> func);
//      Translation_Unit(Varb* varb); // placeholder type -- needs to change
      virtual ~Translation_Unit();
      std::shared_ptr<ReturnPacket> get_translation();
      void set_translation(std::shared_ptr<ReturnPacket> translation);
      void set_trans_unit_type(trans_unit_type intype);
      trans_unit_type get_trans_unit_type();
      const std::string toString() const;
   private:
      std::shared_ptr<ReturnPacket> translation;
      trans_unit_type trans_type;
};

}  // namespace njnr
#endif  // SRC_INCLUDE_CPPTYPES_HPP_
