#ifndef _LEX_HPP
#define _LEX_HPP 1

#include <string>
#include <istream>
#include <iostream>

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

//#include "compiler.hpp"
#include "njnr.tab.hpp"
#include "location.hh"
namespace njnr
{
class Compiler;
class njnrLexer : public yyFlexLexer
{
public:
    njnrLexer(std::istream* in, Compiler& compiler);
    virtual int yylex(njnrParser::semantic_type* const lval,
                      njnrParser::location_type* location);

    virtual ~njnrLexer();
private:
    njnrParser::semantic_type* yylval = nullptr;
    njnrParser::location_type* loc = nullptr;
    Compiler& compiler;
    std::string string_buf{""};
};
}

#endif