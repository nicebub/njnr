#define DEBUGON
#define DEBUG
//#define YYDEBUG
#ifdef DEBUGON
extern int yydebug;
# ifndef DEBUG
#  define DEBUG
# endif
// int yydebug = 1;
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "data.h"
//#define YYSTYPE data

extern int yyparse(void);

int main(int argc, const char* argv[])
{
   #if YYDEBUG == 1
    yydebug = 1;
   #endif

	yyparse();

	return 0;
}
