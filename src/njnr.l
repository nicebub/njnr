/* we want to use c++ not c */
%option c++
/* directly include the code between '%{' and '%}' into the generated lexer */
%{
#include <cstdint>

#include "debug.hpp"
#include "type.hpp"
#include "cpptypes.hpp"
#include "lex.hpp"
#include "list.hpp"
#include "symbol_table_entry.hpp"
#include "symbol_table.hpp"
#include "symbol_table_stack.hpp"
#include "data.hpp"

/* we redefine our declaration for the lexer as we changed it */
#undef YY_DECL
#define YY_DECL int njnrLexer::yylex(njnrParser::semantic_type* const lval, njnrParser::location_type* location)
/* change user action */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng); yylval = lval;

#include "njnr.tab.hpp"
#include "compiler.hpp"

/* we use our namespace */
using namespace njnr;
using token = njnrParser::token;

%}

%option noyywrap
%option stack
%option yylineno
%option yyclass="njnrLexer"

%s initial
%x astring
%x comment

DIGIT          [0-9]
LETTER         [A-Za-z\_]
SPACE          [ ]
EOLN           \\n
PERCENT        \%
QUESTION       \?
NULLS          \\0
BEGCOM         "\/\*"
ENDCOM         "\*\/"
ELIP           "..."
EQUEQU         "=="
NEQ            "\!="
LEQ            "<="
GEQ            ">="
ADOF           "&"
PRINTABLE_CHAR [!@#$%^&*\(\)\-_=+\[\]\{\}\\|;:'",<.>/?0-9A-Za-z]

%%
<comment>{
[^*\n]*
[^*\n]*\n      ++compiler.Line_Number;
\*+[^*/\n]*
\*+[^*/\n]*\n  ++compiler.Line_Number;
{ENDCOM} {
      BEGIN(INITIAL);}
<<EOF>> {
   compiler.error("eof terminated comment","");
   BEGIN(INITIAL);
   }
}

<astring>{

\" {
   BEGIN(INITIAL);
   yylval->emplace<njnr::StrConstant>() = string_buf;
   return(token::StrConstant);
   }

\n {
   BEGIN(INITIAL);
   ++compiler.Line_Number;
   compiler.error("unterminated string constant","");
   }

\\n {
       string_buf += "\\n";
    }
\\\" {
       string_buf += "\\\"";
     }

\\[^n\\\"] {
             int c;
             BEGIN(INITIAL);
             compiler.error("illegal character:%s in string",yytext);
             while(((c = yyinput()) != '\"') && (c != EOF))
           {
               ;
             }
             if(c == EOF)
           {
               compiler.error("eof terminated string","");
             }
          }

((\\\\{SPACE}+)*|[&@$\%^/,.+'-\[\]{}();~`|=#\!:<>]*|{LETTER}|{DIGIT}|{PERCENT}|{SPACE}|{BEGCOM}|{ENDCOM}|{QUESTION})* {
      char *yptr = yytext;
      while((*yptr != (int)NULL) && (*yptr))
      {
          string_buf += *yptr++;
      }
   }

<<EOF>> {
          compiler.error("eof terminated string","");
          BEGIN(INITIAL);
       }
}
fn {
   return token::fnt;
}
void {/*keyword void*/
       return token::voidt;
    }

if {/* keyword if*/
      return token::ift;
   }

return {/* keyword return*/
         return token::returnt;
       }

else {/* keyword else*/
       return token::elset;
    }

while {/*keyword while*/
        return token::whilet;
      }

int { /*keyword int*/
      return token::intt;
    }

float {/* keyword float*/
        return token::floatt;
      }

char { /* keyword char*/
        return token::chart;
    }

let {
   return token::lett;
}
{GEQ} {
         return token::geq;
     }

{LEQ} {
        return token::leq;
      }

{NEQ} {
         return token::neq;
      }

{EQUEQU} {
            return token::equequ;
        }

{ADOF} {
          return token::adof;
      }

{BEGCOM} {
            BEGIN(comment);
        }

{LETTER}({LETTER}|{DIGIT})*  { /* identifier*/
   std::string tempstr(yytext);
   yylval->emplace<njnr::Identifier>() = Identifier{tempstr};
   return(token::Ident);
                             }

((0|([1-9]{DIGIT}*)))(while|if|void|return|char|int|float|else|for|extern) {
                           compiler.error("illegal token: %s", yytext);
                     }

((0|([1-9]{DIGIT}*))(\.{DIGIT}+))(while|if|void|return|char|int|float|else|for|extern) {
                           compiler.error("illegal token: %s",yytext);
                           }

(0|([1-9]{DIGIT}*))({LETTER}({LETTER}|{DIGIT})*) { /* bad form*/
                  compiler.error("illegal token: %s", yytext);
                  }

((0|([1-9]{DIGIT}*))(\.{DIGIT}{DIGIT}*))({LETTER}({LETTER}|{DIGIT})*) {/*bad form*/
                     compiler.error("illegal token: %s",yytext);
                     }

(0|([1-9]{DIGIT}*))\.{DIGIT}{DIGIT}* {/*float*/
   yylval->emplace<njnr::FloatConstant>() = std::atof(yytext);
   return(token::FloatConstant);
                                 }

0{DIGIT}+\.{DIGIT}+    { /* bad float*/
      compiler.error("illegal float: %s",yytext);
                     }

0{DIGIT}+  { /* bad integer*/
    compiler.error("illegal integer: %s", yytext);
           }

(0|([1-9]{DIGIT}*))     { /*integer constant*/
   yylval = lval;
   yylval->emplace<njnr::IntConstant>() = std::atoi(yytext);
   return(token::IntConstant);
                        }

{ELIP} {
          return token::elip;
       }

\" {
      string_buf.clear();
      BEGIN(astring);
   }

\'{LETTER}\' {
                yylval = lval;
                yylval->emplace<njnr::CharConstant>() = yytext[1];
                return(token::CharConstant);
             }
\'{PRINTABLE_CHAR}\' {
                yylval = lval;
                yylval->emplace<njnr::CharConstant>() = yytext[1];
                return(token::CharConstant);
             }
\n {
       ++compiler.Line_Number;
   }

[ \t\r]+ { /*eat up tabs, whitespace */
        }

<<EOF>> {
           return '\0';
        }

\) {
      return token::rpar;
   }

\( {
      return token::lpar;
   }

\{ {
      return token::lcbra;
   }

\} {
      return token::rcbra;
   }

\; {
      return token::semi;
   }

\, {
      return token::comma;
   }

\< {
      return token::lesst;
   }

\> {
      return token::greatt;
   }

\= {
      return token::equalt;
   }

\+ {
      return token::plus;
   }

\- {
      return token::minus;
   }

\/ {
      return token::divide;
   }
\\ {
      return token::backst;
   }
\| {
      return token::verticalbart;
   }

\_ {
      return token::underst;
   }

\$ {
      return token::dollart;
   }

\^ {
      return token::caratt;
   }

\* {
      return token::star;
   }

\# {
      return token::hasht;
   }

\@ {
      return token::att;
   }
\[ {
      return token::lbrat;
   }

\] {
      return token::rbrat;
   }

\: {
      return token::colont;
   }

\! {
      return token::exclamationt;
   }

\~ {
      return token::tildat;
   }
\` {
      return token::backtickt;
   }
\. {
      return token::periodt;
   }
\? {
      return token::questiont;
   }

.  {
      compiler.error("illegal character: %s", yytext);
      return token::illegalt;
   }

%%
