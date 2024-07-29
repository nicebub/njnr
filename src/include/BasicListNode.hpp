#ifndef SRC_INCLUDE_BASICLISTNODE_HPP_
#define SRC_INCLUDE_BASICLISTNODE_HPP_
#include <config.h>
#include <string>

namespace njnr
{
enum class eNodeType
{
    STANDARD,
    EXPR,
    P,
    STMT,
    TRANSLATION_UNIT,  // functions or variable declarations
    TYPE,
    IDENTIFER,
    CHARCONSTANT,
    INTCONSTANT,
    FLOATCONSTANT,
    STRCONSTANT,
};

class BasicListNode
{
public:
    BasicListNode(): nodeType{njnr::eNodeType::STANDARD} {};
    explicit BasicListNode(eNodeType t);
    virtual ~BasicListNode() = 0;
    eNodeType get_nodeType() const;
    void set_nodeType(eNodeType);
    const std::string toString() const;

private:
    eNodeType nodeType;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_BASICLISTNODE_HPP_
