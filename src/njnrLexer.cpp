#include <config.h>
#include <string>
#include <istream>

#include "njnrLexer.hpp"
#include "location.hh"
#include "Compiler.hpp"

using njnr::njnrLexer;

namespace njnr
{
   //  njnrLexer::njnrLexer() : string_buf{}, yylval{nullptr},
   //              loc{new njnrParser::location_type()}, compiler() {}
   njnrLexer::~njnrLexer()
   {
       report(njnr::logType::debug, "running njnrLexer() Destructor");
       delete loc;
       loc = nullptr;
   }

   njnrLexer::njnrLexer(std::istream* in,
                        Compiler* compiler) : yyFlexLexer(in),
                                              compiler{compiler}
   {
       loc = new njnrParser::location_type();
       string_buf = "";
   }
}  // namespace njnr
