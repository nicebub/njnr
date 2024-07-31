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
      explicit Identifier(const std::string inName);
      explicit Identifier(const std::string inName,
                          std::string defaultVal);
      explicit Identifier(const std::string inName,
                          std::shared_ptr<Constant> constant);
      explicit Identifier(const Constant);
      virtual ~Identifier()
      {
         report(njnr::logType::debug,
                "running Identifier() Destructor");
         report(njnr::logType::debug, "name" + name);
      }
      Identifier& operator=(const Identifier& in);
      std::string getName() const;
      void setName(const std::string inName);
      const std::string toString() const;
   private:
      std::string name;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_IDENTIFIER_HPP_
