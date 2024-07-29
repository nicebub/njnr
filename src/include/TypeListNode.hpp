#ifndef SRC_INCLUDE_TYPELISTNODE_HPP_
#define SRC_INCLUDE_TYPELISTNODE_HPP_
#include <config.h>
#include <string>

#include "type.hpp"
#include "ListNode.hpp"

namespace njnr
{
class TypeListNode : public ListNode
{
   public:
      TypeListNode();
      // need to change actual class used this was placeholder
      explicit TypeListNode(njnr::type intype);
      virtual ~TypeListNode()
      {
         report(njnr::logType::debug,
                "running TypeListNode() Destructor");
         report(njnr::logType::debug, this->toString());
      }
      njnr::type gettype() const;
      void settype(njnr::type type);
      const std::string toString() const;
   private:
      njnr::type         type;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_TYPELISTNODE_HPP_
