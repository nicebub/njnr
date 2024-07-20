/* we want to use c++ not c */
%option c++
/* directly include the code between '%{' and '%}' into the generated lexer */
%{
#include <config.h>
#include <cstdint>

#include "debug.hpp"
#include "lex.hpp"

/* we redefine our declaration for the lexer as we changed it */
#undef  YY_DECL
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

[^*\n]*\n      ++compiler->Line_Number;

\*+[^*/\n]*

\*+[^*/\n]*\n  ++compiler->Line_Number;

{ENDCOM} {
            BEGIN(INITIAL);
         }

<<EOF>> {
           compiler->error("eof terminated comment","");
           BEGIN(INITIAL);
        }
}

<astring>{

\" {
      BEGIN(INITIAL);
      yylval->emplace<std::string>() = string_buf;
      return(token::StrConstant);
   }

\n {
      BEGIN(INITIAL);
      ++compiler->Line_Number;
      compiler->error("unterminated string constant","");
   }

\\n {
       string_buf += "\\n";
    }
\\\" {
       string_buf += "\\\"";
     }

\\[^n\\\"]  {
               int c;
               BEGIN(INITIAL);
               compiler->error("illegal character:%s in string",yytext);
               while(((c = yyinput()) != '\"') && (c != EOF)) ;
               if(c == EOF)
               {
                  compiler->error("eof terminated string","");
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
           compiler->error("eof terminated string","");
           BEGIN(INITIAL);
        }
}

fn {
      yylval->emplace<std::string>() = "fn";
      return token::fnt;
   }
void {/* keyword void */
      yylval->emplace<std::string>() = "void";
        return token::voidt;
     }

if {/* keyword if */
      yylval->emplace<std::string>() = "if";
      return token::ift;
   }

return {/* keyword return*/
      yylval->emplace<std::string>() = "return";
          return token::returnt;
       }

else {/* keyword else*/
      yylval->emplace<std::string>() = "else";
        return token::elset;
     }

while {/*keyword while*/
      yylval->emplace<std::string>() = "while";
         return token::whilet;
      }

int { /*keyword int*/
      yylval->emplace<std::string>() = "int";
       return token::intt;
    }

float {/* keyword float*/
      yylval->emplace<std::string>() = "float";
         return token::floatt;
      }

char { /* keyword char*/
      yylval->emplace<std::string>() = "char";
        return token::chart;
     }

let {
      yylval->emplace<std::string>() = "let";
       return token::lett;
    }
{GEQ} {
      yylval->emplace<std::string>() = ">=";
         return token::geq;
      }

{LEQ} {
      yylval->emplace<std::string>() = "<=";
         return token::leq;
      }

{NEQ} {
      yylval->emplace<std::string>() = "!=";
         return token::neq;
      }

{EQUEQU} {
      yylval->emplace<std::string>() = "==";
            return token::equequ;
         }

{ADOF} {
      yylval->emplace<std::string>() = "&";
          return token::adof;
       }

{BEGCOM} {
            BEGIN(comment);
         }

{LETTER}({LETTER}|{DIGIT})*  { /* identifier */
                                yylval->emplace<std::string>() = yytext;
                                return(token::Ident);
                             }

((0|([1-9]{DIGIT}*)))(while|if|void|return|char|int|float|else|for|extern) {
                           compiler->error("illegal token: %s", yytext);
                     }

((0|([1-9]{DIGIT}*))(\.{DIGIT}+))(while|if|void|return|char|int|float|else|for|extern) {
                           compiler->error("illegal token: %s",yytext);
                           }

(0|([1-9]{DIGIT}*))({LETTER}({LETTER}|{DIGIT})*) { /* bad form*/
                  compiler->error("illegal token: %s", yytext);
                  }

((0|([1-9]{DIGIT}*))(\.{DIGIT}{DIGIT}*))({LETTER}({LETTER}|{DIGIT})*) {/*bad form*/
                     compiler->error("illegal token: %s",yytext);
                     }

