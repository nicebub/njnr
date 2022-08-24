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
    founderror{false},
    returnTypes{}
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

Compiler::Compiler(int argc, const char** argv) : 	Compiler{}
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
        }
        delete outfile;
        outfile = nullptr;
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
}
