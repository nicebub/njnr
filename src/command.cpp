#include <iostream>
#include <string>
#include <iostream>
#include <fstream>

#include "debug.hpp"
#include "compiler.hpp"
namespace njnr
{
   bool Compiler::filenameDoesEndsInDotN(const std::string& inFilename)  noexcept
   {
       std::string extra{""};
       auto f_sz{ inFilename.size() };
       if(f_sz >= 2)
       {
          extra = inFilename[(f_sz-1)];
          extra += inFilename[(f_sz-2)];
       }
       return extra == "n.";
   }
   bool Compiler::openedInputFile(int argc, char* const* argv)
   {
       if(argc >1)
       {
           try
           {
               std::ifstream* next{new std::ifstream{argv[1], std::ifstream::in}};
               if(next->is_open())
               {
                   lexer.switch_streams(next);
                   return true;
               }
           }
           catch(std::bad_alloc& e)
           {
               debugprint(e.what(),"");
           }
           std::cerr << argv[1] << ": cannot open input file\n";
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
       if(argc > 1)
       {
          std::string tempstr{argv[1]};

           const size_t a{tempstr.length()-2};

           tempstr[a] = '.';
           tempstr[a+1] = 'a';
           tempstr += "sm";

           debugprint("trying to open file: ", tempstr);
           try
           {
               std::ofstream* next{new std::ofstream{tempstr, std::fstream::out}};
               if(next->is_open())
               {
                   outfile = next;
                   filename = tempstr;
                   return true;
               }
           }
           catch(std::bad_alloc& e)
           {
               std::cerr << "error: cannot open file " << tempstr << " for writing\n";
               debugprint(e.what(),"");
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

#ifndef MAIN
#define MAIN
   
   int main(int argc,  char* const* argv)
   {
       Compiler compiler{};
   
       if(! compiler.openedInputFile(argc,argv) )
       {
           compiler.filename = "main.n";
           return -1;
       }
       if(!compiler.openedOutputFile(argc, argv))
       {
           return -1;
       }
       return 0;
   }
#endif
}
