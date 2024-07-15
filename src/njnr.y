%{
#include <config.h>
#include <cstdio>
#include <string>

#include "debug.hpp"
#include "symbol_table_stackX.hpp"

/*
#include "type.hpp"
#include "list.hpp"
#include "data.hpp
#include "trans.hpp"
#include "lex.hpp"
#include "cpptypes.hpp"
*/

using namespace njnr;

#define YYDEBUG 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYERROR_VERBOSE 1

#include "compiler.hpp"

int yyerror(std::string err,Compiler& compiler);
%}

%verbose
//%define parse.trace

%require "3.7"
%expect 1
%skeleton "lalr1.cc"

//%define parse.assert

%defines
%locations
%define api.value.type variant
//%define api.token.constructor
%define api.token.raw

%define api.namespace{njnr}
%define api.parser.class {njnrParser}

%code requires {
    namespace njnr
    {
       class Compiler;
       class S_TableEntryX;
    }
    #include <config.h>
    #include "cpptypes.hpp"
    #include "list.hpp"
    #include "type.hpp"
    #include "operator.hpp"
    using namespace njnr;

    # if !defined __EXCEPTIONS
    #  define YY_EXCEPTIONS 0
    # else
    #  define YY_EXCEPTIONS 1
    # endif
}

%parse-param{ Compiler& compiler }
//%lex-param{ njnrParser::semantic_type* const lval }
//%lex-param{ njnrParser::location_type* loc }
%code{
    #undef yylex
    #define yylex compiler.lexer.yylex

    void njnr::njnrParser::error(njnr::location const & loc, const std::string & message)
    {
       std::cout << "at " << loc << " : " << message << std::endl;
    }
} 


%token <std::string> Ident "Identifier"
%token <std::string> IntConstant "IntConstant"
%token <std::string> FloatConstant "FloatConstant"
%token <std::string> StrConstant "StrConstant"
%token <std::string> CharConstant "CharConstant"
%token voidt
%token intt
%token floatt
%token chart
%token ift
%token whilet
%token returnt
%token elset
%token equequ
%token neq
%token leq
%token geq
%token adof
%token elip
%token lpar
%token rpar
%token lcbra
%token rcbra
%token semi
%token comma
%token lesst
%token greatt
%token equalt
%token plus
%token minus
%token divide
%token star
%token uminus
%token fnt
%token tryt
%token catcht
%token loopt
%token caset
%token breakt
%token continuet
%token untilt
%token dot
%token lett
%token vart
%token foreacht
%token fort
%token foreachint

%token equgreatt
%token arrowt
%token defaultt
%token illegalt
%token backst
%token verticalbart
%token underst
%token dollart
%token caratt
%token colont
%token exclamationt
%token hasht
%token att
%token lbrat
%token rbrat
%token tildat
%token backtickt
%token periodt
%token questiont

%right equequ neq
%right lesst greatt
%left leq geq
%left plus minus
%left divide star
%right adof
%right uminus


%type <List*> identlist
%type <Operator*> relop
%type <Operator*> mulop
%type <Operator*> addop
%type <Operator*> eqop

%type <int> whilet ift elset
%type <int> intt
%type <float> floatt
%type <int> chart voidt adof elip lpar rpar lcbra rcbra semi comma equalt
%type <reltype> lesst greatt leq geq
%type <reltype> plus minus
%type <reltype> equequ neq
%type <reltype> divide star
%type <int> uminus
%type <List*> translation_unit_part_list translation_unit funcbody_internal funcbody
%type <Funcb*> func variabledecl
%nterm <List*> paramdeflist paramdef
%nterm <funcheadertype*> funcheader
%nterm <ReturnPacket*> expr
%nterm <Statement*> stmt
//%nterm <ReturnPacket*> stmtlist
%nterm <ReturnPacket*> ifexprstmt
%nterm <Constant*> constant
%nterm <ReturnPacket*> factor function_call func_call_with_params name_and_params
%nterm <ReturnPacket*> TERM
%nterm <ReturnPacket*> simpleexpr
%nterm <ReturnPacket*> relexpr
%nterm <ReturnPacket*> equalexpr

%start starter

%%
starter: translation_unit {
                          }
;

translation_unit: translation_unit_part_list {
                                                compiler.setfinished($1);
                                             }
;

translation_unit_part_list: func { $$ = List::mklist($1); }
                          | variabledecl {
//                                          $$ = List::mklist($1);
                                         }
                          | translation_unit_part_list func { $$ = $1->appendList($2); }
                          | translation_unit_part_list variabledecl {
//                                                                     $$ = $1->appendList($2);
                                                                    }
