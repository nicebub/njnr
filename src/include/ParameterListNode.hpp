#ifndef SRC_INCLUDE_PARAMETERLISTNODE_HPP_
#define SRC_INCLUDE_PARAMETERLISTNODE_HPP_
#include <config.h>
#include <string>

#include "type.hpp"
#include "ListNode.hpp"

namespace njnr
{
class ParameterListNode : public ListNode
{
public:
   ParameterListNode();
   ParameterListNode(std::string, njnr::type);
   virtual ~ParameterListNode()
   {
      report(njnr::logType::debug,
             "running ParameterListNode() Destructor");
      report(njnr::logType::debug, this->toString());
   }
    njnr::type gettype() const;
    void settype(njnr::type type);
    const std::string toString() const;
private:
    njnr::type type;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_PARAMETERLISTNODE_HPP_
