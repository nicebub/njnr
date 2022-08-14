#include <iostream>
#include <string>
#include <iostream>
#include <fstream>

#include "debug.hpp"
#include "compiler.hpp"
namespace njnr {

bool Compiler::filenameDoesEndsInDotC(const std::string& inFilename)  noexcept {
    std::string extra{""};
    auto f_sz{ inFilename.size() };

    extra = inFilename[(f_sz-1)];
    extra += inFilename[(f_sz-2)];
    return extra == "c.";
}
bool Compiler::openedInputFile(int argc, const char** argv) {
    if(argc >1) {
        if(filenameDoesEndsInDotC(argv[1])) {
            try {
                std::ifstream* next{new std::ifstream{argv[1], std::ifstream::in}};
                if(next->is_open()) {
                    lexer.switch_streams(next);
                    return true;
                }
            }
            catch(std::bad_alloc& e) {
                debugprint(e.what(),"");
            }
            std::cerr << argv[1] << ": cannot open input file\n";
        }
        else
            std::cerr << argv[1] << ": does not end in .c\n";
    }
    else
        std::cerr << "did not recieve an input file\n";
    return false;
}

bool Compiler::openedOutputFile(int argc, const char** argv) {
    std::string tempstr{argv[1]};
    if(filenameDoesEndsInDotC(tempstr)) {
        const size_t a{tempstr.length()-2};

        tempstr[a] = '.';
        tempstr[a+1] = 'a';
        tempstr += "sm";

        debugprint("trying to open file: ", tempstr);
        try {
            std::ofstream* next{new std::ofstream{tempstr, std::fstream::out}};
            if(next->is_open()) {
                outfile = next;
                filename = tempstr;
                return true;
            }
        }
        catch(std::bad_alloc& e) {
            std::cerr << "error: cannot open file " << tempstr << " for writing\n";
            debugprint(e.what(),"");
        }
    }
    return false;
}

#ifndef MAIN
#define MAIN

int main(int argc, const char** argv) {
    Compiler compiler{};

    if(! compiler.openedInputFile(argc,argv) ) {
        compiler.filename = "main.c";
        return -1;
    }
    if(!compiler.openedOutputFile(argc, argv)) {
        return -1;
    }
    return 0;
}
}
#endif
