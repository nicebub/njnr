%{
#include <stdio.h>
#include <stdbool.h>
#include "data.h"

#define YYDEBUG 1
int yydebug = 1;
#define YYERROR_VERBOSE 1
int yyerror(char*);
extern int yylex(void);

static bool has_return_value(int curr_fn);
static void set_return_value_of_statement_to_nil(int curr_fn, int curr_statement);

%}
%define parse.trace

%token BREAK
%token CASE
%token CATCH
%token CONST
%token CONTINUE
%token DIV
%token DO
%token ELSE
%token EQEQ
%token FN
%token FOR
%token IDENT
%token IF
%token INTEGER
%token LOOP
%token MIN
%token MUL
%token NEQ
%token PLUS
%token RETURN
%token SWITCH
%token TRY
%token UNTIL
%token WHILE


%start starter

%%

starter: start {YYACCEPT;}
;

start: translation_unit {printf("found start symbol\n");}
;


translation_unit: function { printf("found 1 function\n");}
                | translation_unit function { printf("found another function\n");}
                | translation_unit error { printf("unexpected token between translation units\n");}
;

function: function_header function_body {printf("full function read\n");}
;

function_header: FN IDENT optional_params {
   printf("found full function header....processing\n");
   printf("function name: %s\n", $2.u_values.svalue);
   printf("Checking for optional parameters....\n");

}
;

optional_params: /* empty */  { $$.u_values.bvalue = false;}
              | '(' Params ')' { $$ = $2; $$.u_values.bvalue = true;}
;

function_body: '{' statements '}' { printf("matched a function body\n");}
;

statements: /* empty */  { printf("empty statement\n");}
             | statement statements { printf("matching statements\n");}
;

statement: '{' statements '}' 
           | return_statement { $$ = $1;}
           | ifstatement  | conditional_expression ';'  | assignment_expression ';' {}
;

assignment_expression: IDENT '=' conditional_expression | IDENT '=' ifstatement {}
;

switch_statement: SWITCH '(' conditional_expression ')' switch_body {}
;

switch_body: '{' case_statements '}' {}
;

case_statements: | case_statement case_statements {}
;

case_statement: CASE Value ':' statements {}
;

optional_semicolon: /* empty */ | ';' {}
;

return_statement: RETURN Value  optional_semicolon { 

int curr_fn = 0;
int curr_statement = 0;

$$.has_return = true;
$$.return_type = $2.return_type;
if($2.u_values.bvalue == true)
{
   if (true == has_return_value(curr_fn))
   {
      set_return_value_of_statement_to_nil(curr_fn,curr_statement);
   }
}
}
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

Value: /* empty */ {} 
       | IDENT { printf("found an identifier %s\n", $1.u_values.svalue);
                 $$ = $1;
               }
       | Number { $$ = $1;}
;

Number:  INTEGER { printf("found an integer of value: %i\n", $1.u_values.ivalue); $$ = $1;}
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

static bool has_return_value(int curr_fn)
{

}

static void set_return_value_of_statement_to_nil(int curr_fn, int curr_statement)
{

}
