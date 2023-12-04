#include "helper.hpp"
#include "compiler.hpp"
#include "symbol_table_stack.hpp"
namespace njnr
{

   #define error_and_return_false(x) error((x),""); \
   	return false

   void Compiler::install_parameters_into_symbol_table_curren_scope(funcheadertype** inFuncHeaderptr)
   {
      funcheadertype* inFuncHeader{*inFuncHeaderptr};
      for(auto element : *inFuncHeader->paramlist)
      {
         PListNode* nelement{dynamic_cast<PListNode*>(element)};
         auto tempEntry = mysymtab->createParam(nelement->getval(), nelement->gettype(),(offset_counter));
         mysymtab->install(tempEntry);
         if(nelement->gettype() != njnr::type::VOID)
         {
            offset_counter++;
         }
      }
   }
   bool Compiler::is_function_decl_or_def_accurate(funcheadertype** inFuncHeaderptr, bool isdeclaration)
   {
      funcheadertype* inFuncHeader{*inFuncHeaderptr};

      currentFunc = static_cast<Funcb*>(mysymtab->lookup(inFuncHeader->name));
      auto foundPacket{mysymtab->lookupB(inFuncHeader->name)};

      if(!foundPacket)
      {
         error_and_return_false("Function name not in symbol mysymtab");
      }
      if(foundPacket->getGroup() != njnr::btype::FUNC)
      {
         error_and_return_false("Not a function");
      }
      if(currentFunc->getreturntype() != inFuncHeader->returntype)
      {
         error_and_return_false("Function declared with different return type");
      }
      if(currentFunc->getnum_param() == -1)
      {
         error_and_return_false("Function cannot have those parameters");
      }
      if(inFuncHeader->paramlist != nullptr &&
         (inFuncHeader->paramlist->size()) != currentFunc->getnum_param())
      {
         error_and_return_false("Function has different number of parameters");
      }
      int list_index{0};
      for(auto element : * inFuncHeader->paramlist)
      {
         PListNode* nelement{dynamic_cast<PListNode*>(element)};
         if(currentFunc->getparam_type()[list_index] != nelement->gettype())
         {
            std::cerr << "Error: Line: " << Line_Number << ": argument " << (list_index+1) << ": has different parameter type than in function declaration\n";
           #ifdef DEBUG
           //				std::cerr << "\nThey are " <<  currentFunc->getparam_type()[list_index] << " and " << nelement->gettype() << std::endl ;
           #endif
            return false;
         }
         list_index++;
      }
      if(list_index != inFuncHeader->paramlist->size())
      {
         error_and_return_false("Stopped");
      }
      if(currentFunc->getbodydef() && ( ! isdeclaration) )
      {
         error_and_return_false("Function definition is previously declared");
      }

      return true;
   }
   #undef error_and_return_false
}
