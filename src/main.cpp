#include <string>
#include <iostream>

#ifndef MAIN
# define MAIN
#endif

#include "debug.hpp"
#include "compiler.hpp"

using namespace njnr;

/* function to process command-line arguments */
extern void njnr_getopt(int* argc,  char * const **argv);

int main(int argc,  char * const *argv)
{
   int ret{EXIT_FAILURE};

   /* Compiler object to store compiler state while....compiling */
   Compiler compiler{};

   /* process command-line arguments */
   njnr_getopt(&argc,&argv);

   /* must supply an input and output file or the defaults must open successfully */
   if((false !=  compiler.openedInputFile(argc,argv)) &&
      (false !=  compiler.openedOutputFile(argc, argv)))
   {
      /* setup the output file stream */
      compiler.code_generator.setstream(compiler.outfile);

      /* start the parser */
      compiler.parser->parse();

     #ifdef DEBUG
      compiler.printProgramTree();
      compiler.mysymtab->printTree();
     #endif

      /* always succeed if we got this far */
      ret = EXIT_SUCCESS;
   }

   return ret;
}
