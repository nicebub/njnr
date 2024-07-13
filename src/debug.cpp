#include <config.h>
#include <iostream>

#include "debug.hpp"

using namespace njnr;


#ifdef DEBUG
int Debug::yydebug = 1;
#else
int Debug::yydebug = 0;

#endif
namespace njnr
{

   Debug::Debug() {}

   Debug::~Debug() {}

   int Debug::get_yydebug()
   {
       return yydebug;
   }
   void Debug::set_yydebug(const int value)
   {
       yydebug = value;
   }

  #ifdef DEBUG
   void debugprint(std::string s1, std::string s2)
   {
       if(!s1.empty() && !s2.empty())
       {
           std::cerr << "---Debug---\n" << s1 << "\"" << s2 << "\"\n" << "---Debug---\n";
       }
       else if(!s1.empty() && s2.empty())
       {
           std::cerr << "---Debug---\n" << s1 << "\n" << "---Debug---\n";
       }
   }
   void debugprint(std::string s1, int s2)
   {
       if(!s1.empty())
       {
           std::cerr << "---Debug---\n" << s1 << "\"" << s2 << "\"\n" << "---Debug---\n";
       }
   }

  #endif

}