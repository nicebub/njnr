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
    IDENT
};

enum class mbool
{
    TRUE,
    FALSE
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
    std::string 	name;
    List*				paramlist;
    type				returntype;
    type				ttype;
};
}

#endif // _MYTYPE_H
