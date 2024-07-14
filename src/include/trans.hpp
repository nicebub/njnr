#ifndef SRC_INCLUDE_TRANS_HPP_
#define SRC_INCLUDE_TRANS_HPP_
#include <config.h>
#include <cstdio>
#include <string>

#include "list.hpp"

namespace njnr
{
class SymbolTableX;
class CodeGenerator
{
   public:
      // Default Constructor
      CodeGenerator();
      // Constructor with given ostream reference
      explicit CodeGenerator(std::ostream& outfile);
      // Deconstructor
      ~CodeGenerator();
      // Set ostream after already Constructed
      void setstream(std::ostream* outfile);
      // Returns whether we can generate code or not
      bool canGenerateCode() const noexcept;

      // Sets Code Generator as disabled
      void stop() noexcept;
      // Sets Code Generator as enabled
      void start() noexcept;

      // label initializer - helper function
      void initializelabel(void);

      // return next available label number
      int getlabel(void);
      // generate label with label name : name
      void gen_label(std::string name);
      // generate a label with $<labelname><labelnumber>
      std::string genlabelw(std::string name, int labelnum);

      // generate a function call
      void gen_call(std::string funcname, int numargs);

      void setSymbolTable(SymbolTableX* s);
      std::string getOutputTypeForCINType(Funcb* f);
      // concat 2 strings and return the answer, remember to
      // free it when done
      static std::string concat(std::string, std::string);
      // Empties a string. Not being used currently
      static void nullout(std::string& name, int length);
      void generate(List* f);
      void generateTranslationUnit(njnr::TranslationUnitListNode* tn);
      void generateFunction(Funcb* f);
      void generateStatement(njnr::StmtListNode* e);
      void generateReturnStatement(Statement* s);
      void generateVariabledeclarations(Funcb* f);

   private:
      // Which lable number are we on in generating labels
      int            labelcounter;
      // our variable used to determine enabled/disabled
      bool           canGenerate;
      // stream for writing
      std::ostream*  outfile;
      // was our last instruction we wrote a returnf instruction
      bool           lastInstructionWasReturnf;
      SymbolTableX*   symtab;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_TRANS_HPP_
