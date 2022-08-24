#ifndef _MYTYPE_H
#define _MYTYPE_H

#include <vector>
#include <string>


namespace njnr
{
class List;
enum class addtype
{
    PLS,
    MIN
};

enum class multype
{
    DIV,
    MULT
};

enum class eqtype
{
    NEQ,
    EQEQ
};

enum class reltype
{
    LES,
    LEQ,
    GRE,
    GEQ
};

enum class btype
{
    FUNC,
    VAR,
    PARAM
};

enum class type
{
    INT,
    FLOAT,
    VOID,
    CHAR,
    STR,
    REFINT,
    REFFLOAT,
    REFSTR,
    IDENT,
    STMT,
    CHECK
};

enum class mbool
{
    TRUE,
    FALSE
};

enum class statement_type
{
   INVALID,
   RETURN,
   WHILE,
   UNTIL,
   IF,
   LOOP,
   FOR,
   FOREACH,
   IFELSE,
   DOWHILE,
   DOUNTIL,
   SWITCH
};
enum class trans_unit_type
{
   INVALID,
   VARDECL,
   FUNCTION
};

struct Pair
{
    int one;
    int two;
};

struct exprtype
{
    bool lval;
    njnr::type type;
    bool numeric;
};

struct funcheadertype
{
    std::string   name;
    List*         paramlist;
    type          returntype;
    type          ttype;
};

}

#endif // _MYTYPE_H
