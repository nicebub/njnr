#ifndef SRC_INCLUDE_TRANSLATIONUNIT_HPP_
#define SRC_INCLUDE_TRANSLATIONUNIT_HPP_

#include <config.h>
#include <string>
#include <memory>

#include "type.hpp"
#include "ReturnPacket.hpp"

namespace njnr
{
class Translation_Unit : public ReturnPacket
{
   public:
      Translation_Unit();
//      Translation_Unit(std::shared_ptr<FunctionBinding> func);
//      Translation_Unit(VariableBinding* varb); // placeholder type -- needs to change
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
#endif // SRC_INCLUDE_TRANSLATIONUNIT_HPP_
