#include <cstdio>
#include <cstdlib>
#include <string>
#include <ostream>
#include <iostream>

#include "trans.hpp"
#include "list.hpp"
#include "type.hpp"
#include "cpptypes.hpp"
#include "compiler.hpp"

using namespace njnr;

CodeGenerator::CodeGenerator() : labelcounter{1},  canGenerate{true},outfile{&std::cout},lastInstructionWasReturnf{false} {}

CodeGenerator::CodeGenerator(std::ostream& out) : labelcounter{1},  canGenerate{true}, outfile{&out},lastInstructionWasReturnf{false} {}

CodeGenerator::~CodeGenerator() {}

void CodeGenerator::setstream(std::ostream* outfile)
{
    this->outfile = outfile;
}

inline void CodeGenerator::initializelabel()
{
    labelcounter = 1;
}

int CodeGenerator::getlabel()
{
    labelcounter++;
    return (labelcounter-1);
}

void CodeGenerator::nullout(std::string& name, int length)
{
    name.clear();
}

std::string CodeGenerator::genlabelw(std::string name, int labelnum)
{
    std::string temp{"$"};
    temp += name;
    temp += std::to_string(labelnum);
    return temp;
}

void CodeGenerator::gen_label(std::string name)
{
    if(canGenerate)
    {
        *outfile << name << "\n";
        lastInstructionWasReturnf = false;
    }
}

void CodeGenerator::gen_call(std::string funcname, int numargs)
{
    if(canGenerate)
    {
        *outfile << "\tcall\t" << funcname << ", " << numargs << "\n";
        lastInstructionWasReturnf = false;
    }
}

std::string CodeGenerator::concat(std::string char1, std::string char2)
{
    return char1 + char2;
}
bool CodeGenerator::canGenerateCode() const noexcept
{
    return canGenerate;
}
void CodeGenerator::stop() noexcept
{
    canGenerate = false;
}
void CodeGenerator::start() noexcept
{
    canGenerate = true;
}

void CodeGenerator::generateFunction(Funcb* f)
{
   if(nullptr != f)
   {
      *outfile << Compiler::getStringFromType(f->getreturntype());
      *outfile << " ";
      *outfile << f->getfuncheader()->name + "()\n{\n}\n";
   }
   else
   {
      std::cerr << "NULL argument given: generateFunction\n";
   }
}
void CodeGenerator::generateTranslationUnit(njnr::TranslationUnitListNode* tn)
{
    if(nullptr != tn)
    {
        switch(tn->get_trans_unit_type())
        {
            case njnr::trans_unit_type::FUNCTION:
               generateFunction(tn->getFunc());
               break;
            case njnr::trans_unit_type::VARDECL:
               std::cout << "not implemented yet\n";
               break;
            case njnr::trans_unit_type::INVALID:
               break;
            default:
               std::cerr << "invalid tranlation unit type\n";
               break;
        }
    }
    else
    {
        std::cerr << "Null Argument given: generateTranslationUnit\n";
    }
}
void CodeGenerator::generate(List* f)
{
    if(nullptr != f)
    {
       for(auto e : *f)
       {
        switch(e->get_nodeType())
        {
            case njnr::eNodeType::TRANSLATION_UNIT:
               generateTranslationUnit(dynamic_cast<njnr::TranslationUnitListNode*>(e));
               break;
            case njnr::eNodeType::EXPR:
            case njnr::eNodeType::P:
            case njnr::eNodeType::STANDARD:
            case njnr::eNodeType::STMT:
            case njnr::eNodeType::TYPE:
               std::cerr << "Node type should not be at this level\n";
               break;
            default:
               std::cerr << "unknown node type\n";
               break;
        }
       }
    }
    else
    {
       std::cerr << "NULL argument given: generate\n";
    }
}
