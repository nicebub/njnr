#ifndef SRC_INCLUDE_COMPILER_HPP_
#define SRC_INCLUDE_COMPILER_HPP_
#include <config.h>
#include <ostream>
#include <string>
#include <memory>
/*
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#define yyFlexLexer yyFlexLexer
#endif
*/
#include "Constant.hpp"
#include "type.hpp"
#include "ReturnPacket.hpp"
#include "Statement.hpp"
#include "CodeGenerator.hpp"
#include "symbol_table_entry.hpp"
#include "symbol_table.hpp"
// #include "symbol_table_stack.hpp"
#include "njnr.tab.hpp"
#include "njnrLexer.hpp"
#include "operator.hpp"

namespace njnr
{

/* defined elsewhere but needed below */
class SymbolTableX;

/* The Compiler class runs the compiler and keeps its state */
class Compiler
{
   public:
      SymbolTableX*     symbolTable{};  // symbol table
      SymbolTableX*   constantTable{};
      SymbolTableX*       typeTable{};
      CodeGenerator code_generator{};  // code generator
      njnrLexer                lexer;  // lexical analyzer
      njnrParser*           parser{};  // syntactic parser
      std::shared_ptr<FunctionBinding> currentFunc;  // stores current function reading
      std::ostream*          outfile;  // current output stream reference
      std::ifstream*          infile;  // current input file
      std::string           filename;  // name to file needing to output to
      // currently counted line number in a read file
      int                Line_Number;
      // number of global variables read in a source file
      int                globalcount;
      int             offset_counter;
      // count of how many lablels we've created
      int               labelcounter;
      int               othercounter;  // count of ..
      int               param_offset;  // ...
      int                  mainlocal;  // ....
      int                  mainlabel;  // .....
      List               returnTypes;  // .......

      constexpr static int INITIAL_TREE_SIZE{100};

      Compiler();  // Default Constructor
      ~Compiler();  // Deconstructor
      // Constructor with main() arguments passed in
      Compiler(int argc,  char* const* argv);

      // open the command-line given output file
      bool openedOutputFile(int argc,  char* const* argv);
      // open the command-line given input file
      bool openedInputFile(int argc,  char* const* argv);

      // install a function into the symbol table
      void install_functions_into_symbolTable();

      // parsing error function
      int error(std::string, std::string) noexcept;
      // parsing warning function
      int warning(std::string, std::string) noexcept;

      void block1_start_trans_unit();
      bool is_function_decl_or_def_accurate(std::shared_ptr<FunctionHeader> inFunc,
                                            bool isdeclaration);

      void install_parameters_into_symbol_table_curren_scope(std::shared_ptr<FunctionHeader> \
                                                             inFuncHeaderptr);

      std::shared_ptr<FunctionBinding> create_full_function(std::shared_ptr<FunctionHeader> funcheader,
                                                  std::shared_ptr<List> funcbody);
      void block2_func_funcheader_source(std::shared_ptr<FunctionHeader> funcheaderptr);
      void block3_func_funcheader_source_funcbody();
      void block4_func_funcheader_semi(std::shared_ptr<FunctionHeader> inFuncHeaderptr);

      void block5_funcheader_error_semi(std::shared_ptr<FunctionHeader> inFuncHeaderptr);

      std::shared_ptr<FunctionHeader> funcheader_returntype_ident_lpar_paramdef_rpar_helper(\
                                        std::string inIdent,
                                        std::shared_ptr<List> inParamdeflist,
                                        njnr::type inreturntype);


      std::shared_ptr<FunctionHeader> block6_funcheader_void_ident_lpar_paramdef_rpar(\
                            std::string ident,
                            std::shared_ptr<List> paramdeflist);

      std::shared_ptr<FunctionHeader> block7_funcheader_int_ident_lpar_paramdef_rpar(\
                        std::string inIdent,
                        std::shared_ptr<List> inParamdeflist);

      std::shared_ptr<FunctionHeader> block8_funcheader_float_ident_lpar_paramdef_rpar(\
                        std::string inIdent,
                        std::shared_ptr<List> inParamdeflist);

