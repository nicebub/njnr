#include <config.h>
#include <string>
#include <iostream>

#ifndef MAIN
# define MAIN
#endif
#ifndef DEBUG
#define DEBUG 0
#endif

#include "debug.hpp"
#include "Compiler.hpp"

using njnr::Compiler;

/* function to process command-line arguments */
extern void njnr_getopt(int* argc,  char * const **argv);

int main(int argc,  char * const *argv)
{
   int ret{EXIT_FAILURE};

   /* Compiler object to store compiler state while....compiling */
   std::shared_ptr<Compiler> compiler = std::make_shared<Compiler>();
   /* process command-line arguments */
   njnr_getopt(&argc, &argv);

   /* must supply an input and output file or the
       defaults must open successfully */
   if ((true ==  compiler->openedInputFile(argc, argv)) &&
       (true ==  compiler->openedOutputFile(argc, argv)))
   {
      /* setup the output file stream */
      compiler->code_generator.setstream(compiler->outfile);

      /* start the parser */
      compiler->parser->parse();
      if (DEBUG)
      {
         compiler->printProgramTree();
      }
     #if DEBUG
      compiler->symbolTable->printTree();
     #endif

      if (true == compiler->code_generator.canGenerateCode())
      {
         std::cout << "-- Generating Code --\n";
         compiler->code_generator.setSymbolTable(compiler->symbolTable);
         compiler->code_generator.generate(compiler->getfinished());
      }
      else
      {
         report(njnr::logType::debug, "not generating code");
      }
      /* always succeed if we got this far */
      ret = EXIT_SUCCESS;
   }
   report(njnr::logType::debug,"deleting compiler");;
    compiler = nullptr;
   return ret;
}
