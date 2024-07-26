#include <config.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <ostream>
#include <iostream>

#include "CodeGenerator.hpp"
#include "List.hpp"
#include "type.hpp"
#include "cpptypes.hpp"
#include "compiler.hpp"
#include "symbol_table_stackX.hpp"
// #include "symtab.hpp"

using njnr::CodeGenerator;

CodeGenerator::CodeGenerator() : labelcounter{1},
                                 canGenerate{true},
                                 outfile{&std::cout},
                                 lastInstructionWasReturnf{false}
                                 {}

CodeGenerator::CodeGenerator(std::ostream& out) :
                                               labelcounter{1},
                                               canGenerate{true},
                                               outfile{&out},
                                               lastInstructionWasReturnf{false}
                                               {}

CodeGenerator::~CodeGenerator()
{
   report(njnr::logType::debug,
          "running CodeGenerator() Destructor");

   report(njnr::logType::debug, "labelcounter" + labelcounter);
   report(njnr::logType::debug, "canGenerate" + canGenerate);
   report(njnr::logType::debug, "lastInstructionWasReturnf" + lastInstructionWasReturnf);

}

void CodeGenerator::setSymbolTable(SymbolTableX* s)
{
   symtab = s;
}
void CodeGenerator::setstream(std::ostream* outfile)
{
    this->outfile = outfile;
}

inline void CodeGenerator::initializelabel()
{
    labelcounter = 1;
}

int CodeGenerator::getlabel()
{
    labelcounter++;
    return (labelcounter-1);
}

void CodeGenerator::nullout(std::shared_ptr<std::string> name, int length)
{
    name->clear();
}

std::string CodeGenerator::genlabelw(std::string name, int labelnum)
{
    std::string temp{"$"};
    temp += name;
    temp += std::to_string(labelnum);
    return temp;
}

void CodeGenerator::gen_label(std::string name)
{
    if (canGenerate)
    {
        *outfile << name << "\n";
        lastInstructionWasReturnf = false;
    }
}

void CodeGenerator::gen_call(std::string funcname, int numargs)
{
    if (canGenerate)
    {
        *outfile << "\tcall\t" << funcname << ", " << numargs << "\n";
        lastInstructionWasReturnf = false;
    }
}

std::string CodeGenerator::concat(std::string char1, std::string char2)
{
    return char1 + char2;
}
bool CodeGenerator::canGenerateCode() const noexcept
{
    return canGenerate;
}
void CodeGenerator::stop() noexcept
{
    canGenerate = false;
}
void CodeGenerator::start() noexcept
{
    canGenerate = true;
}

std::string CodeGenerator::getOutputTypeForCINType(std::shared_ptr<Funcb> f)
{
    std::string r{"void"};

    if (nullptr != f)
    {
       switch (f->getreturntype())
       {
        case njnr::type::STR:
         r = "char*";
         break;
        case njnr::type::INT:
           r = "int";
           break;
        case njnr::type::FLOAT:
           r = "float";
           break;
        case njnr::type::IDENT:
           /* TODO(nicebub): need to get type of identifier, possibly
                              from symbol table ? */
          r = "IDENT";
          break;
        case njnr::type::CHAR:
           r = "char";
           break;
        case njnr::type::VOID:
        default:
           r = "void";
           break;
       }
    }
    else
    {
        std::cerr << "NULL argument given: getOutputTypeForCINType\n";
    }
    return r;
}

