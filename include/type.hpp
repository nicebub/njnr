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
      CHECK,     // Hasn't been determined yet and needs to be checked later
      OPERATOR,
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

   /**
    * @brief Type System Type Abstract Class Interface
    * 
    */
   class TSAbstractType
   {
      public:
         TSAbstractType() : typeValue{""}, tType{njnr::type::VOID}, isNumeric{false}, isLval{false} {};

         TSAbstractType(std::string typeValue,
                        njnr::type tType=njnr::type::VOID) : typeValue{typeValue},
                                                             tType{tType}, isNumeric{false}, isLval{false} {};

         TSAbstractType(std::string typeValue, njnr::type tType,
                        bool isNumeric=false, bool isLval = false) : typeValue{typeValue}, 
                                                                     tType{tType},
                                                                     isNumeric{isNumeric},
                                                                     isLval{isLval}
                                                                     {};
         virtual                     ~TSAbstractType() {};

         virtual   const bool             getNumeric()    const noexcept = 0;
         virtual   const bool                getLVal()    const noexcept = 0;

         virtual   const std::string    getTypeValue()    const noexcept = 0;
         virtual   const std::string        toString()    const noexcept = 0;
         virtual   const njnr::type          getType()    const noexcept = 0;

         virtual   void       setNumeric(const bool n)          noexcept = 0;
         virtual   void          setLVal(const bool l)          noexcept = 0;
      protected:
         const std::string typeValue;
         const njnr::type  tType;
         bool              isNumeric;
         bool              isLval;
   };

   /**
    * @brief Generic lower-level implementation of Abstract Class Interface
    *         TSAbstractType
    * 
    */
   class TSType : public TSAbstractType
   {
      public:
         virtual ~TSType() {};

         TSType() : TSAbstractType("", njnr::type::VOID, false, false) {};

         TSType(std::string typeValue,
                njnr::type tType=njnr::type::VOID) : TSAbstractType(typeValue, tType, false, false) {};

         TSType(std::string typeValue, njnr::type tType,
                bool isNumeric=false, bool isLval = false) : TSAbstractType(typeValue,
                                                                            tType,
                                                                            isNumeric,
                                                                            isLval) {};

         virtual const std::string toString() const noexcept {return typeValue;};
         virtual const njnr::type getType() const noexcept {return tType;};
         virtual const std::string getTypeValue() const noexcept {return typeValue;};
         virtual const bool getNumeric() const noexcept {return false;};
         virtual const bool getLVal() const noexcept { return false;};
         virtual void setNumeric(const bool isNumeric) noexcept { this->isNumeric = isNumeric;};
         virtual void setLVal(const bool isLval)  noexcept { this->isLval = isLval;};
   };
};
#endif // _MYTYPE_H
