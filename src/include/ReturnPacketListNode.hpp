#ifndef SRC_INCLUDE_RETURNPACKETLISTNODE_HPP_
#define SRC_INCLUDE_RETURNPACKETLISTNODE_HPP_
#include <config.h>
#include <string>
#include <memory>

#include "BasicListNode.hpp"
#include "ReturnPacket.hpp"

namespace njnr
{
class ReturnPacketListNode : public BasicListNode
{
public:
    ReturnPacketListNode();
    explicit ReturnPacketListNode(std::shared_ptr<ReturnPacket> expr);
    virtual ~ReturnPacketListNode();
    ReturnPacketListNode(const ReturnPacketListNode& in);
    virtual ReturnPacketListNode& operator=(const ReturnPacketListNode& in);
    const std::string toString() const;
    std::shared_ptr<ReturnPacket> getexpr(void);
private:
    std::shared_ptr<ReturnPacket> expr;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_RETURNPACKETLISTNODE_HPP_