void CodeGenerator::generateVariabledeclarations(std::shared_ptr<Funcb> f)
{
   if (f != nullptr && nullptr != symtab)
   {
      if (f->getfuncheader()->paramlist != nullptr)
      {
         for (auto p : *(f->getfuncheader())->paramlist)
         {
            if (p == nullptr)
            {
               std::cerr <<"INTERNAL ERROR\n";
            }
            std::shared_ptr<ReturnPacketListNode> RP{dynamic_pointer_cast<ReturnPacketListNode>(p)};
            if (RP == nullptr)
            {
               std::cerr <<"INTERNAL ERROR\n";
            }
            else
            if (RP->getexpr() == nullptr)
            {
               std::cerr << "INTERNAL ERROR: rp->getexpr()\n";
            }
            else
            {
            std::shared_ptr<Identifier> Id{dynamic_pointer_cast<Identifier>(RP->getexpr())};
            if (Id == nullptr)
            {
               std::cerr <<"INTERNAL ERROR\n";
            }
            std::string name{Id->getvalue()};
            if (name.empty())
            {
               std::cerr <<"INTERNAL ERROR\n";
            }
            std::shared_ptr<ReturnPacket> r = reinterpret_pointer_cast<ReturnPacket>(symtab->
                                                              lookup(name));
            if (r == nullptr)
            {
               std::cerr <<"INTERNAL ERROR\n";
            }
            if (nullptr != r)
            {
               std::cerr << "FOUND parameter in symbol table\n";
            }
            else
            {
               std::cerr << "did not find parameter in symbol table\n";
            }
            }
         }
      }
   }
   else
   {
      std::cerr << "NULL argument given: generateVariabledeclarations\n";
   }
}
void CodeGenerator::generateReturnStatement(std::shared_ptr<Statement> s)
{
   if (nullptr != s)
   {
      if (s->getstype() == njnr::statement_type::RETURN)
      {
         njnr::type m{njnr::type::VOID};

         *outfile << "return";
         if (s->getrettype() == njnr::type::CHECK)
         {
            m = s->getexpr()->gettype();
         }
         else
         {
            m = s->getrettype();
         }
         switch (m)
         {
            case njnr::type::VOID:
               std::cout << "found void return type\n";
               break;
            case njnr::type::CHAR:
               std::cout << "found Char constant return type\n";
               *outfile << " \'" +
                           std::string{dynamic_pointer_cast<Constant>(s->
                                                               getexpr())->
                                                               getValue()} +
                           "\'";
               break;
            case njnr::type::INT:
               std::cout << "found Integer constant return type\n";
               if (dynamic_pointer_cast<Constant>(s->getexpr()) != NULL)
               {
                  *outfile << " " + dynamic_pointer_cast<Constant>(s->
                                                            getexpr())->
                                                            getValue();
               }
               else
               {
                  *outfile << " " + std::to_string(0);
               }
               break;
            case njnr::type::FLOAT:
               std::cout << "found Float constant return type\n";
               *outfile << " " + dynamic_pointer_cast<Constant>(s->getexpr())->
                                                            getValue();
               break;
            case njnr::type::STR:
               std::cout << "found Constant String return\n";
               *outfile << " \"" + dynamic_pointer_cast<Constant>(s->
                                                           getexpr())->
                                                           getValue() +
                           "\"";
               break;
            case njnr::type::IDENT:
               std::cout << "found Identifier return\n";
               *outfile << " " + dynamic_pointer_cast<Identifier>(s->
                                                           getexpr())->
                                                           getValue();
               break;
            default:
               std::cout << "error in return type? " +
                            Compiler::getStringFromType(s->getrettype())+"\n";
               break;
         }
         *outfile << ";\n";
      }
      else
      {
         std::cerr << "trying to generate a return statement " \
                      "from a different type of statement\n";
      }
   }
   else
   {
      std::cerr << "NULL argument given: generateReturnStatement\n";
   }
}

void CodeGenerator::generateStatement(std::shared_ptr<njnr::StmtListNode> e)
{
   if (nullptr != e)
   {
      std::shared_ptr<Statement> s{e->getstmt()};
      if (nullptr != s)
      {
         if (njnr::statement_type::RETURN == s->getstype())
         {
            generateReturnStatement(s);
         }
         else
         {
            std::cout << "not implemented yet\n";
         }
      }
      else
      {
         std::cerr << "statement is NULL!!\n";
      }
   }
   else
   {
    std::cerr << "NULL argument given: generateStatement\n";
   }
}

void CodeGenerator::generateFunction(std::shared_ptr<Funcb> f)
{
   if (nullptr != f)
   {
      *outfile << getOutputTypeForCINType(f);
      *outfile << " ";
      *outfile << f->getfuncheader()->name + "(";
      /* TODO: write out parameters */
      if (nullptr != f->getfuncheader() &&
          f->getfuncheader()->paramlist == nullptr)
      {
        *outfile << "void";
      }
      *outfile << ")\n{\n";
      if (f->getfuncbody_list() != nullptr)
      {
//        generateVariabledeclarations(f);
        std::shared_ptr<List> l{f->getfuncbody_list()};
         for (auto e : *l)
         {
            if (nullptr != e)
            {
               if (njnr::eNodeType::EXPR == e->get_nodeType())
               {
                  std::cout << "TODO working on Expressions\n";
                  /* TODO: generate expression */
               }
               else if (njnr::eNodeType::STMT == e->get_nodeType())
               {
                  generateStatement(dynamic_pointer_cast<njnr::StmtListNode>(e));
               }
               else
               {
                  std::cerr << "Invalid Node type at this point in time\n";
               }
            }
         }
      }
      else
      {
         std::cout << "function body empty\n";
      }
      *outfile <<"";
      *outfile << "\n}\n";
   }
   else
   {
      std::cerr << "NULL argument given: generateFunction\n";
   }
}
void CodeGenerator::generateTranslationUnit(std::shared_ptr<njnr::TranslationUnitListNode> tn)
{
    if (nullptr != tn)
    {
       if (njnr::trans_unit_type::FUNCTION == tn->get_trans_unit_type())
       {
          generateFunction(tn->getFunc());
       }
       else if (njnr::trans_unit_type::VARDECL == tn->get_trans_unit_type())
       {
          std::cout << "not implemented yet\n";
       }
       else
       {
          std::cerr << "invalid tranlation unit type\n";
       }
    }
    else
    {
        std::cerr << "Null Argument given: generateTranslationUnit\n";
    }
}
void CodeGenerator::generate(std::shared_ptr<List> f)
{
    if (nullptr != f)
    {
       for (auto e : *f)
       {
         if (nullptr != e)
         {
            if (njnr::eNodeType::TRANSLATION_UNIT == e->get_nodeType())
            {
               generateTranslationUnit(\
                                 dynamic_pointer_cast<njnr::TranslationUnitListNode>(e));
            }
            else
            {
               std::cerr << "Node type should not be at this level\n";
            }
         }
       }
    }
    else
    {
       std::cerr << "NULL argument given: generate\n";
    }
}
