%{
#include "data.h"
#include "njnr.tab.h"
int lineno = 0;
%}

%option noyywrap
%option yylineno

letter  ([a-z]|[A-Z]|_)
LETTER	[A-Za-z\_]
digit   [0-9]
DIGIT	[0-9]
nonzero [1-9]
ident   {letter}({letter}|{digit})*
integer (0|({nonzero}{digit}*))

%%

[ \t\r]   { /* eat white space */ }
\n        { /* eat white space and count lines */
            lineno++; }
fn        { return FN; }
return    { return RETURN; }
try       { return TRY; }
catch     { return CATCH; }
const     { return CONST; }
{ident}   {
   yylval.u_values.svalue = (char *) strdup(yytext);
   return IDENT; 
   }
{integer} {
   yylval.u_values.ivalue = atoi(yytext);
   return INTEGER;
   }


((0|([1-9]{DIGIT}*)))(while|if|void|return|char|int|float|else|for|extern) {
									printf("illegal token: %s", yytext);
							}

((0|([1-9]{DIGIT}*))(\.{DIGIT}+))(while|if|void|return|char|int|float|else|for|extern) {
									printf("illegal token: %s",yytext);
									}

(0|([1-9]{DIGIT}*))({LETTER}({LETTER}|{DIGIT})*) { /* bad form*/
						printf("illegal token: %s", yytext);
						}

((0|([1-9]{DIGIT}*))(\.{DIGIT}{DIGIT}*))({LETTER}({LETTER}|{DIGIT})*) {/*bad form*/
							printf("illegal token: %s",yytext);
							}
0{DIGIT}+	{/* bad integer*/
				printf("illegal integer: %s", yytext);
		}



<<EOF>>   {
             printf("%d lines read\n", lineno); 
             return 0;
          }

.         { return yytext[0]; }

%%
