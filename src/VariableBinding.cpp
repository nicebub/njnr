#include <config.h>
#include <string>

#include "VariableBinding.hpp"
#include "type.hpp"
#include "Identifier.hpp"
using njnr::VariableBinding;
using njnr::ReturnPacket;
using njnr::report;

   VariableBinding::VariableBinding() : Identifier{} {}
   VariableBinding::~VariableBinding() {
                  report(njnr::logType::debug, "running VariableBinding() Destructor");
                  report(njnr::logType::debug, this->toString());
                 }

   const std::string VariableBinding::toString() const
   {
      return ReturnPacket::toString();
   }
