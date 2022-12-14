#ifndef _MYTYPE_H
#define _MYTYPE_H

#include <vector>
#include <string>


namespace njnr
{
   /* defined elsewhere but need below */
   class List;

   /* additive operator types */
   enum class addtype
   {
      PLS,   // Plus      +
      MIN    // Minus     -
   };

   /* multiplicitive operator types */
   enum class multype
   {
      DIV,   // Divide    *
      MULT   // Multiply  /
   };

   /* euqality testing operator types */
   enum class eqtype
   {
      NEQ,   // Not Equal   !=
      EQEQ   // Equal Equal ==
   };

   /* relational operator types */
   enum class reltype
   {
      LES,   // Less than              <
      LEQ,   // Less than or equal     <=
      GRE,   // Greater than           >
      GEQ    // Greather than or equal >=
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
      INT,      // Integer
      FLOAT,    // Float
      VOID,     // Void
      CHAR,     // Character
      STR,      // String
      REFINT,   // Reference to an Integer
      REFFLOAT, // Reference to a Float
      REFSTR,   // Reference to a String
      IDENT,    // Identifer
      STMT,     // Statement
      CHECK     // Hasn't been determined yet and needs to be checked later
   };

   /* boolean types */
   enum class mbool
   {
      TRUE,  // true
      FALSE  // false
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
      const std::string toString(void) const { return "one: " + std::to_string(one) + " two: " + std::to_string(two) + "\n";}
   };

   /* expression type data structure */
   struct exprtype
   {
      bool lval;        // are we an lval or not - LHS vs RHS
      bool numeric;     // are we numeric and can compute numbers
      njnr::type type;  // what type of expression are we
   };

   /* function prototype data structure */
   struct funcheadertype
   {
      std::string   name;       // fn name
      njnr::List*   paramlist;  // list of parameters the fn accept as input
      njnr::type    returntype; // return type(if any) of fn
      njnr::type    ttype;      // type of fn?(TBD)
   };
};
#endif // _MYTYPE_H
