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
optional_params: | '(' Params ')'
;

function_body: '{' statements '}' {}
;

statements:  | statements statement {}
;

statement: RETURN Value {}
;

Value: | IDENT | Number {}
;

Number:  INTEGER {}
;

Params: | IDENT ',' Params {}
%%

int yyerror(char*){}
