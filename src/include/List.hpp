#ifndef SRC_INCLUDE_LIST_HPP_
#define SRC_INCLUDE_LIST_HPP_
#include <config.h>
#include <vector>
#include <string>
#include <memory>

#include "type.hpp"
#include "Identifier.hpp"
#include "Constant.hpp"
#include "BasicListNode.hpp"
#include "ReturnPacket.hpp"
#include "Statement.hpp"
#include "FunctionBinding.hpp"
#include "VariableBinding.hpp"

namespace njnr
{

class List
{
public:
    List();
    virtual ~List();
    List(const List& cp);
/*    List& operator=(const List& in);*/
    void push_back(std::shared_ptr<BasicListNode> node);
    std::vector<std::shared_ptr<BasicListNode>> getlist();
    static std::shared_ptr<List> mklist(std::shared_ptr<Identifier>);
    static std::shared_ptr<List> mklist(std::shared_ptr<Constant>);
    static std::shared_ptr<List> mklist(std::string inVal);
    static std::shared_ptr<List> mklist(std::string inVal, type inType);
    static std::shared_ptr<List> mklist(std::shared_ptr<ReturnPacket> expr);
    // static List* mklist(FunctionBinding* expr);
    static std::shared_ptr<List> mklist(std::shared_ptr<FunctionBinding> expr);

    // place holder type -- needs changing
    static std::shared_ptr<List> mklist(std::shared_ptr<VariableBinding> expr);

    static std::shared_ptr<List> mklist(njnr::type type);
    static std::shared_ptr<List> mklist(std::shared_ptr<Statement> instmt);
    std::vector<std::shared_ptr<BasicListNode>>::iterator begin();
    std::vector<std::shared_ptr<BasicListNode>>::iterator end();
    bool appendList(std::string inVal);
    bool appendList(std::string inVal, njnr::type inType);
    bool appendList(std::shared_ptr<ReturnPacket> expr);
    bool appendList(std::shared_ptr<FunctionBinding> expr);

    // placeholder type -- needs changing
    bool appendList(std::shared_ptr<VariableBinding> expr);
    bool appendList(njnr::type type);
    bool appendList(std::shared_ptr<Statement> type);
    bool appendList(std::shared_ptr<Identifier>);
    bool appendList(std::shared_ptr<Constant>);
    int size() const;
    const std::string toString() const;
private:
    std::vector<std::shared_ptr<BasicListNode>> list;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_LIST_HPP_
