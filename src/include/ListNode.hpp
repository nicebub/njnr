#ifndef SRC_INCLUDE_LISTNODE_HPP_
#define SRC_INCLUDE_LISTNODE_HPP_
#include <config.h>
#include <vector>
#include <string>
#include <memory>

#include "type.hpp"
#include "BasicListNode.hpp"

namespace njnr
{
class ListNode : public BasicListNode
{
public:
   ListNode();
   explicit ListNode(std::string in);
   virtual ~ListNode()
   {
      report(njnr::logType::debug,
             "running ListNode() Destructor");
      report(njnr::logType::debug, this->toString());
   }
   std::string getval() const;
   void setval(std::string in);
   const std::string toString() const;
private:
   std::string val;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_LISTNODE_HPP_
