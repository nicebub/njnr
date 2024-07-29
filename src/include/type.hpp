#ifndef SRC_INCLUDE_TYPE_HPP_
#define SRC_INCLUDE_TYPE_HPP_

#include <config.h>
#include <string>
#include <map>
namespace njnr
{
/* additive operator types */

/* multiplicitive operator types */

/* euqality testing operator types */

/* relational operator types */
enum class reltype
{
   PLS,   // Plus      +
   MIN,    // Minus     -
   DIV,   // Divide    *
   MULT,   // Multiply  /
   NEQ,   // Not Equal   !=
   EQEQ,   // Equal Equal ==
   LES,   // Less than              <
   LEQ,   // Less than or equal     <=
   GRE,   // Greater than           >
   GEQ    // Greather than or equal >=
};

enum class logType
{
   debug,
   error
};

/* group types */
enum class btype
{
   FUNC,  // Function
   VAR,   // Variable
   PARAM  // Parameter
};

/* data types */
enum class type
{
   INVALID = -1,
   MIN = INVALID,
   INT,       // Integer
   FLOAT,     // Float
   VOID,      // Void
   CHAR,      // Character
   STR,       // String
   REFINT,    // Reference to an Integer
   REFFLOAT,  // Reference to a Float
   REFSTR,    // Reference to a String
   IDENT,     // Identifer
   STMT,      // Statement
   CHECK,     // Hasn't been determined yet and needs to be checked later
   CONSTANT,
   OPERATOR,
   MAX
};

static const std::map<njnr::type, std::string> typeToStringMap
{
   {njnr::type::INT, "INT"},
   {njnr::type::FLOAT, "FLOAT"},
   {njnr::type::CHAR, "CHAR"},
   {njnr::type::VOID, "VOID"},
   {njnr::type::STR, "STR"},
   {njnr::type::REFINT, "REFINT"},
   {njnr::type::REFFLOAT, "REFFLOAT"},
   {njnr::type::REFSTR, "REFSTR"},
   {njnr::type::IDENT, "IDENT"},
   {njnr::type::STMT, "STMT"},
   {njnr::type::CHECK, "CHECK"},
   {njnr::type::CONSTANT, "CONSTANT"},
   {njnr::type::OPERATOR, "OPERATOR"},
};


/* statement types */
enum class statement_type
{
   INVALID,  // Invalid statement type
   RETURN,   // Return statement
   WHILE,    // While statement
   UNTIL,    // Until statement
   IF,       // If statement
   LOOP,     // Loop statement
   FOR,      // For statement
   FOREACH,  // Foreach statement
   IFELSE,   // If...else statement
   DOWHILE,  // Do...while statement
   DOUNTIL,  // Do...until statement
   SWITCH    // Switch statement
};

/* translation unit types */
enum class trans_unit_type
{
   INVALID,  // Invalid translation unit type
   VARDECL,  // Variable Declaration translation unit
   FUNCTION  // Function translation unit
};

/* Used for passing data during parsing, inside generated parser */
struct Pair
{
   int one;
   int two;
   const std::string toString(void) const
   {
      return "one: " + std::to_string(one) +
             " two: " + std::to_string(two) + "\n";
   }
};

void report(njnr::logType t, std::string s);

/* unused types from older architecture
// expression type data structure
struct exprtype
{
   bool lval;        // are we an lval or not - LHS vs RHS
   bool numeric;     // are we numeric and can compute numbers
   njnr::type type;  // what type of expression are we
};
// boolean types
enum class mbool
{
   TRUE,  // true
   FALSE  // false
};
*/
}  // namespace njnr
#endif  // SRC_INCLUDE_TYPE_HPP_
