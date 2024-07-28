#include <config.h>
#include <string>

#include "VariableBinding.hpp"
#include "type.hpp"
#include "Identifier.hpp"
using namespace njnr;

   Varb::Varb() : Identifier{} {}
   Varb::~Varb() {
                  report(njnr::logType::debug, "running Varb() Destructor");
                  report(njnr::logType::debug, this->toString());
                 }

   const std::string Varb::toString() const
   {
      return ReturnPacket::toString();
   }
