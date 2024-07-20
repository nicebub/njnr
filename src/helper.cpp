#include <config.h>
#include "helper.hpp"
#include "compiler.hpp"
#include "symbol_table_stack.hpp"
#include "symbol_table_stackX.hpp"
namespace njnr
{

   #define error_and_return_false(x) error((x), ""); \
      return false

   void Compiler::install_parameters_into_symbol_table_curren_scope(\
                                              std::shared_ptr<funcheadertype> inFuncHeaderptr)
   {
      std::shared_ptr<funcheadertype> inFuncHeader{inFuncHeaderptr};
      for (auto element : *inFuncHeader->paramlist)
      {
         std::shared_ptr<PListNode> nelement{dynamic_pointer_cast<PListNode>(element)};
         auto tempEntry = symbolTable->createParam(nelement->getval(),
                                                   nelement->gettype(),
                                                   (offset_counter));
         symbolTable->install(tempEntry);
         if (nelement->gettype() != njnr::type::VOID)
         {
            offset_counter++;
         }
      }
   }
   bool Compiler::is_function_decl_or_def_accurate(\
                                     std::shared_ptr<funcheadertype> inFuncHeaderptr,
                                                   bool isdeclaration)
   {
      std::shared_ptr<funcheadertype> inFuncHeader{inFuncHeaderptr};

      currentFunc = static_pointer_cast<Funcb>(symbolTable->lookup(inFuncHeader->name));

      std::shared_ptr<S_TableEntryX> foundPacket = static_pointer_cast<S_TableEntryX>(symbolTable->
                                                     lookupB(inFuncHeader->
                                                     name));
/*
      if(!foundPacket)
      {
         error_and_return_false("Function name not in symbol symbolTable");
      }
*/
      if (foundPacket->getGroup() != njnr::btype::FUNC)
      {
         error_and_return_false("Not a function");
      }
      if (currentFunc->getreturntype() != inFuncHeader->returntype)
      {
         error_and_return_false("Function declared with different return type");
      }
      if (currentFunc->getnum_param() == -1)
      {
         error_and_return_false("Function cannot have those parameters");
      }
      if (inFuncHeader->paramlist != nullptr &&
          (inFuncHeader->paramlist->size()) != currentFunc->getnum_param())
      {
         error_and_return_false("Function has different number of parameters");
      }
      int list_index{0};
      for (auto element : * inFuncHeader->paramlist)
      {
         std::shared_ptr<PListNode> nelement{dynamic_pointer_cast<PListNode>(element)};
         if (currentFunc->getparam_type()[list_index] != nelement->gettype())
         {
            std::cerr << "Error: Line: " << Line_Number << ": argument " <<
                         (list_index+1) << ": has different parameter type " \
                                           "than in function declaration\n";
           #ifdef DEBUG
           //  std::cerr << "\nThey are " <<
           //               currentFunc->getparam_type()[list_index] <<
           //               " and " << nelement->gettype() << std::endl ;
           #endif
            return false;
         }
         list_index++;
      }
      if (list_index != inFuncHeader->paramlist->size())
      {
         error_and_return_false("Stopped");
      }
      if (currentFunc->getbodydef() && (!isdeclaration))
      {
         error_and_return_false("Function definition is previously declared");
      }

      return true;
   }
   #undef error_and_return_false
}  // namespace njnr

