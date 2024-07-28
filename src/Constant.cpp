#include <string>
#include "type.hpp"
#include "Constant.hpp"
using namespace njnr;
Constant::Constant() : ReturnPacket{},
                       val{""},
                       typ{njnr::type::VOID}
                       {}
Constant::Constant(bool lval, njnr::type ttype, bool ifnum, int offset) :
                   ReturnPacket{lval, ttype, ifnum, offset},
                   val{""},
                   typ{njnr::type::VOID}
                   {}
Constant::Constant(std::string val, njnr::type t): val{val}, typ{t} {}

std::string Constant::getValue() const
{
   return val;
}

void Constant::setValue(const std::string in)
{
   val = in;
}

njnr::type Constant::getType() const
{
   return typ;
}

void Constant::setType(const njnr::type t)
{
   typ = t;
}
