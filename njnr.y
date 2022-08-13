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
                | variable_declaration { printf("found variable declration\n");}
                | translation_unit function { printf("found another function\n");}
                | translation_unit variable_declaration { printf("found another variable declaration\n");}
                | translation_unit error { printf("unexpected token between translation units\n");}
;

variable_declaration: 'v' {} ;

function: function_header function_body {printf("full function read\n");}
;

function_header: FN IDENT optional_params {
   printf("found full function header....processing\n");
   printf("function name: %s\n", $2.u_values.svalue);
   printf("Checking for optional parameters....\n");

}
;

optional_params: /* empty */  { printf("empty optional params\n"); $$.u_values.bvalue = false;}
              | '(' Params ')' { $$ = $2; $$.u_values.bvalue = true; printf("Params found\n");}
;

function_body: '{' statements '}' { printf("matched a function body\n");}
;

statements: /* empty */  { printf("empty statement\n");}
             | statement statements { printf("matching statements\n");}
;

statement: '{' statements '}' {printf("statements withing '{' and '}'\n");}
           | return_statement ';' {printf("return statement found\n"); $$ = $1;}
           | conditional_expression ';' { printf("conditionl expression statement\n");}
           | assignment_expression  ';' {printf("assignment expression statement\n");}
           | ifstatement {printf("ifstatement statement\n");}
           | switch_statement {printf("switch statement statement found\n");}
;

assignment_expression: IDENT '=' conditional_expression {printf("assignment expression = condtional expression\n");}
                     | IDENT '=' ifstatement {printf("assignment expression = ifstatement\n");}
;

switch_statement: SWITCH '(' conditional_expression ')' switch_body {printf("switch statement found\n");}
;

switch_body: '{' case_statements '}' {printf("found switch_body\n");}
;

case_statements: /* empty */ {printf("empty case statements\n");}
               | case_statement case_statements {printf("case statement found\n");}
;

case_statement: CASE Value ':' statements {printf("internal case statement found\n");}
;

return_statement: 
   RETURN   {} 
 | RETURN Value   { 
printf("return statement parsing\n");
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

ifstatement: IF '(' conditional_expression ')' ifbody  optional_else {printf("if statement found\n");}
;

ifbody: '{' statements '}' {printf("if statement body and statements parsing\n");}
;

conditional_expression: paren_expression {}
         | paren_expression relop paren_expression {}
;

paren_expression: expon_expression {}
                | expon_expression mulop expon_expression {}
;

expon_expression: mul_expression add_op mul_expression {}
                | mul_expression {}
;

mul_expression: INTEGER {}
;

optional_else: /* empty */ {}
                | ELSE ifbody {}
                | ELSE ifstatement {}
;

Value: IDENT { printf("found an identifier %s\n", $1.u_values.svalue);
                 $$ = $1;
               }
       | Number { $$ = $1;}
;

Number:  INTEGER { printf("found an integer of value: %i\n", $1.u_values.ivalue); $$ = $1;}
;

Params: /* empty */ {}
         | IDENT {}
         | IDENT ',' Params {}
;

relop: EQEQ {}
     | NEQ {}
;

add_op: PLUS {}
      | MIN {}
;

mulop: MUL {}
     | DIV {}
;

%%

int yyerror(char*){}

static bool has_return_value(int curr_fn)
{

}

static void set_return_value_of_statement_to_nil(int curr_fn, int curr_statement)
{

}
