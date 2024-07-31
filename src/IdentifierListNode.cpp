#include <config.h>
#include <string>
#include <memory>

#include "type.hpp"
#include "ReturnPacketListNode.hpp"
#include "IdentifierListNode.hpp"

using njnr::ReturnPacketListNode;
using njnr::IdentListNode;
using njnr::Identifier;

IdentListNode::IdentListNode() : ReturnPacketListNode{} {}

IdentListNode::IdentListNode(std::shared_ptr<Identifier> inIdent) :
                             ReturnPacketListNode{},
                             ident{inIdent} {}

std::shared_ptr<Identifier> IdentListNode::getident(void) { return ident; }
void IdentListNode::setident(std::shared_ptr<Identifier> instmt) { ident = instmt; }
const std::string IdentListNode::toString() const { return ident->getName(); }
//std::shared_ptr<Identifier>         ident;
