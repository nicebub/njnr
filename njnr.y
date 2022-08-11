%{
#include <stdio.h>
#define YYDEBUG 0
int yyerror(char*);
extern int yylex(void);
%}

%token FN
%token RETURN
%token CONST
%token INTEGER
%token IDENT
%token IF
%token ELSE
%token PLUS
%token MIN
%token MUL
%token DIV
%token EQEQ
%token NEQ

%start starter

%%

starter: start {YYACCEPT;}
;

start: functions {}
;

functions: | function {}
;

function: function_header function_body {}
;

function_header: FN IDENT optional_params { }
;

optional_params: /* empty */ | '(' Params ')'
;

function_body: '{' statements '}' {}
;

statements: /* empty */ | statements statement {}
;

statement: return_statement | ifstatement {}
;

return_statement: RETURN Value {}
;

ifstatement: IF '(' conditional_expression ')' ifbody  optional_else {}
;

ifbody: '{' statements '}' {}
;

conditional_expression: paren_expression | paren_expression relop paren_expression {}
;

paren_expression: expon_expression | expon_expression mulop expon_expression {}
;

expon_expression: mul_expression add_op mul_expression | mul_expression {}
;

mul_expression: INTEGER {}
;

optional_else: /* empty */ | ELSE ifbody | ELSE ifstatement {}
;

Value: /* empty */ | IDENT | Number {}
;

Number:  INTEGER {}
;

Params: /* empty */ | IDENT ',' Params {}
;

relop: EQEQ | NEQ {}
;

add_op: PLUS | MIN {}
;

mulop: MUL | DIV {}
;

%%

int yyerror(char*){}