      std::shared_ptr<FunctionHeader> block9_funcheader_void_error_rpar();
      std::shared_ptr<FunctionHeader> block10_funcheader_int_error_rpar();
      std::shared_ptr<FunctionHeader> block11_funcheader_float_error_rpar();

      std::shared_ptr<FunctionHeader> block12_funcheader_void_ident_lpar_error_rpar(\
                                                std::string inIdent);

      std::shared_ptr<FunctionHeader> block13_funcheader_float_ident_lpar_error_rpar(\
                                                std::string inIdent);

      std::shared_ptr<FunctionHeader> block14_funcheader_int_ident_lpar_error_rpar(\
                                                std::string inIdent);

      std::shared_ptr<List>block15_paramdef_paramdeflist_comma_elip(std::shared_ptr<List> inParamdeflistptr);
      std::shared_ptr<List>block16_paramdef_void();

      void block17_paramdef_paramdeflist_error_rpar(std::shared_ptr<List> inParamdeflistptr);

      void block18_paramdef_paramdeflist_comma_error_rpar(\
                                                std::shared_ptr<List> inParamdeflistptr);

      std::shared_ptr<List>paramdeflist_type_ident_helper(njnr::Identifier inIdent,
                                                          njnr::type intype);
      std::shared_ptr<List>block19_paramdeflist_int_ident(std::string inIdent);
      std::shared_ptr<List>block20_paramdeflist_float_ident(std::string inIdent);
      std::shared_ptr<List>block21_paramdeflist_char_star_ident(std::string inIdent);

      std::shared_ptr<List>paramdeflist_paramdeflist_comma_type_ident_helper(\
      std::shared_ptr<List> inParamdeflistptr, njnr::Identifier inIdent, njnr::type intype);

      std::shared_ptr<List>block22_paramdeflist_paramdeflist_comma_int_ident(\
      std::shared_ptr<List> inParamdeflist, njnr::Identifier inIdent);

      std::shared_ptr<List>block23_paramdeflist_paramdeflist_comma_float_ident(\
      std::shared_ptr<List> inParamdeflist, njnr::Identifier inIdent);

      std::shared_ptr<List>block24_paramdeflist_paramdeflist_comma_char_star_ident(\
      std::shared_ptr<List> inParamdeflist, njnr::Identifier inIdent);

      void block25_funcbody_lcbra_decls_source();
      void block26_funcbody_lcbra_decls_source_stmtlist_rcbra();

      void block27_variabledecl_int_identlist_semi(std::shared_ptr<List> inIdentlist);
      void block28_variabledecl_float_identlist_semi(std::shared_ptr<List> inIdentlist);

      void block29_stmt_expr_semi();

      void dealwithstmtlist(std::shared_ptr<List> stmtlist);

      std::shared_ptr<FunctionBinding> create_and_return_a_fn_body_statement_element(std::shared_ptr<Statement> stmt);
      std::shared_ptr<FunctionBinding> add_statement_to_fn_body_and_return(std::shared_ptr<List>func,
                                                                 std::shared_ptr<Statement> stmt);
      std::shared_ptr<Statement> stmt_return_expr_semi(std::shared_ptr<ReturnPacket> inPacket);

      void variableFetch(std::shared_ptr<ReturnPacket> inPacket,
                         bool conversionNeeded);
      void variableFetchWithNumericCheck(std::shared_ptr<ReturnPacket> inPacket,
                                         bool conversionNeeded);
      void variableFetchWithNumericCheckAndLvalCheck(\
               std::shared_ptr<ReturnPacket> insimplePacketptr,
               bool conversionNeeded);
      std::shared_ptr<ReturnPacket> block32_stmt_while_source();
      void block33_stmt_while_source_expr_semi_source_lpar_expr_rpar(\
                  std::shared_ptr<ReturnPacket> insourcePacket,
                  std::shared_ptr<ReturnPacket> inexprPacket);

