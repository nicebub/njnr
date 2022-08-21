#include <string>
#include <cstdio>
#include <cstdlib>
#include <search.h>
#include <cassert>

#include "debug.hpp"
#include "symtab.hpp"
#include "type.hpp"
#include "list.hpp"
#include "data.hpp"
#include "cpptypes.hpp"


using namespace njnr;
namespace njnr {

TableEntry::TableEntry() : TableEntry{""} {}
TableEntry::TableEntry(std::string name) :name{name}, binding{nullptr}, self{btype::FUNC} {}
TableEntry::TableEntry(std::string name, ReturnPacket* binding, btype self) : name{name}, binding{binding}, self{self} {}
TableEntry::~TableEntry() {
    if(binding) {
//		delete binding;
// delete binding depeinding on FUNC, VAR, PARAM, need to create classes for those with destructors to make
//	this work better
    }
}
TableEntry::TableEntry(const TableEntry& in) : name{in.name}, binding{in.binding}, self{in.self} {}

TableEntry& TableEntry::operator=(const TableEntry& in) {
    if(this != &in) {
        name = in.name;
        binding = in.binding;
        self = in.self;
    }
    return *this;
}
void TableEntry::setName(std::string inName) {
    name = inName;
}
std::string TableEntry::getName() const {
    return name;
}
ReturnPacket* TableEntry::getBinding() {
    return binding;
}

btype TableEntry::getself() const {
    return self;
}


Table::Table() : table{} {}
Table::~Table() {
    /*
        for(auto& element : table){
    		//decompose the element and delete the pointer data
    //		delete element;
    	}
    */
}
ReturnPacket* Table::lookup(const std::string name) {
    auto result{table.find(name)};
    if(result != table.end()) {
        return result->second->getBinding();
    }
    return nullptr;
}
TableEntry* Table::lookupB(const std::string name) {
    try {
        auto result{table.at(name)};
        return result;
    }
    catch(std::out_of_range& e) {
        // not in table
        debugprint("caught out of range\n","");
    }
    return nullptr;
}
bool Table::empty() noexcept
{
    return table.empty();
}

bool Table::install(TableEntry* entry)
{
    bool answer;
    try
    {
        table.at(entry->getName());
        std::cerr << "error: symbol already declared in current scope" << std::endl;
        answer = false;
    }
    catch(std::out_of_range& e)
    {
        debugprint("caught out of range\n","");
        table[entry->getName()] = entry;
        answer = true;
    }
    debugprint("through install function of symbol table. Printing symbol table tree\n","");
//	printTree(symtab);

    return answer;
}

SymbolTable::SymbolTable(Compiler& compiler) : compiler{compiler}, stack{}, actualStacksize(1), Stacksize(1) {
    openscope();

}
SymbolTable::~SymbolTable() {
    /*
    for(auto element : stack){
    	delete element;
    	element = nullptr;
    	}*/
}

void SymbolTable::openscope() {
    debugprint("Opening new Scope\n","");
    stack.push_back(new Table{});
    actualStacksize += 1;
    compiler.offset_counter=5;
}

void SymbolTable::closescope() {
    if(stack.size() == 1)
        compiler.error("Cannot close Global scope","");
    else {
        debugprint("Closing Scope\n","");

        if(!stack.empty()) {
            stack.pop_back();
            actualStacksize -= 1;
        }
    }
}

ReturnPacket* SymbolTable::lookup(const std::string name) {
    if(!name.empty()) {
//		for(auto &it : stack){
        for(auto it = stack.rbegin(); it != stack.rend(); it++) {
            auto *result = (*it)->lookup(name);
            if(result != nullptr) {
                return result;
            }
        }
        return nullptr;
    }
    else {
        compiler.error("cannot lookup variable without a name","");
        return nullptr;
    }
}

void SymbolTable::install(TableEntry* temp)
{
    Table* locatedTable{stack.back()};
    if(!locatedTable->install(temp))
    {
        compiler.error("symbol already declared in current scope","");
    }

    debugprint("through install function of symbol table. Printing symbol table tree\n","");
#ifdef DEBUG
//	printTree(symtab);
#endif
}

#ifdef DEBUG
void njnr::SymbolTable::printTree() const
{
}
#endif
/*
SymbolTable* SymbolTable::createTree(Compiler& compiler,int Stacksize){
	SymbolTable *temp{new SymbolTable{compiler}};
	temp->actualStacksize=1;
	temp->Stacksize = Stacksize;
	return temp;
}
*/
TableEntry* SymbolTable::createFunc(std::string name, type returntype, List* paramlist) {
    TableEntry* temp{nullptr};
    bool elip{false};

    if( name.empty() ) {
        compiler.error("name not found\n","");
    }
    else {
        Funcb* tBinding{new Funcb{returntype}};
        tBinding->setvalue(name);

        if(paramlist!=nullptr ) {
            tBinding->setnum_param(paramlist->size());
        }
        if(tBinding->getnum_param() >0) {
            for(auto &element : *paramlist) {
                PListNode* n_element{dynamic_cast<PListNode*>(element)};
                tBinding->getparam_type().push_back(n_element->gettype());
                if( n_element->getval() == "..." ) {
                    elip = true;
                }
                else {
                    elip=false;
                }
            }
            if(elip == true) {
                tBinding->setactual_num(tBinding->getnum_param());
                tBinding->setnum_param(-1);
            }
        }
        temp = new TableEntry{name,tBinding,btype::FUNC};
    }
    return temp;
}

TableEntry* SymbolTable::createVar(std::string name, type t_type, int offset) {
    Varb* tBindingV{new Varb{}};

    tBindingV->settype(t_type);
    tBindingV->setoffset(offset);
    tBindingV->setvalue(name);

    TableEntry* result{new TableEntry{name,tBindingV,btype::VAR}};
    return result;
}

TableEntry* SymbolTable::createParam(std::string name, type t_type, int offset) {
    Paramb* tBindingP{new Paramb{}};

    tBindingP->settype(t_type);
    tBindingP->setoffset(offset);

    TableEntry* temp{new TableEntry{name,tBindingP,btype::PARAM}};
    return temp;
}

void SymbolTable::addtosymtab(type mytype, List* myList)
{
    assert(myList != nullptr);
    if(myList !=nullptr)
    {
        for(auto& element : *myList)
        {
            TableEntry* temp{nullptr};
            ListNode* n_element{dynamic_cast<ListNode*>(element)};
            temp= createVar(n_element->getval(), mytype, compiler.offset_counter);
            if(mytype != njnr::type::VOID)
            {
                compiler.offset_counter++;
            }
            if( stack.size() == 1)
            {
                compiler.globalcount++;
            }
            install(temp);
        }
    }
    else
    {
        compiler.error("List given was nullptr","");
    }
}

TableEntry * SymbolTable::lookupB(const std::string name) {
    if( name.empty() ) {
        compiler.error("cannot lookup variable without a name","");
    }
    else {
//		for(auto *it : stack){
        for(auto it = stack.rbegin(); it != stack.rend(); it++) {
            auto result{ (*it)->lookupB(name) };
            if(result != nullptr) {
                return dynamic_cast<TableEntry*>(result);
            }
        }
    }
    return nullptr;
}

bool SymbolTable::inCscope(const std::string name) {
    if(! name.empty() ) {
        auto table{stack.rbegin()};
        if( ! (*table)->empty() ) {
            auto *result{ (*table)->lookup(name)};
            if(result != nullptr) {
                return true;
            }
        }
    }
    return false;
}

int SymbolTable::getleveldif(std::string name) {
//	TableEntry ** found;
//	found = nullptr;
    if(!name.empty()) {
        int i{0};
//		for(auto *it : stack){
        for(auto it = stack.rbegin(); it != stack.rend(); it++) {
            auto result = (*it)->lookup(name);
            if(result != nullptr) {
                return i;
            }
            ++i;
        }
    }
    return -1;
}
}
