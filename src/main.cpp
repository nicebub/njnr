#include <string>
#include <iostream>
#ifndef MAIN
#define MAIN
#endif

#include "debug.hpp"
#include "compiler.hpp"
using namespace njnr;
extern void njnr_getopt(int* argc,  char * const **argv);

int main(int argc,  char * const *argv)
{
    int ret{EXIT_FAILURE};
    Compiler compiler{};

    njnr_getopt(&argc,&argv);

    if((false !=  compiler.openedInputFile(argc,argv)) &&
       (false !=  compiler.openedOutputFile(argc, argv)))
    {
        compiler.code_generator.setstream(compiler.outfile);

        compiler.parser->parse();

#ifdef DEBUG
        compiler.mysymtab->printTree();
#endif
        ret = EXIT_SUCCESS;
    }
    return ret;
}
