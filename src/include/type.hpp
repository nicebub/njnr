#ifndef SRC_INCLUDE_TYPE_HPP_
#define SRC_INCLUDE_TYPE_HPP_

#include <config.h>
#include <string>
#include <memory>

namespace njnr
{
/* defined elsewhere but need below */
class List;

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
   debug, error
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
   const std::string toString(void) const
   {
      return "one: " + std::to_string(one) +
             " two: " + std::to_string(two) + "\n";
   }
};

/* expression type data structure */
struct exprtype
{
   bool lval;        // are we an lval or not - LHS vs RHS
   bool numeric;     // are we numeric and can compute numbers
   njnr::type type;  // what type of expression are we
};

void report(njnr::logType t, std::string s);

/* function prototype data structure */
class funcheadertype
{
   public:
   funcheadertype() : name{}, paramlist{nullptr}, returntype{}, ttype{} {}
   virtual ~funcheadertype();
   std::string   name;        // fn name
   std::shared_ptr<njnr::List>   paramlist;   // list of parameters the fn accept as input
   njnr::type    returntype;  // return type(if any) of fn
   njnr::type    ttype;       // type of fn?(TBD)
};
/**
 * @brief Type System Type Abstract Class Interface
 * 
 */
class TSAbstractType
{
   public:
      TSAbstractType() : typeValue{"AbstractType__NA__()"} {};

      explicit TSAbstractType(const std::string typeValue) :
                                 typeValue{"AbstractType" + typeValue+"()"} {}

      virtual                     ~TSAbstractType()
      {
         report(njnr::logType::debug,
                "running TSAbstractType() destructor");
         report(njnr::logType::debug, "typeValue" + typeValue);
      }

      virtual   const bool             getNumeric()    const noexcept = 0;
      virtual   const bool                getLVal()    const noexcept = 0;

      virtual   const std::string        toString()    const noexcept = 0;
      virtual   const std::string    getTypeValue()    const noexcept = 0;
      virtual   const njnr::type          getType()    const noexcept = 0;
      virtual TSAbstractType& operator=(const TSAbstractType& t)
      {
         if (const_cast<TSAbstractType*>(&t) != this)
         {
            this->typeValue = t.typeValue;
         }
         return *this;
      }

   protected:
      std::string typeValue;
};

/**
 * @brief Generic lower-level implementation of Abstract Class Interface
 *         TSAbstractType
 * 
 */
class TSType : public TSAbstractType
{
   public:
      TSType() : TSAbstractType("GenericType__NA__()"),
                                isNumeric{false},
                                isLval{false} {};

      explicit TSType(const std::string typeValue) :
                   TSAbstractType("GenericType" + typeValue + "()"),
                   isNumeric{false},
                   isLval{false} {};


      TSType(const std::string typeValue,
             const bool isNumeric,
             const bool isLval = false) :
             TSAbstractType("GenericType" + typeValue + "()"),
             isNumeric{isNumeric},
             isLval{isLval} {};

      virtual ~TSType()
      {
         report(njnr::logType::debug,
                "running TSType() Destructor");
         report(njnr::logType::debug, this->toString());
         report(njnr::logType::debug, "isnumeric" + isNumeric);
         report(njnr::logType::debug, "isLval" + isLval);
      }

      virtual const bool getNumeric()          const noexcept
      {
         return isNumeric;
      }
      virtual const bool getLVal()             const noexcept
      {
         return isLval;
      }

      virtual const std::string toString()     const noexcept
      {
         return typeValue;
      }
      virtual const std::string getTypeValue() const noexcept
      {
         return typeValue;
      }
      virtual const njnr::type getType()       const noexcept
      {
         return njnr::type::VOID;
      }

      virtual TSType& operator=(const TSType& t)
      {
         if (const_cast<TSType*>(&t) != this)
         {
            this->typeValue = t.typeValue;
            this->isNumeric = t.isNumeric;
            this->isLval = t.isLval;
         }
         return *this;
      }

   private:
      bool isNumeric;
      bool isLval;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_TYPE_HPP_