;

func: funcheader funcbody {
                             $$ = compiler.create_full_function($1, $2);
                          }
;

funcheader: fnt Ident lpar paramdef rpar {
                                            $$ = compiler.funcheader_returntype_ident_lpar_paramdef_rpar_helper(Identifier{$2}, $<List*>4, njnr::type::VOID);
                                         }
          | fnt Ident lpar rpar {
                                   $$ = compiler.funcheader_returntype_ident_lpar_paramdef_rpar_helper(Identifier{$2}, nullptr, njnr::type::VOID);
                                }
          | fnt Ident {
                         $$ = compiler.funcheader_returntype_ident_lpar_paramdef_rpar_helper(Identifier{$2}, nullptr, njnr::type::VOID);
                      }
          | fnt error rpar {
                              yyerrok;
                              $$ = compiler.funcheader_returntype_ident_lpar_paramdef_rpar_helper(njnr::Identifier{""}, List::mklist(std::string{"error"}, type::VOID),  njnr::type::VOID);
                              compiler.error("(expecting lpar before rpar in function)","");
                           }
          | fnt Ident lpar error rpar {
                                         yyerrok;
                                         $$ = compiler.funcheader_returntype_ident_lpar_paramdef_rpar_helper(Identifier{$2}, List::mklist(std::string{"error"}, type::VOID),  njnr::type::VOID);
                                         compiler.error("(unexpected token after lpar and before rpar in function)","");
                                      }
;

paramdef: paramdeflist {$$ = $1;}
        | paramdeflist comma elip {
                                     $$ = $1->appendList("...", type::VOID);
                                  }
        | paramdeflist error rpar {
                                     yyerrok;
                                     compiler.error("(unexpected token before rpar in parameter definition)","");
                                     delete $1;
                                     $1 = nullptr;
                                  }
        | paramdeflist comma error rpar {
                                           yyerrok;
                                           compiler.error("(unexpected token before rpar in parameter definition)","");
                                           delete $1;
                                           $1 = nullptr;
                                        }
;

paramdeflist: Ident {
                       $$ = List::mklist($1);
                       compiler.installParameterIntoSymbolTable($1, njnr::type::INT);
                    }
            | paramdeflist comma Ident {
                                          $$ = $1->appendList($3);
                                          compiler.installParameterIntoSymbolTable($3, njnr::type::INT);
                                       }
;

funcbody: lcbra funcbody_internal rcbra {
                                           $$ = $2;
                                           compiler.dealwithstmtlist($2);
                                        }
;

funcbody_internal: variabledecl {
                                   $$ = List::mklist($1);
//                                 compiler.block25_funcbody_lcbra_decls_source();
                                }
                 | stmt {
                           $$ = List::mklist($1);
//                            compiler.create_and_return_a_fn_body_statement_element($1);
                           /* compiler.block26_funcbody_lcbra_decls_source_stmtlist_rcbra(); */
                        }
                | funcbody_internal variabledecl {
                                                     compiler.block25_funcbody_lcbra_decls_source();
                                                     $$ = $1->appendList($2);
                                                  }
                 | funcbody_internal stmt {
//                                           compiler.add_statement_to_fn_body_and_return($1,$2);
                                             $$ = $1->appendList($2);
                                          }
;

variabledecl: vart identlist {
//                                compiler.symbolTable->addtosymtab(type::INT, $2);
                             }
              lett identlist {
//                               compiler.symbolTable->addtosymtab(type::INT, $2);
                             }
;

stmt:     expr semi {
                       compiler.block29_stmt_expr_semi();
                    }
        | returnt semi {
                          $$ = compiler.stmt_return_expr_semi(nullptr);
                       }
        | returnt expr semi {
                               $$ = compiler.stmt_return_expr_semi($2);
                            }

        | whilet <ReturnPacket*>{
                                   $$ = compiler.block32_stmt_while_source();
                                }
          lpar expr rpar {
                            compiler.block33_stmt_while_source_expr_semi_source_lpar_expr_rpar($2,$4);
                         }
          stmt {
                  compiler.block34_stmt_while_source_expr_semi_source_lpar_expr_rpar_source_stmt($2,$4);
               }

        | ifexprstmt elset {
                              compiler.block35_stmt_ifexprstmt_else($1);
                           }
          stmt {
                  compiler.block36_stmt_ifexprstmt_else_source_stmt($1);
               }

        | ifexprstmt {
                        compiler.block37_stmt_ifexprstmt($1);
                     }

        | lcbra funcbody_internal rcbra {
                                        }  // closescope(symbolTable);
