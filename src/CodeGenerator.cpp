#include <config.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <ostream>
#include <iostream>

#include "CodeGenerator.hpp"
#include "List.hpp"
#include "ListNode.hpp"
#include "type.hpp"
#include "Statement.hpp"
#include "Compiler.hpp"
#include "ReturnPacket.hpp"
#include "symbol_table_stackX.hpp"
#include "StatementListNode.hpp"
// #include "symtab.hpp"
#include "ReturnPacketListNode.hpp"
#include "TranslationUnitListNode.hpp"

using njnr::CodeGenerator;
using njnr::StmtListNode;

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

std::string CodeGenerator::getOutputTypeForCINType(std::shared_ptr<FunctionBinding> f)
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
        report(njnr::logType::debug, "NULL argument given: getOutputTypeForCINType");
    }
    return r;
}

void CodeGenerator::generateVariabledeclarations(std::shared_ptr<FunctionBinding> f)
{
   if (f != nullptr && nullptr != symtab)
   {
      if (f->getfuncheader()->paramlist != nullptr)
      {
         for (auto p : *(f->getfuncheader())->paramlist)
         {
            if (p == nullptr)
            {
               report(njnr::logType::error, "INTERNAL ERROR");
            }
            std::shared_ptr<ReturnPacketListNode> RP{dynamic_pointer_cast<ReturnPacketListNode>(p)};
            if (RP == nullptr)
            {
               report(njnr::logType::error, "INTERNAL ERROR");
            }
            else
            if (RP->getexpr() == nullptr)
            {
               report(njnr::logType::error, "INTERNAL ERROR: rp->getexpr()");
            }
            else
            {
            std::shared_ptr<Identifier> Id{dynamic_pointer_cast<Identifier>(RP->getexpr())};
            if (Id == nullptr)
            {
               report(njnr::logType::error, "INTERNAL ERROR");
            }
            std::string name{Id->getName()};
            if (name.empty())
            {
               report(njnr::logType::error, "INTERNAL ERROR");
            }
            std::shared_ptr<ReturnPacket> r = reinterpret_pointer_cast<ReturnPacket>(symtab->
                                                              lookup(name));
            if (r == nullptr)
            {
               report(njnr::logType::error, "INTERNAL ERROR");
            }
            if (nullptr != r)
            {
               report(njnr::logType::debug, "FOUND parameter in symbol table");
            }
            else
            {
               report(njnr::logType::debug, "did not find parameter in symbol table");
            }
            }
         }
      }
   }
   else
   {
      report(njnr::logType::debug, "NULL argument given: generateVariabledeclarations");
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
               report(njnr::logType::debug, "found void return type");
               break;
            case njnr::type::CHAR:
               report(njnr::logType::debug, "found Char constant return type");
               *outfile << " \'" +
                           std::string{dynamic_pointer_cast<Constant>(s->
                                                               getexpr())->
                                                               getValue()} +
                           "\'";
               break;
            case njnr::type::INT:
               report(njnr::logType::debug, "found Integer constant return type");
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
               report(njnr::logType::debug, "found Float constant return type");
               *outfile << " " + dynamic_pointer_cast<Constant>(s->getexpr())->
                                                            getValue();
               break;
            case njnr::type::STR:
               report(njnr::logType::debug, "found Constant String return");
               *outfile << " \"" + dynamic_pointer_cast<Constant>(s->
                                                           getexpr())->
                                                           getValue() +
                           "\"";
               break;
            case njnr::type::IDENT:
               report(njnr::logType::debug, "found Identifier return");
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
         report(njnr::logType::error, "trying to generate a return statement " \
                      "from a different type of statement");
      }
   }
   else
   {
      report(njnr::logType::debug, "NULL argument given: generateReturnStatement");
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
            report(njnr::logType::info, "-INFO--> not implemented yet");
         }
      }
      else
      {
         report(njnr::logType::error, "statement is NULL!!");
      }
   }
   else
   {
    report(njnr::logType::debug, "NULL argument given: generateStatement");
   }
}

void CodeGenerator::generateFunction(std::shared_ptr<FunctionBinding> f)
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
                  report(njnr::logType::debug, "TODO working on Expressions");
                  /* TODO: generate expression */
               }
               else if (njnr::eNodeType::STMT == e->get_nodeType())
               {
                  generateStatement(dynamic_pointer_cast<njnr::StmtListNode>(e));
               }
               else
               {
                  report(njnr::logType::error, "Invalid Node type at this point in time");
               }
            }
         }
      }
      else
      {
         report(njnr::logType::debug, "function body empty");
      }
      *outfile <<"";
      *outfile << "\n}\n";
   }
   else
   {
      report(njnr::logType::debug, "NULL argument given: generateFunction");
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
          report(njnr::logType::info, "-INFO--> not implemented yet");
       }
       else
       {
          report(njnr::logType::error, "invalid tranlation unit type");
       }
    }
    else
    {
        report(njnr::logType::debug, "Null Argument given: generateTranslationUnit");
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
               report(njnr::logType::error, "Node type should not be at this level");
            }
         }
       }
    }
    else
    {
       report(njnr::logType::debug, "NULL argument given: generate");
    }
}
