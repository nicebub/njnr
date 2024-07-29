#ifndef SRC_INCLUDE_TSCONSTANTTYPE_HPP_
#define SRC_INCLUDE_TSCONSTANTTYPE_HPP_

#include <config.h>
#include <string>

#include "type.hpp"
#include "TSType.hpp"

namespace njnr
{
class TSConstantType: public TSType
{
   virtual ~TSConstantType()
   {
      report(njnr::logType::debug,
             "running TSConstantType() Destructor");
   }
   TSConstantType();
   explicit TSConstantType(std::string s);
   explicit TSConstantType(njnr::type t);
};
}  // namespace njnr
#endif  // SRC_INCLUDE_TSCONSTANTTYPE_HPP_
