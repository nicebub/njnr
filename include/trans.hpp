#ifndef _MYTRANS_H
#define _MYTRANS_H
#include <cstdio>
#include <string>

#include "list.hpp"
namespace njnr
{
   class CodeGenerator
   {
      public:
         CodeGenerator();                                         // Default Constructor
         CodeGenerator(std::ostream& outfile);                    // Constructor with given ostream reference
         ~CodeGenerator();                                        // Deconstructor
         void setstream(std::ostream* outfile);                   // Set ostream after already Constructed
         bool canGenerateCode() const noexcept;                   // Returns whether we can generate code or not
         void stop() noexcept;                                    // Sets Code Generator as disabled
         void start() noexcept;                                   // Sets Code Generator as enabled

         void initializelabel(void);                              // label initializer - helper function
         int getlabel(void); 	                                    // return next available label number
         void gen_label(std::string name);	                     // generate label with label name : name
         std::string genlabelw(std::string name, int labelnum);   // generate a label with $<labelname><labelnumber>

         void gen_call(std::string funcname, int numargs);        // generate a function call

         static std::string concat(std::string, std::string);	    // concat 2 strings and return the answer, remember to free it when done
         static void nullout(std::string& name, int length);       // Empties a string. Not being used currently
         void generate(List* f);
         void generateTranslationUnit(njnr::TranslationUnitListNode* tn);
         void generateFunction(Funcb* f);
      private:
         int 				labelcounter;                              // Which lable number are we on in generating labels
         bool				canGenerate;                               // our variable used to determine enabled/disabled
         std::ostream* 	outfile;                                   // stream for writing
         bool           lastInstructionWasReturnf;                 // was our last instruction we wrote a returnf instruction
   };
};
#endif // _MYTRANS_H
