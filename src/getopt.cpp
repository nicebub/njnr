#include <config.h>
#include <unistd.h>
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstdio>

#define GETOPT_DONE (-1)
#define COMPILER_NAME "njnr"
#define COMPILER_VERSION "0.0.1"

void njnr_getopt(int* argc,  char * const **argv)
{
    int opt{GETOPT_DONE};

    while ((opt = getopt(*argc,*argv,"hv")) != GETOPT_DONE)
    {
        switch(opt)
        {
            case 'v': std::cout << COMPILER_NAME << " " << COMPILER_VERSION << std::endl; break;
            case 'h':
            case '?': fprintf(stderr, "Usage: %s [-vh] [njnr source file]\n",
                              (*argv)[0]);
                      break;
        }
    }
   if(optind > 1)
   {
      *argc -= optind;
      *argv += optind;
   }
}