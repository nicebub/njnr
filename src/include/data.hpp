#ifndef SRC_INCLUDE_DATA_HPP_
#define SRC_INCLUDE_DATA_HPP_

#include <config.h>
#include <string>

#include "type.hpp"
#include "symbol_table_entry.hpp"
#include "symbol_table.hpp"
#include "List.hpp"

namespace njnr
{
struct data
{
public:
    union p1
    {
        std::string                 svalue;
        char                        cvalue;
        int                         ivalue;
        float                       fvalue;
        std::shared_ptr<List>     lstvalue;
        std::shared_ptr<List>    lstpvalue;
        std::shared_ptr<List>    lstevalue;
        type                        tvalue;
        reltype                 addopvalue;
        reltype                multopvalue;
        reltype                  eqopvalue;
        Pair                     pairvalue;
        std::shared_ptr<exprtype> exprvalue;
        reltype                 relopvalue;
        shared_ptr<FunctionHeader> funcheadervalue;
        // Entry *funcentvalue;
    } value;

    std::shared_ptr<S_TableEntryX>         entry;
    std::shared_ptr<S_TableEntryX>       funcent;
    std::shared_ptr<FunctionBinding>           funcbinding;
    std::string            name;
    type                  ttype;
    bool                   lval;
    bool                numeric;
    int                     one;
    int                     two;
    int               mainlabel;
    int                  params;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_DATA_HPP_
