#include <config.h>
#include <string>
#include <istream>

#include "lex.hpp"
#include "location.hh"
#include "compiler.hpp"

using njnr::njnrLexer;

namespace njnr
{
   //  njnrLexer::njnrLexer() : string_buf{}, yylval{nullptr}, loc{new njnrParser::location_type()}, compiler() {}
   njnrLexer::~njnrLexer()
   {
       delete loc;
       loc = nullptr;
   }

   njnrLexer::njnrLexer(std::istream* in,
                        Compiler& compiler) : yyFlexLexer(in),
                                              compiler{compiler}
   {
       loc = new njnrParser::location_type();
       string_buf = "";
   }
}  // namespace njnr