(0|([1-9]{DIGIT}*))\.{DIGIT}{DIGIT}* {/*float*/
                                        yylval->emplace<std::string>() = yytext;
                                        return(token::FloatConstant);
                                     }

0{DIGIT}+\.{DIGIT}+    { /* bad float*/
                          compiler->error("illegal float: %s",yytext);
                       }

0{DIGIT}+  { /* bad integer*/
              compiler->error("illegal integer: %s", yytext);
           }

(0|([1-9]{DIGIT}*))     { /*integer constant */
                           yylval->emplace<std::string>() = yytext;
                           return(token::IntConstant);
                        }

{ELIP} {
          return token::elip;
       }

\" {
      string_buf.clear();
      BEGIN(astring);
   }

\'{LETTER}|\' {
                yylval->emplace<std::string>() = std::to_string(yytext[1]);
                return(token::CharConstant);
             }
\'{PRINTABLE_CHAR}\' {
                        yylval->emplace<std::string>() = std::to_string(yytext[1]);
                        return(token::CharConstant);
                     }
\n {
      ++compiler->Line_Number;
   }

[ \t\r]+ { /*eat up tabs, whitespace */}

<<EOF>> {
           return '\0';
        }

\) {
      yylval->emplace<std::string>() = ")";
      return token::rpar;
   }

\( {
      yylval->emplace<std::string>() = "(";
      return token::lpar;
   }

\{ {
      yylval->emplace<std::string>() = "{";
      return token::lcbra;
   }

\} {
      yylval->emplace<std::string>() = "}";
      return token::rcbra;
   }

\; {
      yylval->emplace<std::string>() = ";";
      return token::semi;
   }

\, {
      yylval->emplace<std::string>() = ",";
      return token::comma;
   }

\< {
      yylval->emplace<std::string>() = "<";
      return token::lesst;
   }

\> {
      yylval->emplace<std::string>() = ">";
      return token::greatt;
   }

\= {
      yylval->emplace<std::string>() = "=";
      return token::equalt;
   }

\+ {
      yylval->emplace<std::string>() = "+";
      return token::plus;
   }

\- {
      yylval->emplace<std::string>() = "-";
      return token::minus;
   }

\/ {
      yylval->emplace<std::string>() = "/";
      return token::divide;
   }
\\ {
      yylval->emplace<std::string>() = "\\";
      return token::backst;
   }
\| {
      yylval->emplace<std::string>() = "|";
      return token::verticalbart;
   }

\\\_ {
      yylval->emplace<std::string>() = "_";
      return token::underst;
   }

\$ {
      yylval->emplace<std::string>() = "$";
      return token::dollart;
   }

\^ {
      yylval->emplace<std::string>() = "^";
      return token::caratt;
   }

\* {
      yylval->emplace<std::string>() = "*";
      return token::star;
   }

\# {
      yylval->emplace<std::string>() = "#";
      return token::hasht;
   }

\@ {
      yylval->emplace<std::string>() = "@";
      return token::att;
   }
\[ {
      yylval->emplace<std::string>() = "[";
      return token::lbrat;
   }

\] {
      yylval->emplace<std::string>() = "]";
      return token::rbrat;
   }

\: {
      yylval->emplace<std::string>() = ":";
      return token::colont;
   }

\! {
      yylval->emplace<std::string>() = "!";
      return token::exclamationt;
   }

\~ {
      yylval->emplace<std::string>() = "~";
      return token::tildat;
   }
\` {
      yylval->emplace<std::string>() = "`";
      return token::backtickt;
   }
\. {
      yylval->emplace<std::string>() = ".";
      return token::periodt;
   }
\? {
      yylval->emplace<std::string>() = "?";
      return token::questiont;
   }

.  {
      compiler->error("illegal character: %s", yytext);
      return token::illegalt;
   }

%%
