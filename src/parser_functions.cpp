#include <config.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "debug.hpp"
#include "compiler.hpp"
#include "njnr.tab.hpp"

namespace njnr
{
   void Compiler::block1_start_trans_unit()
   {
       code_generator.gen_label("main");
       code_generator.gen_call(code_generator.genlabelw("main", mainlabel), 0);
   }

   void Compiler::variableFetch(std::shared_ptr<ReturnPacket> inPacket, bool conversionNeeded)
   {
       if (inPacket->getlval())
       {
           static const std::string fetch{"fetch"};
           switch (inPacket->gettype())
           {
           case type::INT:
               break;

           case type::FLOAT:

           default:
               if (conversionNeeded) {;}
               break;
           }
       }
   }
   void Compiler::variableFetchWithNumericCheck(std::shared_ptr<ReturnPacket> inPacket,
                                                bool conversionNeeded)
   {
       if (inPacket->getnumeric())
       {
           variableFetch(inPacket, conversionNeeded);
       }
   }
   void Compiler::normalStore(njnr::type intype)
   {
       switch (intype)
       {
       case(njnr::type::INT):
           break;
       case(njnr::type::FLOAT):
           break;
       default:
           break;
       }
   }
   void Compiler::variableStore(njnr::type intype)
   {
       static std::string instruction{""};
       static std::string letter{""};
       switch (intype)
       {
       case njnr::type::INT:
           instruction = "int";
           letter = "I";
           break;
       case njnr::type::FLOAT:
           instruction = "flt";
           letter = "R";
           break;
       default:
           break;
       }
       warning("expressons are of different type, data may be lost", "");
   }

   void Compiler::variableFetchWithNumericCheckAndLvalCheck(\
                                              std::shared_ptr<ReturnPacket> insimplePacket,
                                              bool conversionNeeded)
   {
       if (insimplePacket->getlval())
       {
           variableFetchWithNumericCheck(insimplePacket, conversionNeeded);
       }
   }
}  // namespace njnr
