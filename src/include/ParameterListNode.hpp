#ifndef SRC_INCLUDE_PARAMETERLISTNODE_HPP_
#define SRC_INCLUDE_PARAMETERLISTNODE_HPP_
#include <config.h>
#include <string>

#include "type.hpp"
#include "ListNode.hpp"

namespace njnr
{
class PListNode : public ListNode
{
public:
   PListNode();
   PListNode(std::string, njnr::type);
   virtual ~PListNode()
   {
      report(njnr::logType::debug,
             "running PListNode() Destructor");
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
