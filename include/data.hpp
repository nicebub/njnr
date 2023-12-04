#ifndef _MYDATA_H
#define _MYDATA_H

#include <string>

#include "type.hpp"
#include "symbol_table_entry.hpp"
#include "symbol_table.hpp"
#include "symbol_table_stack.hpp"
#include "list.hpp"

namespace njnr
{
struct data
{
public:
    union p1
    {
        std::string 		     svalue;
        char 					 cvalue;
        int 					 ivalue;
        float 				     fvalue;
        List*				   lstvalue;
        List* 				  lstpvalue;
        type 					 tvalue;
        addtype 		 	 addopvalue;
        multype 	        multopvalue;
        eqtype 				  eqopvalue;
        List* 				  lstevalue;
        Pair 				  pairvalue;
        exprtype* 			  exprvalue;
        reltype 			 relopvalue;
        funcheadertype* funcheadervalue;
        //Entry *funcentvalue;
    } value;

    S_TableEntry* 		  entry;
    S_TableEntry* 		funcent;
    Funcb* 			funcbinding;
    std::string 	 	   name;
    type 				  ttype;
    bool 				   lval;
    bool 				numeric;
    int 					one;
    int 					two;
    int 			  mainlabel;
    int 				 params;
};
}
#endif
