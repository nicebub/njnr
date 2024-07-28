#include <config.h>
#include <string>

#include "type.hpp"
#include "List.hpp"
#include "ParameterBinding.hpp"

namespace njnr
{
   const std::string funcheadertype::toString() const
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
   funcheadertype::~funcheadertype()
   {
      report(njnr::logType::debug,
             "running funcheadertype() Destructor");
      paramlist = nullptr;
   }
}  // namespace njnr
