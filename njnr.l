%{
#include "njnr.tab.h"
int lineno = 0;
%}

%option noyywrap

letter ([a-z]|[A-Z]|_)
digit [0-9]
nonzero [1-9]
ident {letter}({letter}|{digit})*
integer (0|({nonzero}{digit}*))

%%

[ \t\r] {}
\n { lineno++;}
fn { return FN; }
return { return RETURN;}
const { return CONST;}
{ident} { return IDENT;}
{integer} { return INTEGER;}

<<EOF>> {
           printf("%d lines read\n", lineno); 
           return 0;
        }
. { return yytext[0]; }

%%