//      | returnt error {
//                         yyerrok;
//                         compiler.error("(unexpected token after return in return stmt)","");
//                      }
        | whilet error semi {
                               yyerrok;
                               compiler.error("(unexpected token before semi in while stmt)","");
                            }
        | ift error stmt {
                            yyerrok;
                            compiler.error("(unexpected token before stmt in if stmt)","");
                         }
        | lcbra funcbody_internal error rcbra {
                                                 yyerrok;
                                                 compiler.error("(unexpected token before rcbra in stmt)","");
                                              }  // closescope(symbolTable);
;

ifexprstmt: ift lpar expr <struct Pair>{
                                            $$ = compiler.block38_ifexprstmt_if_lpar_expr_source($3);
                                         }
            rpar stmt {
                         $$ = $3; $$->m_pair = $4;
                      }
;

expr: equalexpr equalt equalexpr {
                                    $$ = compiler.block40_expr_equalexpr_equal_equalexpr(&$1, &$3);
                                 }
    | equalexpr {
                   $$ = $1;
                }
    | equalexpr equalt error {
                                yyerrok;
                                compiler.error("(unexpected token after equalt operator in expr)","");
                             }
;

equalexpr: relexpr eqop {
                           compiler.block42_equalexpr_relexpr_eqop_source(&$1);
                        }
           relexpr {
                      $$ = compiler.block43_equalexpr_relexpr_eqop_source_relexpr($2,&$1,&$4);
                   }
         | relexpr {
                      $$ = $1;
                   }
         | relexpr eqop error {
                                 yyerrok;
                                 compiler.error("(unexpected token after equality operator in expr)","");
                              }
;

relexpr: simpleexpr relop {
                             compiler.block45_relexpr_simpleexpr_relop_source(&$1);
                          }
         simpleexpr {
                       $$ = compiler.block46_relexpr_simpleexpr_relop_source_simpleexpr(&$1,$2,&$4);
                    }
       | simpleexpr {
                       $$ = $1;
                    }
       | simpleexpr relop error {
                                   yyerrok;
                                   compiler.error("(unexpected token after relational operator","");
                                }
;

simpleexpr: simpleexpr addop {
                                compiler.block48_simpleexpr_simpleexpr_addop_source(&$1);
                             }
            TERM {
                    $$ = compiler.block49_simpleexpr_simpleexpr_addop_source_term(&$1,$2,&$4);
                 }
          | TERM {
                    $$ = $1;
                 }
          | simpleexpr addop error {
                                      yyerrok;
                                      compiler.error("(unexpected token after additive operator)","");
                                   }
;

TERM: TERM mulop {
                    compiler.block51_term_term_mulop_source(&$1);
                 }
       factor {
                 $$ = compiler.block52_term_term_mulop_source_factor(&$1,$2,$4);
              }
     | factor {
                 $$ = $1;
              }
     | TERM mulop error {
                           yyerrok;
                           compiler.error("(unexpected token after multiplicative operator)","");
                        }
;

factor: constant {
                    $$ = compiler.block54_factor_constant($1);
                 }
      | Ident {
                 $$ = compiler.block55_factor_ident(Identifier{$1});
                 compiler.installVariableIntoSymbolTable($1, njnr::type::INT);
              }
      | lpar expr rpar {
                          $$ = $2;
                       }
      | addop factor %prec uminus {
                                     $$ = compiler.block57_factor_addop_factor_uminus($1,&$2);
                                  }
      | adof Ident {
                      $$ = compiler.block58_factor_adof_ident(Identifier{$2});
                   }
      | function_call {
                         $$ = $1;
                      }
      | addop error {
                       yyerrok;
                       compiler.error("(unexpected token after unary additive operator)","");
                    }
      | lpar expr error rpar {
                                yyerrok;
                                compiler.error("(unexpected token before rpar)","");
                             }
;

function_call: Ident lpar rpar {
                                  $$ = compiler.block60_function_call_ident_lpar_rpar(Identifier{$1});
                               }
             | func_call_with_params {
                                        $$ = $1;
                                     }
;

func_call_with_params: name_and_params rpar {
                                               $$ = compiler.block62_func_call_with_params_name_and_params_rpar(&$1);
                                            }
;

