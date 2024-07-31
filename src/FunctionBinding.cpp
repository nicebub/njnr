#include <config.h>
#include <string>

#include "type.hpp"
#include "FunctionBinding.hpp"
#include "Compiler.hpp"
using njnr::FunctionBinding;
using njnr::ReturnPacket;
using njnr::Compiler;
using njnr::report;

   FunctionBinding::FunctionBinding() : param_type{},
       returntype{njnr::type::VOID},
       bodydef{false},
       num_param{0},
       label{0},
       localcount{0},
       actual_num{0},
       funcheader{nullptr},
       funcbody_list{nullptr}
   {}
   FunctionBinding::FunctionBinding(njnr::type returntype, bool bodydef, int num_param,
                std::vector<njnr::type> param_type, int label,
                int localcount, int actual_num) :
       param_type{param_type},
       returntype{returntype},
       bodydef{bodydef},
       num_param{num_param},
       label{label},
       localcount{localcount},
       actual_num{actual_num},
       funcheader{nullptr},
       funcbody_list{nullptr}
   {}
   FunctionBinding::FunctionBinding(njnr::type returntype) : FunctionBinding{}
   {
       this->returntype = returntype;
   }
   FunctionBinding::FunctionBinding(const FunctionBinding& in) :
       param_type{in.param_type},
       returntype{in.returntype},
       bodydef{in.bodydef},
       num_param{in.num_param},
       label{in.label},
       localcount{in.localcount},
       actual_num{in.actual_num},
       funcheader{in.funcheader},
       funcbody_list{in.funcbody_list}
   {
       setName(in.getName());
   }

   FunctionBinding& FunctionBinding::operator=(const FunctionBinding& in)
   {
       if (&in != this) {
           returntype = in.returntype;
           bodydef = in.bodydef;
           num_param = in.num_param;
           label = in.label;
           localcount = in.localcount;
           actual_num = in.actual_num;
           param_type = in.param_type;
           funcheader = in.funcheader;
           funcbody_list = in.funcbody_list;
           setName(in.getName());
       }
       return *this;
   }
   FunctionBinding::~FunctionBinding()
   {
      report(njnr::logType::debug, "running FunctionBinding() destructor");
      report(njnr::logType::debug, "FunctionBinding:" + this->toString());
/*
      report(njnr::logType::debug,
             "bodydef"+ bodydef);
      report(njnr::logType::debug,
             "num_param"+ num_param);
      report(njnr::logType::debug,
             "label"+ label);
      report(njnr::logType::debug,
             "localcount"+ localcount);
      report(njnr::logType::debug,
             "actual_num"+ actual_num);
*/
      param_type.clear();
      funcbody_list = nullptr;
      funcheader = nullptr;
    }
   std::vector<njnr::type> FunctionBinding::getparam_type()
   {
       return param_type;
   }
   njnr::type FunctionBinding::getreturntype()
   {
       return returntype;
   }
   bool FunctionBinding::getbodydef()
   {
       return bodydef;
   }
   int FunctionBinding::getnum_param()
   {
       return num_param;
   }
   int FunctionBinding::getlabel()
   {
       return label;
   }
   int FunctionBinding::getlocalcount()
   {
       return localcount;
   }
   int FunctionBinding::getactual_num()
   {
       return actual_num;
   }
   void FunctionBinding::FunctionBinding::setparam_type(std::vector<njnr::type> param_type)
   {
       this->param_type = param_type;
   }
   void FunctionBinding::setreturntype(njnr::type returntype)
   {
       this->returntype = returntype;
   }
   void FunctionBinding::setbodydef(bool bodydef)
   {
       this->bodydef = bodydef;
   }
   void FunctionBinding::setnum_param(int num_param)
   {
       this->num_param = num_param;
   }
   void FunctionBinding::setlabel(int label)
   {
       this->label = label;
   }
   void FunctionBinding::setlocalcount(int localcount)
   {
       this->localcount = localcount;
   }
   void FunctionBinding::setactual_num(int actual_num )
   {
       this->actual_num = actual_num;
   }

   void FunctionBinding::setfuncbody_list(std::shared_ptr<List> funcbody)
   {
      funcbody_list = funcbody;
   }
   std::shared_ptr<List> FunctionBinding::getfuncbody_list(void)
   {
    return funcbody_list;
   }
   void FunctionBinding::setfuncheader(std::shared_ptr<FunctionHeader> funcheader)
   {
      this->funcheader = funcheader;
   }
   std::shared_ptr<FunctionHeader> FunctionBinding::getfuncheader(void)
   {
    return funcheader;
   }
   const std::string FunctionBinding::toString() const
   {
    /**
         std::vector<njnr::type> param_type;
         type   returntype;
         bool   bodydef;
         int    num_param;
         int    label;
         int    localcount;
         int    actual_num;
         std::shared_ptr<FunctionHeader> funcheader;
         std::shared_ptr<List> funcbody_list;
     */

      std::string r{};
      r += "Currently Set Return Type: ";
      r += Compiler::getStringFromType(returntype);
      r += "bodydef:? " + (true == bodydef) ? "true\n" : "false\n";
      r += "label: " + std::to_string(label) + "\n";
      r += "localcount: " + std::to_string(localcount) + "\n";
      r += "actual_num" + std::to_string(actual_num) + "\n";
      r += "num_param" + std::to_string(num_param) + "\n";
      if (0 <= param_type.size())
      {
        for (auto t : param_type)
        {
            r += "param type: " + njnr::typeToStringMap.at(t) + "\n"; 
        }
      }
/* TODO : params list vector */
      if (nullptr != funcheader)
      {
         r += funcheader->toString() + "\n";
      }
      if (nullptr != funcbody_list)
      {
         r += funcbody_list->toString();
      }
      return r;
   }
