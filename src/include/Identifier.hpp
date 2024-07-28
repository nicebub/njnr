#ifndef SRC_INCLUDE_IDENTIFIER_HPP_
#define SRC_INCLUDE_IDENTIFIER_HPP_

#include <config.h>
#include <string>

#include "type.hpp"
#include "Constant.hpp"
#include "Identifier.hpp"

namespace njnr
{
class Identifier : public Constant
{
   public:
      Identifier();
      explicit Identifier(const std::string invalue);
      explicit Identifier(const Constant);
      virtual ~Identifier()
      {
         report(njnr::logType::debug,
                "running Identifier() Destructor");
         report(njnr::logType::debug, "value" + value);
      }
      Identifier& operator=(const Identifier& in);
      std::string getvalue() const;
      void setvalue(const std::string in);
      const std::string toString() const;
   private:
      std::string value;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_IDENTIFIER_HPP_
