#ifndef _COMPILER_HPP
#define _COMPILER_HPP
#include <ostream>
#include <string>
/*
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#define yyFlexLexer yyFlexLexer
#endif
*/
#include "type.hpp"
#include "trans.hpp"
#include "symtab.hpp"
#include "njnr.tab.hpp"
#include "lex.hpp"

namespace njnr
{
   class SymbolTable;

   class Compiler
   {
      public:
         SymbolTable*        mysymtab{};
         CodeGenerator code_generator{};
         njnrLexer                lexer;
         njnrParser*           parser{};
         Funcb*             currentFunc;
         std::ostream*          outfile;
         std::string           filename;
         int                Line_Number;
         int                globalcount;
         int             offset_counter;
         int               labelcounter;
         int               othercounter;
         int               param_offset;
         int                  mainlocal;
         int                  mainlabel;
         List               returnTypes;

         constexpr static int INITIAL_TREE_SIZE{100};

         Compiler();
         Compiler(int argc, const char** argv);
         ~Compiler();

         bool openedOutputFile(int argc, const char** argv);
         bool openedInputFile(int argc, const char** argv);

         void install_functions_into_symbolTable();

         int error(std::string,std::string) noexcept;
         int warning(std::string,std::string) noexcept;

         void block1_start_trans_unit();
         bool is_function_decl_or_def_accurate(funcheadertype** inFunc, bool isdeclaration);
         void install_parameters_into_symbol_table_curren_scope(funcheadertype** inFuncHeaderptr);

         Funcb* create_full_function(funcheadertype* funcheader, List* funcbody);
         void block2_func_funcheader_source(funcheadertype** funcheaderptr);
         void block3_func_funcheader_source_funcbody();
         void block4_func_funcheader_semi(funcheadertype* inFuncHeaderptr);
  
         void block5_funcheader_error_semi(funcheadertype** inFuncHeaderptr);
  
         funcheadertype* funcheader_returntype_ident_lpar_paramdef_rpar_helper(njnr::Identifier inIdent, List* inParamdeflist,njnr::type inreturntype);
  
         funcheadertype* block6_funcheader_void_ident_lpar_paramdef_rpar(njnr::Identifier ident, List* paramdeflist);
         funcheadertype* block7_funcheader_int_ident_lpar_paramdef_rpar(njnr::Identifier inIdent, List* inParamdeflist);
         funcheadertype* block8_funcheader_float_ident_lpar_paramdef_rpar(njnr::Identifier inIdent, List* inParamdeflist);
         funcheadertype* block9_funcheader_void_error_rpar();
         funcheadertype* block10_funcheader_int_error_rpar();
         funcheadertype* block11_funcheader_float_error_rpar();
         funcheadertype* block12_funcheader_void_ident_lpar_error_rpar(njnr::Identifier inIdent);
         funcheadertype* block13_funcheader_float_ident_lpar_error_rpar(njnr::Identifier inIdent);
         funcheadertype* block14_funcheader_int_ident_lpar_error_rpar(njnr::Identifier inIdent);

         List* block15_paramdef_paramdeflist_comma_elip(List** inParamdeflistptr);
         List* block16_paramdef_void();
  
         void block17_paramdef_paramdeflist_error_rpar(List** inParamdeflistptr);
         void block18_paramdef_paramdeflist_comma_error_rpar(List** inParamdeflistptr);
  
         List* paramdeflist_type_ident_helper(njnr::Identifier inIdent, njnr::type intype);
         List* block19_paramdeflist_int_ident(njnr::Identifier inIdent);
         List* block20_paramdeflist_float_ident(njnr::Identifier inIdent);
         List* block21_paramdeflist_char_star_ident(njnr::Identifier inIdent);
  
         List* paramdeflist_paramdeflist_comma_type_ident_helper(List** inParamdeflistptr, njnr::Identifier inIdent, njnr::type intype);
         List* block22_paramdeflist_paramdeflist_comma_int_ident(List** inParamdeflist, njnr::Identifier inIdent);
         List* block23_paramdeflist_paramdeflist_comma_float_ident(List** inParamdeflist, njnr::Identifier inIdent);
         List* block24_paramdeflist_paramdeflist_comma_char_star_ident(List** inParamdeflist, njnr::Identifier inIdent);
  
         void block25_funcbody_lcbra_decls_source();
         void block26_funcbody_lcbra_decls_source_stmtlist_rcbra();
  
         void block27_variabledecl_int_identlist_semi(List** inIdentlist);
         void block28_variabledecl_float_identlist_semi(List** inIdentlist);
  
         void block29_stmt_expr_semi();

         void dealwithstmtlist(List* stmtlist);

         Funcb* create_and_return_a_fn_body_statement_element(Statement* stmt);
         Funcb* add_statement_to_fn_body_and_return(List* func, Statement* stmt);
         Statement* block30_stmt_return_semi();
         Statement* block31_stmt_return_expr_semi(ReturnPacket* inPacket);
  
         void variableFetch(ReturnPacket* inPacket, bool conversionNeeded);
         void variableFetchWithNumericCheck(ReturnPacket* inPacket, bool conversionNeeded);
         void variableFetchWithNumericCheckAndLvalCheck(ReturnPacket* insimplePacketptr,bool conversionNeeded);
         ReturnPacket* block32_stmt_while_source();
         void block33_stmt_while_source_expr_semi_source_lpar_expr_rpar(ReturnPacket* insourcePacket, ReturnPacket* inexprPacket);
  
