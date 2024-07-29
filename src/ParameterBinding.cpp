#include <config.h>
#include <string>

#include "ParameterBinding.hpp"
#include "ReturnPacket.hpp"
#include "type.hpp"
using njnr::ParameterBinding;
using njnr::ReturnPacket;
using njnr::report;

   const std::string ParameterBinding::toString() const
   {
      return ReturnPacket::toString();
   }
   ParameterBinding::ParameterBinding() : ReturnPacket{} {}
   ParameterBinding::~ParameterBinding()
   {
      report(njnr::logType::debug,
             "running ParameterBinding() Destructor");
      report(njnr::logType::debug, this->toString());

   }
