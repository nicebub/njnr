#ifndef SRC_INCLUDE_STATEMENTLISTNODE_HPP_
#define SRC_INCLUDE_STATEMENTLISTNODE_HPP_
#include <config.h>
#include <string>
#include <memory>

#include "type.hpp"
#include "ListNode.hpp"
#include "Statement.hpp"

namespace njnr
{
class StmtListNode : public ListNode
{
   public:
      StmtListNode();
      explicit StmtListNode(std::shared_ptr<Statement> instmt);
      virtual ~StmtListNode()
      {
         report(njnr::logType::debug,
                "running StmtListNode() Destructor");
         report(njnr::logType::debug, this->toString());

//         stmt = nullptr;
      }
      std::shared_ptr<Statement> getstmt(void);
      void setstmt(std::shared_ptr<Statement> instmt);
      const std::string toString() const;
   private:
      std::shared_ptr<Statement>         stmt;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_STATEMENTLISTNODE_HPP_
