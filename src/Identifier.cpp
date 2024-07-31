#include <config.h>
#include <string>

#include "Identifier.hpp"
#include "ReturnPacket.hpp"
#include "type.hpp"
using njnr::Identifier;
using njnr::Constant;

   const std::string Identifier::toString() const
   {
      std::string ret = ReturnPacket::toString();
      return "\name: " + name + "\n" + ret;
   }
   Identifier::Identifier() : Constant{"", njnr::type::IDENT},
                              name{""} {}

   Identifier::Identifier(const std::string inName) :
                          Constant{"", njnr::type::IDENT},
                          name{inName}
                          {}

   Identifier::Identifier(const std::string inName, std::string defaultVal) :
                          Constant{defaultVal,
                          njnr::type::IDENT},
                          name{inName}
                          {}

   Identifier::Identifier(const std::string inName,
                          std::shared_ptr<Constant> inConstant) :
                          Constant{*inConstant},
                          name{inName}
                          {}

   Identifier::Identifier(const Constant in) :
                          Constant{in.getlval(),
                          njnr::type::IDENT, false, in.getoffset()},
                          name{""}
                          {}

   Identifier& Identifier::operator=(const Identifier& in)
   {
       if (&in != this)
       {
           name = in.name;
           lval = in.lval;
           numeric = false;
           ttype = njnr::type::IDENT;
           offset = in.offset;
       }
       return *this;
   }
   std::string Identifier::getName() const
   {
       return name;
   }

   void Identifier::setName(const std::string inName)
   {
       name = inName;
   }
