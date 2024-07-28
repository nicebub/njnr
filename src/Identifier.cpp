#include <string>

#include "Identifier.hpp"
#include "ReturnPacket.hpp"
#include "type.hpp"
using namespace njnr;

   const std::string Identifier::toString() const
   {
      std::string ret = ReturnPacket::toString();
      return "\nvalue: " + value + "\n" + ret;
   }
   Identifier::Identifier() : Constant{false, njnr::type::IDENT, false, 0},
                              value{""} {}

   Identifier::Identifier(const std::string invalue) :
                          Constant{false, njnr::type::IDENT, false, 0},
                          value{invalue}
                          {}

   Identifier::Identifier(const Constant in) :
                          Constant{in.getlval(),
                          njnr::type::IDENT, false, in.getoffset()},
                          value{in.getValue()}
                          {}

   Identifier& Identifier::operator=(const Identifier& in)
   {
       if (&in != this)
       {
           value = in.value;
           lval = in.lval;
           numeric = false;
           ttype = njnr::type::IDENT;
           offset = in.offset;
       }
       return *this;
   }
   std::string Identifier::getvalue() const
   {
       return value;
   }

   void Identifier::setvalue(const std::string in)
   {
       value = in;
   }
