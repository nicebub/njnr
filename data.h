#ifndef _MYDATAH
#define _MYDATAH

#include <stdbool.h>

typedef struct
{
   union
   {
      char* svalue;
      float fvalue;
      int   ivalue;
	   char  cvalue;
      bool  bvalue;
   } u_values;
} data;

#define YYSTYPE data

/*
   char*    name;
   int       one;
   int       two;
   int mainlabel;
   bool     lval;
   bool  numeric;
   int    params;
*/

#endif /* _MYDATAH */
