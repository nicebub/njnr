#ifndef _MYDATAH
#define _MYDATAH

#include <stdbool.h>

typedef enum tag_ttype
{
   INV,
   MIN_TYPE = INV,
   STR,
   INT,
   CHAR,
   PTR,
   NUL,
   NIL,
   MAX_TYPE = NIL
} ttype;

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
   bool has_return;
   ttype return_type;
   struct data* next;
   struct data* prev;
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
