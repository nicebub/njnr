#ifndef SRC_INCLUDE_FUNCTIONHEADER_HPP_
#define SRC_INCLUDE_FUNCTIONHEADER_HPP_

#include <config.h>
#include <string>
#include <memory>

#include "type.hpp"

namespace njnr
{

class List;
/* function prototype data structure */
class FunctionHeader
{
   public:
   FunctionHeader() : name{""},
                      paramlist{nullptr},
                      returntype{njnr::type::VOID},
                      ttype{njnr::type::VOID}
                      {}

   virtual ~FunctionHeader();
   const std::string toString() const;
   std::string   name;        // fn name
   std::shared_ptr<njnr::List>   paramlist;   // list of parameters the fn accept as input
   njnr::type    returntype;  // return type(if any) of fn
   njnr::type    ttype;       // type of fn?(TBD)
};
}  // namespace njnr
#endif // SRC_INCLUDE_FUNCTIONHEADER_HPP_
