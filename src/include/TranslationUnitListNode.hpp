#ifndef SRC_INCLUDE_TRANSLATIONUNITLISTNODE_HPP_
#define SRC_INCLUDE_TRANSLATIONUNITLISTNODE_HPP_
#include <config.h>
#include <string>
#include <memory>

#include "type.hpp"
#include "ListNode.hpp"
#include "ReturnPacket.hpp"
#include "FunctionBinding.hpp"
#include "VariableBinding.hpp"

namespace njnr
{
class TranslationUnitListNode : public ListNode
{
   public:
      TranslationUnitListNode();
      explicit TranslationUnitListNode(std::shared_ptr<FunctionBinding> infunc);
      // need to change actual class used this was placeholder
      explicit TranslationUnitListNode(std::shared_ptr<VariableBinding> invardecl);
      virtual ~TranslationUnitListNode()
      {
         report(njnr::logType::debug,
                "running TranslationUnitListNode() Destructor");
         report(njnr::logType::debug, this->toString());

//         unit = nullptr;
      }
      const std::string toString() const;
      const njnr::trans_unit_type get_trans_unit_type(void) const;
      const std::shared_ptr<VariableBinding> getVarDecl(void) const;
      std::shared_ptr<FunctionBinding> getFunc(void) const;
   private:
      std::shared_ptr<ReturnPacket>         unit;
      trans_unit_type                 trans_type;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_TRANSLATIONUNITLISTNODE_HPP_
