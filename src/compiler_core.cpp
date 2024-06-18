#include <cstdio>
#include <fstream>
#include <ostream>
#include "debug.hpp"
#include "compiler.hpp"
#include "symbol_table_stack.hpp"
namespace njnr
{
   Compiler::Compiler(): symbolTable{nullptr},
       constantTable{nulptr},
       code_generator{},
       lexer{nullptr,*this},
       parser{nullptr},
       currentFunc{nullptr},
       outfile{nullptr},
       Line_Number{1},
       globalcount{0},
       offset_counter{5},
       othercounter{1},
       param_offset{0},
       mainlocal{0},
       returnTypes{},
       founderror{false}
   {
       try
       {
           symbolTable = new SymbolTable{ *this};
           install_functions_into_symbolTable();
           constantTable = new SymbolTable{*this};
           parser = new njnrParser{*this};
           parser->set_debug_stream(std::cerr);
   #ifdef DEBUG
           parser->set_debug_level(1);
   #endif
       }
       catch(std::bad_alloc& e)
       {
           debugprint(e.what(),"");
           exit(-1);
       }
       mainlabel = code_generator.getlabel();
   }

   void Compiler::install_functions_into_symbolTable()
   {
       List* params{List::mklist("",njnr::type::VOID)};
       S_TableEntry* entry{symbolTable->createFunc("main", njnr::type::INT,params )};
       symbolTable->install(entry);
   }

   Compiler::Compiler(int argc,  char* const* argv) : Compiler{}
   {
       openedInputFile(argc,argv);
   }

   Compiler::~Compiler()
   {

       closeOrRemoveOutputFile(false);
       if(symbolTable != nullptr)
       {
           debugprint("deleteting symbol table\n","");
           delete symbolTable;
           symbolTable = nullptr;
       }
       if(constantTable != nullptr)
       {
           debugprint("deleteting constant symbol table\n","");
           delete constantTable;
           constantTable = nullptr;
       }

       if(parser != nullptr)
       {
           debugprint("deleteing parser\n","");
           delete parser;
           parser = nullptr;
       }
       currentFunc = nullptr;
   }


   int Compiler::warning(const std::string s1, const std::string s2) noexcept
   {
       std::cerr << "Warning:::"<< filename << ":"<< Line_Number << "-> " << s1 << " "
                 << s2 << "\n";
       return 0;
   }

   void Compiler::closeOrRemoveOutputFile(bool needtoremove)
   {
       if(outfile != nullptr)
       {
           outfile->flush();
           if(outfile != &std::cout)
           {
               auto file{dynamic_cast<std::ofstream*>(outfile)};
               if(file->is_open())
               {
                   debugprint("Closing file\n","");
                   file->close();
                   if(needtoremove)
                   {
                       debugprint("Removing file\n","");
                       remove(this->filename.c_str());
                   }
               }
              delete outfile;
           }
           outfile = nullptr;
       }
   }

   void  Compiler::setfinished(List* inlist)
   {
      finished = inlist;    
   }

    void  Compiler::printProgramTree(void)
    {
        std::cout << "-- Program Printout --" << std::endl;
        if(nullptr != finished)
        {
           std::cout << finished->toString() << std::endl;
        }
    }

   int Compiler::error(const std::string s1, const std::string s2) noexcept
   {
       std::cerr << "Error:::"<< filename << ":"<< Line_Number << "-> " << s1 << " "
                 << s2 << "\n";
       founderror=true;
       code_generator.stop();
       closeOrRemoveOutputFile(true);
       return 0;
   }

   std::string Compiler::getStringFromType(njnr::type t)
   {
      std::string r{"INVALID"};
      switch(t)
      {
        case njnr::type::CHAR:
           r = "CHAR";
           break;
        case njnr::type::CHECK:
           r = "CHECK";
           break;
        case njnr::type::FLOAT:
           r = "FLOAT";
           break;
        case njnr::type::IDENT:
           r = "IDENT";
           break;
        case njnr::type::INT:
           r = "INT";
           break;
        case njnr::type::REFFLOAT:
           r = "REFFLOAT";
           break;
        case njnr::type::REFINT:
           r = "REFINT";
           break;
        case njnr::type::REFSTR:
           r = "REFSTR";
           break;
        case njnr::type::STMT:
           r = "STMT";
           break;
        case njnr::type::STR:
           r = "STR";
           break;
        case njnr::type::VOID:
           r = "VOID";
           break;
        default:
           break;
      }
      return r;
   }

   constexpr bool typeisintegral(njnr::type t)
   {
    return (t == njnr::type::CHAR || t == njnr::type::FLOAT || t == njnr::type::INT);// ||
//            t == njnr::type::REFFLOAT || t == njnr::type::REFINT || t == njnr::type::REFSTR);
   }
   bool  Compiler::aresimilartypes(njnr::type t1, njnr::type t2)
   {
      if(t1 == t2)
      {
        return true;
      }
      if(typeisintegral(t1) && typeisintegral(t2))
      {
         return true;
      }
      return false;
   }

