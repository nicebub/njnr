#ifndef _DEBUG_H
#define _DEBUG_H

#ifdef DEBUGON
#ifndef DEBUG
#define DEBUG
#define YYDEBUG 1
#endif
#endif

#ifndef DEBUG
#define debugprint(x,y)

#endif

#include <string>
namespace njnr
{
class Debug
{
public:
    Debug();
    ~Debug();
    static int get_yydebug() ;
    static void set_yydebug(const int value);
private:
    static int yydebug;
};
#ifdef DEBUG
void debugprint(std::string,std::string);
void debugprint(std::string,int);
#endif
}


#endif