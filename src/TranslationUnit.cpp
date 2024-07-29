#include <config.h>
#include <string>

#include "TranslationUnit.hpp"
#include "type.hpp"
using njnr::Translation_Unit;
using njnr::trans_unit_type;
using njnr::ReturnPacket;
using njnr::report;

   const std::string Translation_Unit::toString() const
   {
      std::string ret{ReturnPacket::toString()};
//         std::shared_ptr<ReturnPacket> translation{nullptr};
//         trans_unit_type trans_type;

      return "translation unit: " + this->toString() + "\n" + ret;
   }
   Translation_Unit::Translation_Unit() : translation{nullptr},
                                          trans_type{trans_unit_type::INVALID}
                                          {}

   Translation_Unit::~Translation_Unit()
   {
      report(njnr::logType::debug,
             "running Translation_Unit() Destructor");
      report(njnr::logType::debug, this->toString());
   }

   std::shared_ptr<ReturnPacket> Translation_Unit::get_translation()
   {
      return translation;
   }
   void Translation_Unit::set_translation(std::shared_ptr<ReturnPacket> translation)
   {
      this->translation = translation;
   }
   void Translation_Unit::set_trans_unit_type(trans_unit_type intype)
   {
      trans_type = intype;
   }
   trans_unit_type Translation_Unit::get_trans_unit_type()
   {
      return trans_type;
   }