         void block34_5_stmt_helper(int one, int two);
  
         void while_and_if_reducer(ReturnPacket* insourcePacket, ReturnPacket* inexprPacket, int number, std::string while_or_if);
  
         void block34_stmt_while_source_expr_semi_source_lpar_expr_rpar_source_stmt(ReturnPacket* insourcePacket, ReturnPacket* inexprPacket);
         void block35_stmt_ifexprstmt_else(ReturnPacket* insourcePacket);
  
         void block36_7_stmt_helper(ReturnPacket* inPacket, int number);
  
         void block36_stmt_ifexprstmt_else_source_stmt(ReturnPacket* inPacket);
         void block37_stmt_ifexprstmt(ReturnPacket* inPacket);
  
         struct Pair block38_ifexprstmt_if_lpar_expr_source(ReturnPacket* inexprPacket);
         void block39_ifexprstmt_if_lpar_expr_source_rpar_stmt();
  
         void normalStore(njnr::type intype);
         void variableStore(njnr::type intype);
         ReturnPacket* block40_expr_equalexpr_equal_equalexpr(ReturnPacket** inequalexprPacketptr,ReturnPacket** inotherequalexprPacketptr);
         void block41_expr_equalexpr();
  
         void block42_equalexpr_relexpr_eqop_source(ReturnPacket** relexprPacketptr);
  
         ReturnPacket* block43_equalexpr_relexpr_helper(njnr::eqtype ineqop, std::string need_letter_b);
  
         ReturnPacket* block43_equalexpr_relexpr_eqop_source_relexpr(njnr::eqtype ineqop, ReturnPacket** relexprPacketptr, ReturnPacket** otherrelexprPacketptr);
         void block44_equalexpr_relexpr();
  
         void block45_relexpr_simpleexpr_relop_source(ReturnPacket** insimplePacketptr);
  
         ReturnPacket* block46_relexpr_simpleexpr_relop_helper(njnr::reltype inrelop, std::string need_letter_b);
  
         ReturnPacket* block46_relexpr_simpleexpr_relop_source_simpleexpr(ReturnPacket** simpleexprPacketptr, njnr::reltype inrelop, ReturnPacket** othersimpleexprPacketptr);
         void block47_relexpr_simpleexpr();
  
         void block48_simpleexpr_simpleexpr_addop_source(ReturnPacket** insimplePacketptr);
  
         ReturnPacket* block49_simpleexpr_addop_helper(njnr::addtype inaddop,std::string need_letter_b);
  
         ReturnPacket* block49_simpleexpr_simpleexpr_addop_source_term(ReturnPacket** simpleexprPacketptr, njnr::addtype inaddop, ReturnPacket** termPacketptr);
         void block50_simpleepr_term();
  
         void block51_term_term_mulop_source(ReturnPacket** inPacketptr);
  
         ReturnPacket* block52_term_mulop_helper(njnr::multype inmulop,std::string need_letter_b);
  
         ReturnPacket* block52_term_term_mulop_source_factor(ReturnPacket** intermptr, njnr::multype inmulop,ReturnPacket** infactorptr);
         void block53_term_factor();
  
         ReturnPacket* block54_factor_constant(Constant* inConstant);
         ReturnPacket* block55_factor_ident(njnr::Identifier inIdent);
         ReturnPacket* block56_factor_lpar_expr_rpar(ReturnPacket** inPacket);
         ReturnPacket* block57_factor_addop_factor_uminus(njnr::addtype inop, ReturnPacket** inPacket);
         ReturnPacket* block58_factor_adof_ident(njnr::Identifier inPacket);
         ReturnPacket* block59_factor_function_call(ReturnPacket** inPacket);
  
         ReturnPacket* block60_function_call_ident_lpar_rpar(njnr::Identifier inIdent);
         void block61_function_call_func_call_with_params();
  
         ReturnPacket* block62_func_call_with_params_name_and_params_rpar(ReturnPacket** nameAndparamptr);
  
         ReturnPacket* block63_name_and_params_ident_lpar_source(njnr::Identifier inPacket);
         ReturnPacket* block64_name_and_params_ident_lpar_source_expr(njnr::Identifier inIdent, ReturnPacket** inEntryptr, ReturnPacket** inPacketptr);
         ReturnPacket* block65_name_and_params_name_and_params_comma_expr(ReturnPacket** innameAndparamPacketptr, ReturnPacket** inexprPacketptr);
  
         void block66_constant_strconstant(njnr::ReturnPacket* mcon, std::string instrconstant);
         void block67_constant_intconstant(njnr::ReturnPacket* mcon, int intconstant);
         void block68_constant_floatconstant(njnr::ReturnPacket* mcon, float floatconstant);
  
         List* block69_identlist_ident(njnr::Identifier inIdent);
         List* block70_identlist_comma_ident(List** inIdentListptr, njnr::Identifier inIdent);
  
      protected:
         static bool filenameDoesEndsInDotN(const std::string& in)  noexcept;
         void closeOrRemoveOutputFile(bool needtoremove);
  
      private:
         bool   founderror;
   };
}
#endif
