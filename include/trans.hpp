#ifndef _MYTRANS_H
#define _MYTRANS_H
#include <cstdio>
#include <string>

namespace njnr
{
class CodeGenerator
{
public:
    CodeGenerator();
    CodeGenerator(std::ostream& outfile);
    ~CodeGenerator();
    void initializelabel(void);
    void setstream(std::ostream* outfile);
    int getlabel(void); 	                                    // return next available label number
    void gen_label(std::string name);	                     // generate label with label name : name
    std::string genlabelw(std::string name, int labelnum);   // generate a label with $<labelname><labelnumber>
    void gen_instr(std::string name); 	                     // for instructions without arguments
    void gen_instr_I(std::string name, int arg);             // for instructions with arguments
    void gen_instr_S(std::string name, std::string inS); 	   // used for jump command
    void gen_instr_F(std::string name, float arg);	         // use for float
    void gen_call(std::string funcname, int numargs);
    void gen_instr_tI(std::string name, int arg1, int arg2);
    bool canGenerateCode() const noexcept;
    void stop() noexcept;
    void start() noexcept;
    static std::string concat(std::string, std::string);	    // concat 2 strings and return the answer, remember to free it when done
    static void nullout(std::string& name, int length);
private:
    int 				labelcounter;
    bool				canGenerate;
    std::ostream* 	outfile;
    bool           lastInstructionWasReturnf;
};
}
#endif // _MYTRANS_H
