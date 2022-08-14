#ifndef _SYMTAB_H
#define _SYMTAB_H

#include <search.h>
#include <cstdio>
#include <map>
#include <deque>

#include "list.hpp"
#include "type.hpp"
#include "compiler.hpp"
#include "cpptypes.hpp"

using namespace njnr;
namespace njnr
{
class Compiler;

class TableEntry
{
public:
    TableEntry();
    TableEntry(std::string name);
    TableEntry(std::string name, ReturnPacket* binding, btype self);
    virtual ~TableEntry();
    TableEntry(const TableEntry& in);
    TableEntry& operator=(const TableEntry& in);
    std::string getName() const;
    void setName(std::string name);
    ReturnPacket* getBinding();
    btype getself() const;
private:
    std::string name;
    ReturnPacket* binding;
    btype self;
};

class Table
{
public:
    Table();
    ~Table();
    ReturnPacket* lookup(const std::string name);
    TableEntry* lookupB(const std::string name);
    bool install(TableEntry * temp);
    bool empty() noexcept;
private:
    std::map<std::string,TableEntry*> table;
};

using stable = std::map<std::string,ReturnPacket*,btype>;

class SymbolTable
{
public:
    SymbolTable();
    SymbolTable(Compiler& compiler);
    ~SymbolTable();
    void printTree() const;
    void install(TableEntry* entry);
    ReturnPacket* lookup(const std::string name);
    TableEntry* lookupB(const std::string name);
    bool inCscope(const std::string name);
    void openscope();
    void closescope();
    //		static SymbolTable* createTree(Compiler& compiler,int Stacksize);
    void addtosymtab(type mytype, List* myList);                                //FIXME: take in a ReturnPacket* instead?
    int getleveldif(std::string name);
    TableEntry* createFunc(std::string name, type returntype, List* paramlist); //FIXME: take in a ReturnPacket* instead?
    TableEntry* createVar(std::string name, type t_type, int offset);           //FIXME: take in a ReturnPacket* instead?
    TableEntry* createParam(std::string name, type t_type, int offset);         //FIXME: take in a ReturnPacket* instead?
private:
    Compiler& compiler;
    std::deque<Table*> stack;  //Stack of Binary Search Trees
    int actualStacksize;       //used to keep size and top of stack
    int Stacksize;             //default of 100
};
}
#endif