    bool Compiler::checkSingleReturnStatement(Statement *realstmt, njnr::type& foundtype, bool first)
    {
        bool success{true};
//        njnr::type found = {};
        njnr::type similar{};

        if(nullptr != realstmt)
        {
            /* make sure we only look at return statements */
            if(realstmt->getstype() == njnr::statement_type::RETURN)
            {
                std::cout << "found return type of " + getStringFromType(realstmt->getrettype()) + "\n";
                switch(realstmt->getrettype())
                {
                    case njnr::type::CHECK:
                         checkSingleReturnStatement(realstmt, similar, first);
                            if(true == first)
                            {
                                foundtype = similar;
                            }
                            else
                            {
                                std::cerr << "types are not compatible with each other: \n";
                                success = false;
                            }
                            break;
                        break;
                    default:
                        similar = Compiler::getReturnTypeFromStatement(realstmt);
                        if(true == aresimilartypes(similar, foundtype))
                        {
                            std::cout << "so far compatible...\n";
                        }
                        else
                        {
                            if(true == first)
                            {
                                foundtype = similar;
                            }
                            else
                            {
                                std::cerr << "types are not compatible with each other: \n";
                                success = false;
                            }
                            break;
                        }
                }
                if(realstmt->getrettype() == njnr::type::CHECK && (first == true))
                {
                    ReturnPacket* realType{realstmt->getexpr()};
                    if(nullptr != realType)
                    {
                        std::cout << "return type checked..... " + Compiler::getStringFromType(realType->gettype()) + "\n";

                        if(njnr::type::IDENT == realType->gettype())
                        {
                          Identifier* Id{dynamic_cast<Identifier*>(realType)};
                          std::string s{Id->getvalue()};
                          /* TODO: check symbol table for this name and get is data type to put here */
                          foundtype = njnr::type::INT;
                          first = false;
                        }
                        else if(realType->gettype() != njnr::type::CHECK)
                        {
                           foundtype = realType->gettype();
                           first = false;
                        }
                        else
                        {
                           std::cout << "needs further checking later on down road, perhaps at runtime\n";
                        }
                    }
                }
            }
            else
            {
                std::cout << "skipping non-RETURN statement statement\n";
            }
        }

        return success;
    }

    bool Compiler::checkAllFunctionReturnStatements(njnr::List* statementList, njnr::type& foundtype)
    {
        bool first{true};
        bool success{false};
        if(nullptr != statementList)
        {
            std::cout << "Calculating Return types from return statements found in function...\n";
            // go through all return statements and compare to existing return type
            //  either we set it initially here or we start to compare and find out
            //  if they all match or not.
            for(auto stmt: *statementList)
            {
                if(stmt->get_nodeType() == njnr::eNodeType::STMT)
                {
//                    Statement* realstmt{(dynamic_cast<StmtListNode*>(stmt))->getstmt()};
                    if(true != checkSingleReturnStatement((dynamic_cast<StmtListNode*>(stmt))->getstmt(), foundtype, first))
                    {
                        break;
                    }
                }
                else
                {
                    std::cout << "skipping non-STMT node\n";
                }
                if(true == first)
                {
                    first = false;
                }
            }
            success = true;
        }
        else
        {
            std::cerr << "Function body is empty\n";
        }

        return success;
    }

    void Compiler::checkfunctionReturnValues(Funcb* functionBinding)
    {
        njnr::type foundtype{njnr::type::VOID};

        // IF passed in good pointer
        if(nullptr != functionBinding)
        {
            std::cout << "current func return type: " + getStringFromType(functionBinding->getreturntype()) + "\n";
            // IF we have a function header 
            if(nullptr != functionBinding->getfuncheader())
            {
                std::cout << "given return type by programmer: " + getStringFromType(functionBinding->getfuncheader()->returntype) + "\n"; 
               functionBinding->setreturntype(functionBinding->getfuncheader()->returntype);
            }
            // IF we have a function body
            if(true == checkAllFunctionReturnStatements(functionBinding->getfuncbody_list(), foundtype))
            {
                std::cout << "Setting new return type to: " + getStringFromType(foundtype) + "\n";
               functionBinding->setreturntype(foundtype);
            }
        }
        else
        {
            std::cerr << "NULL argument\n";
        }
/*    if(nullptr != finished)
    {
       for(auto e : *finished)
       {
           TranslationUnitListNode* t{nullptr};
           if( (t = dynamic_cast<TranslationUnitListNode*>(e))->get_trans_unit_type() == njnr::trans_unit_type::FUNCTION)
           {
              Funcb* f{nullptr};
              if(nullptr != (f = t->getFunc()))
              {

              }

           }
       }
    }
    */
   }

void Compiler::installVariableIntoSymbolTable(njnr::Identifier* Id, njnr::type t)
{
   if(Id != nullptr)
   {
      S_TableEntry* te = symbolTable->createVar(Id->getvalue(), t, 0); 
      symbolTable->install(te);
   }
}
void Compiler::installParameterIntoSymbolTable(njnr::Identifier* Id, njnr::type t)
{
   if(Id != nullptr)
   {
      S_TableEntry* te = symbolTable->createParam(Id->getvalue(), t, 0); 
      symbolTable->install(te);
   }
}

}