name_and_params: Ident lpar <ReturnPacket*>{
                                              $$ = compiler.block63_name_and_params_ident_lpar_source(Identifier{$1});
                                           }
                 exprlist {
                           //$$ = compiler.block64_name_and_params_ident_lpar_source_expr(Identifier{$1},&$3,&$4);
                          }
;
exprlist: expr comma  exprlist {
                                  //  $$ = compiler.block65_name_and_params_name_and_params_comma_expr(&$1, &$4);
                               }
          | expr {}
;


identlist: Ident {
                    $$ = List::mklist($1, njnr::type::IDENT);
                 }
         | identlist comma Ident {
                                    $$ = $1->appendList($3, njnr::type::IDENT);
                                 }
         | identlist comma error {
                                    yyerrok;
                                    compiler.error("(unexpected token after comma)","");
                                    $$ = $1;
                                 }
;

constant: StrConstant {
                          compiler.constantTable->install2($1, njnr::type::STR);
                          compiler.typeTable->install2("string", njnr::type::STR);
                          $$ = new Constant{$1, njnr::type::STR};
                      }
        | IntConstant {
                          compiler.constantTable->install2($1, njnr::type::INT);
                          compiler.typeTable->install2("int", njnr::type::INT);
                          $$ = new Constant{$1, njnr::type::INT};
                       }
        | FloatConstant {
                          compiler.constantTable->install2($1, njnr::type::FLOAT);
                          compiler.typeTable->install2("float", njnr::type::FLOAT);
                          $$ = new Constant{$1, njnr::type::FLOAT};
                        }
        | CharConstant {
                          compiler.constantTable->install2($1, njnr::type::CHAR);
                          compiler.typeTable->install2("char", njnr::type::CHAR);
                          $$ = new Constant{$1, njnr::type::CHAR};
                        }

;

addop: plus  {
               $$ = compiler.block82_relop_greatt($1, "+");
                compiler.typeTable->install2("+", njnr::type::OPERATOR);
                $$ = new Operator(nullptr);
                $$->setType(TSOperatorType("+"));
             }
     | minus {
               $$ = compiler.block82_relop_greatt($1, "-");
                compiler.typeTable->install2("-", njnr::type::OPERATOR);
                $$ = new Operator(nullptr);
                $$->setType(TSOperatorType("-"));
             }
;

mulop: star   {
               $$ = compiler.block82_relop_greatt($1, "*");
                 compiler.typeTable->install2("*", njnr::type::OPERATOR);
                 $$ = new Operator(nullptr);
                 $$->setType(TSOperatorType("*"));
              }
     | divide {
               $$ = compiler.block82_relop_greatt($1, "/");
                 compiler.typeTable->install2("/", njnr::type::OPERATOR);
                 $$ = new Operator(nullptr);
                 $$->setType(TSOperatorType("/"));
              }
;

eqop: 
      equequ {
               $$ = compiler.block82_relop_greatt($1, "==");
                compiler.typeTable->install2("==", njnr::type::OPERATOR);
                $$ = new Operator(nullptr);
                $$->setType(TSOperatorType("=="));
             }
    | neq    {
               $$ = compiler.block82_relop_greatt($1, "!=");
                compiler.typeTable->install2("!=", njnr::type::OPERATOR);
                $$ = new Operator(nullptr);
                $$->setType(TSOperatorType("!="));
             }
;

relop: 
       lesst  {
               $$ = compiler.block82_relop_greatt($1, "<");
                 compiler.typeTable->install2("<", njnr::type::OPERATOR);
                 $$ = new Operator(nullptr);
                 $$->setType(TSOperatorType("<"));
              }
     | leq    {
               $$ = compiler.block82_relop_greatt($1, "<=");
                 compiler.typeTable->install2("<=", njnr::type::OPERATOR);
                 $$ = new Operator(nullptr);
                 $$->setType(TSOperatorType("<="));
              }
     | geq    {
               $$ = compiler.block82_relop_greatt($1,  ">=");
                 compiler.typeTable->install2(">=", njnr::type::OPERATOR);
                 $$ = new Operator(nullptr);
                 $$->setType(TSOperatorType(">="));
              }
     | greatt {
               $$ = compiler.block82_relop_greatt($1, ">");
                 compiler.typeTable->install2(">", njnr::type::OPERATOR);
                 $$ = new Operator(nullptr);
                 $$->setType(TSOperatorType(">"));
              }
;

%%
#include <iostream>
int yyerror(std::string s, Compiler& compiler)
{
   compiler.error(s,"");
   std::cerr << "Error:::"<< compiler.filename << ":"<< compiler.Line_Number << "-> " << s << "\n";
   return 0;
}
