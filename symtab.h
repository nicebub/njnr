#ifndef _SYMTABH
#define _SYMTABH

#include <search.h>
#include <stdio.h>

extern int Line_Number;
extern FILE *infile;
extern int offset_counter;
extern int globalcount;

//extern int warning(char*, char*);

//extern int error(char*,char*);

typedef enum {
        FUNC,
        VAR,
        PARAM
} btype;

typedef struct {
        char * name;
        void * binding;
        btype self;
} Entry;

typedef struct {
        Entry ** Stack; //Stack of Binary Search Trees
        int actualStacksize; //used to keep size and top of stack
        int Stacksize; //default of 100
} Symtab;

int Ecmp(const void *Entry1, const void *Entry2);  //comparison function

void printTree(Symtab *symtab);

void Swalk(const void *node, VISIT myorder, int level);

void install(Entry*, Symtab *symtab);

void * lookup(const char * name, Symtab *symtab);
Entry * lookupB(const char * name, Symtab *symtab);
bool inCscope(const char *name, Symtab *symtab);

void openscope(Symtab *symtab);

void openmainscope(Symtab *symtab);

void closemainscope(Symtab *symtab);

void closescope(Symtab *symtab);

void deleteEntry(Entry * temp);

void deleteTree(Symtab *symtab);

Symtab * createTree(int Stacksize);

Entry* createFunc(char * name, type returntype, ListP *paramlist);

Entry* createVar(char * name, type t_type, int offset);

Entry* createParam(char * name, type t_type, int offset);

void addtosymtab(Symtab* mysymtab, type mytype, List * myList);

int getleveldif(char *name, Symtab *mysymtab);

#endif
