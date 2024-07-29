#ifndef SRC_INCLUDE_BASEDATA_HPP_
#define SRC_INCLUDE_BASEDATA_HPP_

#include <config.h>
#include <string>

#include "type.hpp"

namespace njnr
{
class BaseData
{
   public:
      virtual ~BaseData()
      {
         report(njnr::logType::debug,
                "running BaseData() Destructor");
      }
      virtual const std::string toString() const = 0;
      virtual const bool getlval() const = 0;
      virtual void setlval(const bool in) = 0;
      virtual const njnr::type gettype() const = 0;
      virtual void settype(const njnr::type in) = 0;
      virtual const bool getnumeric() const = 0;
      virtual void setnumeric(const bool in) = 0;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_BASEDATA_HPP_
