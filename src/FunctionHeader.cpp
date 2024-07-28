#include <config.h>
#include <string>

#include "type.hpp"
#include "List.hpp"
#include "ParameterBinding.hpp"

namespace njnr
{
   const std::string FunctionHeader::toString() const
   {
      std::string r = "";
      r += "name: " + name + "\n";
      r += "return type: " + typeToStringMap.at(returntype) + "\n";
      r += "ttype: " +  typeToStringMap.at(ttype) + "\n";
      if (paramlist)
      {
         r += "paramlist: " + paramlist->toString();
      }
      return r;
   }
   FunctionHeader::~FunctionHeader()
   {
      report(njnr::logType::debug,
             "running FunctionHeader() Destructor");
      paramlist = nullptr;
   }
}  // namespace njnr
