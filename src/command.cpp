#include <config.h>
#include <iostream>
#include <string>
#include <fstream>

#include "debug.hpp"
#include "compiler.hpp"
namespace njnr
{
   bool Compiler::filenameDoesEndsInDotN(\
                             const std::string inFilename)  noexcept
   {
       std::string extra{""};
       auto f_sz{ inFilename.size() };
       if (f_sz >= 2)
       {
          extra = inFilename[(f_sz-1)];
          extra += inFilename[(f_sz-2)];
       }
       return extra == "n.";
   }
   bool Compiler::openedInputFile(int argc, char* const* argv)
   {
       if (argc >1)
       {
            if (true == filenameDoesEndsInDotN(argv[1]))
            {
                try
                {
                    std::ifstream* inputStream{};
                    inputStream = new std::ifstream{argv[1]};
                    if (inputStream->is_open())
                    {
                        infile = inputStream;
                        lexer.switch_streams(inputStream);
                        return true;
                    }
                }
                catch(std::bad_alloc& e)
                {
                    debugprint(e.what(), "");
                    std::cerr << argv[1] << ": cannot open input file\n";
                }
            }
            else
            {
                std::cerr << argv[1] << ": does not end in .n\n";
            }
       }
       else
       {
            lexer.switch_streams(&std::cin);
           return true;
       }
       return false;
   }

   bool Compiler::openedOutputFile(int argc,  char* const* argv)
   {
       if (argc > 1)
       {
          std::string tempstr{argv[1]};

           const size_t a{tempstr.length()-2};

           tempstr[a] = '.';
           tempstr[a+1] = 'c';

           debugprint("trying to open file: ", tempstr);
           try
           {
               std::ofstream* outputStream{new std::ofstream{tempstr,
                                           std::fstream::out}};
               if (outputStream->is_open())
               {
                   outfile = outputStream;
                   filename = tempstr;
                   return true;
               }
           }
           catch(std::bad_alloc& e)
           {
               std::cerr << "error: cannot open file " << tempstr <<
                            " for writing\n";
               debugprint(e.what(), "");
           }
       }
       else
       {
          outfile = &std::cout;
          filename = "stdout";
          return true;
       }
       return false;
   }

#ifdef FALSEAA
//#ifndef MAIN
#define MAIN

   int main(int argc,  char* const* argv)
   {
       Compiler compiler{};

       if (!compiler.openedInputFile(argc, argv))
       {
           compiler.filename = "main.n";
           return -1;
       }
       if (!compiler.openedOutputFile(argc, argv))
       {
           return -1;
       }
       return 0;
   }
#endif
}  // namespace njnr
