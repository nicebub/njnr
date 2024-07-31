#ifndef SRC_INCLUDE_IDENTIFIERLISTNODE_HPP_
#define SRC_INCLUDE_IDENTIFIERLISTNODE_HPP_
#include <config.h>
#include <string>
#include <memory>

#include "type.hpp"
#include "ReturnPacketListNode.hpp"
#include "Identifier.hpp"

namespace njnr
{
class IdentListNode : public ReturnPacketListNode
{
   public:
      IdentListNode();
      explicit IdentListNode(std::shared_ptr<Identifier> inident);
      virtual ~IdentListNode()
      {
         report(njnr::logType::debug, "running IdentListNode() Destructor");
         report(njnr::logType::debug, this->toString());

//         ident = nullptr;
      }
      std::shared_ptr<Identifier> getident(void);
      void setident(std::shared_ptr<Identifier> instmt);
      const std::string toString() const;
   private:
      std::shared_ptr<Identifier>         ident;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_IDENTIFIERLISTNODE_HPP_
