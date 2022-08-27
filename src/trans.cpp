#include <cstdio>
#include <cstdlib>
#include <string>
#include <ostream>
#include <iostream>

#include "trans.hpp"

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


