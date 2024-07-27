#ifndef SRC_INCLUDE_LEX_HPP_
#define SRC_INCLUDE_LEX_HPP_ 1

#include <config.h>
#include <string>
#include <istream>
#include <iostream>

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

// #include "Compiler.hpp"
#include "njnr.tab.hpp"
#include "location.hh"

namespace njnr
{
class Compiler;
class njnrLexer : public yyFlexLexer
{
public:
    njnrLexer(std::istream* in, Compiler* compiler);
    virtual int yylex(njnrParser::semantic_type* const lval,
                      njnrParser::location_type* location);

    virtual ~njnrLexer();
private:
    njnrParser::semantic_type* yylval = nullptr;
    njnrParser::location_type* loc = nullptr;
    Compiler* compiler;
    std::string string_buf{""};
};
}  // namespace njnr

#endif  // SRC_INCLUDE_LEX_HPP_