      void block34_5_stmt_helper(int one, int two);

      void while_and_if_reducer(std::shared_ptr<ReturnPacket> insourcePacket,
                                std::shared_ptr<ReturnPacket> inexprPacket,
                                int number,
                                std::string while_or_if);

    void block34_stmt_while_source_expr_semi_source_lpar_expr_rpar_source_stmt \
                    (std::shared_ptr<ReturnPacket> insourcePacket,
                     std::shared_ptr<ReturnPacket> inexprPacket);
      void block35_stmt_ifexprstmt_else(std::shared_ptr<ReturnPacket> insourcePacket);

      void block36_7_stmt_helper(std::shared_ptr<ReturnPacket> inPacket,
                                 int number);

      void block36_stmt_ifexprstmt_else_source_stmt(std::shared_ptr<ReturnPacket> inPacket);
      void block37_stmt_ifexprstmt(std::shared_ptr<ReturnPacket> inPacket);

      struct Pair block38_ifexprstmt_if_lpar_expr_source(\
                                             std::shared_ptr<ReturnPacket> inexprPacket);
      void block39_ifexprstmt_if_lpar_expr_source_rpar_stmt();

      void normalStore(njnr::type intype);
      void variableStore(njnr::type intype);

      std::shared_ptr<ReturnPacket> block40_expr_equalexpr_equal_equalexpr(\
                                 std::shared_ptr<ReturnPacket> inequalexprPacketptr,
                                 std::shared_ptr<ReturnPacket> inotherequalexprPacketptr);

      void block41_expr_equalexpr();

      void block42_equalexpr_relexpr_eqop_source(\
                                      std::shared_ptr<ReturnPacket> relexprPacketptr);

      std::shared_ptr<ReturnPacket> block43_equalexpr_relexpr_helper(njnr::reltype ineqop,
                                                     std::string need_letter_b);

      std::shared_ptr<ReturnPacket> block43_equalexpr_relexpr_eqop_source_relexpr(\
                           Operator* ineqop,
                           std::shared_ptr<ReturnPacket> relexprPacketptr,
                           std::shared_ptr<ReturnPacket> otherrelexprPacketptr);
      void block44_equalexpr_relexpr();

      void block45_relexpr_simpleexpr_relop_source(\
                                       std::shared_ptr<ReturnPacket> insimplePacketptr);

      std::shared_ptr<ReturnPacket> block46_relexpr_simpleexpr_relop_helper(\
                                                    njnr::reltype inrelop,
                                                    std::string need_letter_b);

      std::shared_ptr<ReturnPacket> block46_relexpr_simpleexpr_relop_source_simpleexpr(\
                                      std::shared_ptr<ReturnPacket> simpleexprPacketptr,
                                      Operator* inrelop,
                                      std::shared_ptr<ReturnPacket> othersimpleexprPacketptr);
      void block47_relexpr_simpleexpr();

      void block48_simpleexpr_simpleexpr_addop_source(\
                                             std::shared_ptr<ReturnPacket> insimplePacketptr);

      std::shared_ptr<ReturnPacket> block49_simpleexpr_addop_helper(njnr::reltype inaddop,
                                                    std::string need_letter_b);

      std::shared_ptr<ReturnPacket> block49_simpleexpr_simpleexpr_addop_source_term(\
                                      std::shared_ptr<ReturnPacket> simpleexprPacketptr,
                                      Operator* inaddop,
                                      std::shared_ptr<ReturnPacket> termPacketptr);
      void block50_simpleepr_term();

      void block51_term_term_mulop_source(std::shared_ptr<ReturnPacket> inPacketptr);

      std::shared_ptr<ReturnPacket> block52_term_mulop_helper(njnr::reltype inmulop,
                                              std::string need_letter_b);

      std::shared_ptr<ReturnPacket> block52_term_term_mulop_source_factor(\
                                                 std::shared_ptr<ReturnPacket> intermptr,
                                                 Operator* inmulop,
                                                 std::shared_ptr<ReturnPacket> infactorptr);
      void block53_term_factor();

