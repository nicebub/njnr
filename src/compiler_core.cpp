#include <cstdio>
#include <fstream>
#include <ostream>
#include "debug.hpp"
#include "compiler.hpp"

namespace njnr
{
   Compiler::Compiler(): mysymtab{nullptr},
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
           mysymtab = new SymbolTable{ *this};
           install_functions_into_symbolTable();
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
       TableEntry* entry{mysymtab->createFunc("main", njnr::type::INT,params )};
       mysymtab->install(entry);
   }

   Compiler::Compiler(int argc,  char* const* argv) : 	Compiler{}
   {
       openedInputFile(argc,argv);
   }

   Compiler::~Compiler()
   {

       closeOrRemoveOutputFile(false);
       if(mysymtab != nullptr)
       {
           debugprint("deleteting symbol table\n","");
           delete mysymtab;
           mysymtab = nullptr;
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

   void Compiler::checkfunctionReturnValues(Funcb* f)
   {
    if(nullptr != f)
    {
        std::cout << "current func return type: " + getStringFromType(f->getreturntype()) + "\n";
        if(nullptr != f->getfuncheader())
        {
            std::cout << "given return type by programmer: " + getStringFromType(f->getfuncheader()->returntype) + "\n"; 
        }
        if(nullptr != f->getfuncbody_list())
        {
            njnr::type foundtype{njnr::type::VOID};
            bool first{true};
            bool success{true};
            std::cout << "Calculating Return types from return statements found in function...\n";
            for(auto e: *f->getfuncbody_list())
            {
                if(e->get_nodeType() == njnr::eNodeType::STMT)
                {
                    StmtListNode *s{dynamic_cast<StmtListNode*>(e)};
                    Statement* st{s->getstmt()};
                    if(nullptr != st)
                    {
                        if(st->getstype() == njnr::statement_type::RETURN)
                        {
                            std::cout << "found return type of " + getStringFromType(st->getrettype()) + "\n";
                            if(st->getrettype() == njnr::type::CHECK && (first == true))
                            {
                               ReturnPacket* rt{st->getstmt()};
                               if(nullptr != rt)
                               {
                                  std::cout << "return type checked..... " + Compiler::getStringFromType(rt->gettype()) + "\n";

                                  if(njnr::type::IDENT == rt->gettype())
                                  {
                                    Identifier* Id{dynamic_cast<Identifier*>(rt)};
                                    std::string s{Id->getvalue()};
                                    /* TODO: check symbol table for this name and get is data type to put here */
                                    foundtype = njnr::type::INT;
                                    first = false;

                                  }
                                  else if(rt->gettype() != njnr::type::CHECK)
                                  {
                                     foundtype = rt->gettype();
                                     first = false;
                                  }
                                  else
                                  {
                                     std::cout << "needs further checking later on down road, perhaps at runtime\n";
                                  }

                               }
                            }
                            else if(first)
                            {
                                foundtype = Compiler::getReturnTypeFromStatement(st);
                                first = false;
                            }
                            else
                            {
                                if(aresimilartypes(Compiler::getReturnTypeFromStatement(st), foundtype))
                                {
                                   std::cout << "so far compatible...\n";
                                }
                                else
                                {
                                    std::cerr << "types are not compatible with each other: \n";
                                    success = false;
                                }
                            }
                        }
                        else
                        {
                            std::cout << "skipping non-RETURN statement statement\n";
                        }
                    }
                }
                else
                {
                    std::cout << "skipping non-STMT node\n";
                }
            }
            if(success == true)
            {
                std::cout << "Setting new return type to: " + getStringFromType(foundtype) + "\n";
               f->setreturntype(foundtype);
            }
        }
        else
        {
            std::cerr << "Function body is empty\n";
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
}
