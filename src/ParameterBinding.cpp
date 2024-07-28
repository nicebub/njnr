#include <config.h>
#include <string>

#include "ParameterBinding.hpp"
#include "ReturnPacket.hpp"
#include "type.hpp"
using namespace njnr;

   const std::string Paramb::toString() const
   {
      return ReturnPacket::toString();
   }
   Paramb::Paramb() : ReturnPacket{} {}
   Paramb::~Paramb()
   {
      report(njnr::logType::debug,
             "running Paramb() Destructor");
      report(njnr::logType::debug, this->toString());

   }