      std::shared_ptr<ReturnPacket> block54_factor_constant(std::shared_ptr<Constant> inConstant);
      std::shared_ptr<ReturnPacket> block55_factor_ident(std::string inIdent);
      std::shared_ptr<ReturnPacket> block56_factor_lpar_expr_rpar(std::shared_ptr<ReturnPacket> inPacket);

      std::shared_ptr<ReturnPacket> block57_factor_addop_factor_uminus(Operator* inop,
                                                       std::shared_ptr<ReturnPacket> inPacket);

      std::shared_ptr<ReturnPacket> block58_factor_adof_ident(std::string inPacket);
      std::shared_ptr<ReturnPacket> block59_factor_function_call(std::shared_ptr<ReturnPacket> inPacket);

      std::shared_ptr<ReturnPacket> block60_function_call_ident_lpar_rpar(\
                                                      std::string inIdent);
      void block61_function_call_func_call_with_params();

      std::shared_ptr<ReturnPacket> block62_func_call_with_params_name_and_params_rpar(\
                                                std::shared_ptr<ReturnPacket> nameAndparamptr);

      std::shared_ptr<ReturnPacket> block63_name_and_params_ident_lpar_source(\
                                                     std::string inPacket);

      std::shared_ptr<ReturnPacket> block64_name_and_params_ident_lpar_source_expr(\
                                                    std::string inIdent,
                                                    std::shared_ptr<ReturnPacket> inEntryptr,
                                                    std::shared_ptr<ReturnPacket> inPacketptr);

      std::shared_ptr<ReturnPacket> block65_name_and_params_name_and_params_comma_expr(\
                                         std::shared_ptr<ReturnPacket> innameAndparamPacketptr,
                                         std::shared_ptr<ReturnPacket> inexprPacketptr);

      void block66_constant_strconstant(std::shared_ptr<ReturnPacket> mcon,
                                        std::string instrconstant);

      void block67_constant_intconstant(std::shared_ptr<ReturnPacket> mcon,
                                        int intconstant);

      void block68_constant_floatconstant(std::shared_ptr<ReturnPacket> mcon,
                                          float floatconstant);

      std::shared_ptr<List> block69_identlist_ident(std::string inIdent);
      bool block70_identlist_comma_ident(std::shared_ptr<List> inIdentListptr,
                                          std::string inIdent);
      Operator* createOperator(njnr::reltype n, std::string s);
      std::shared_ptr<Constant> createConstant(njnr::type n, std::string t);
      // void  setfinished(std::shared_ptr<List>inlist);
      void  setfinished(std::shared_ptr<List> inlist);
      void  printProgramTree(void);
      void  checkfunctionReturnValues(std::shared_ptr<FunctionBinding> f);
      bool  aresimilartypes(njnr::type t1, njnr::type t2);
      static std::string getStringFromType(njnr::type t);
      njnr::type getReturnTypeFromStatement(std::shared_ptr<Statement> s);
      std::shared_ptr<List>getfinished(void);
      void installVariableIntoSymbolTable(std::shared_ptr<Identifier> Id, njnr::type t);
      void installVariableIntoSymbolTable(std::string Id, njnr::type t);
      void installParameterIntoSymbolTable(std::shared_ptr<Identifier> Id, njnr::type t);
      void installParameterIntoSymbolTable(std::string Id, njnr::type t);
      bool checkAllFunctionReturnStatements(std::shared_ptr<njnr::List>x, njnr::type);
      bool checkSingleReturnStatement(std::shared_ptr<Statement> realstmt,
                                      njnr::type foundtype,
                                      bool first);
   protected:
      static bool filenameDoesEndsInDotN(const std::string in)  noexcept;
      void closeOrRemoveOutputFile(bool needtoremove);
      void closeOrRemoveInputFile(bool needtoremove);
      static std::string mapNjnrTypeToString(njnr::type t);

   private:
      bool   founderror;
      std::shared_ptr<List> finished;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_COMPILER_HPP_
