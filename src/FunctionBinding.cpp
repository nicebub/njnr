#include <string>

#include "type.hpp"
#include "FunctionBinding.hpp"
#include "Compiler.hpp"
using namespace njnr;
   Funcb::Funcb() : param_type{},
       returntype{njnr::type::VOID},
       bodydef{false},
       num_param{0},
       label{0},
       localcount{0},
       actual_num{0},
       funcheader{nullptr},
       funcbody_list{nullptr}
   {}
   Funcb::Funcb(njnr::type returntype, bool bodydef, int num_param,
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
   Funcb::Funcb(njnr::type returntype) : Funcb{}
   {
       this->returntype = returntype;
   }
   Funcb::Funcb(const Funcb& in) :
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
       setvalue(in.getvalue());
   }

   Funcb& Funcb::operator=(const Funcb& in)
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
           setvalue(in.getvalue());
       }
       return *this;
   }
   Funcb::~Funcb()
   {
      report(njnr::logType::debug, "running Funcb() destructor");
      report(njnr::logType::debug, "Funcb:" + this->toString());
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
   std::vector<njnr::type> Funcb::getparam_type()
   {
       return param_type;
   }
   njnr::type Funcb::getreturntype()
   {
       return returntype;
   }
   bool Funcb::getbodydef()
   {
       return bodydef;
   }
   int Funcb::getnum_param()
   {
       return num_param;
   }
   int Funcb::getlabel()
   {
       return label;
   }
   int Funcb::getlocalcount()
   {
       return localcount;
   }
   int Funcb::getactual_num()
   {
       return actual_num;
   }
   void Funcb::Funcb::setparam_type(std::vector<njnr::type> param_type)
   {
       this->param_type = param_type;
   }
   void Funcb::setreturntype(njnr::type returntype)
   {
       this->returntype = returntype;
   }
   void Funcb::setbodydef(bool bodydef)
   {
       this->bodydef = bodydef;
   }
   void Funcb::setnum_param(int num_param)
   {
       this->num_param = num_param;
   }
   void Funcb::setlabel(int label)
   {
       this->label = label;
   }
   void Funcb::setlocalcount(int localcount)
   {
       this->localcount = localcount;
   }
   void Funcb::setactual_num(int actual_num )
   {
       this->actual_num = actual_num;
   }

   void Funcb::setfuncbody_list(std::shared_ptr<List> funcbody)
   {
      funcbody_list = funcbody;
   }
   std::shared_ptr<List> Funcb::getfuncbody_list(void)
   {
    return funcbody_list;
   }
   void Funcb::setfuncheader(std::shared_ptr<funcheadertype> funcheader)
   {
      this->funcheader = funcheader;
   }
   std::shared_ptr<funcheadertype> Funcb::getfuncheader(void)
   {
    return funcheader;
   }
   const std::string Funcb::toString() const
   {
    /**
         std::vector<njnr::type> param_type;
         type   returntype;
         bool   bodydef;
         int    num_param;
         int    label;
         int    localcount;
         int    actual_num;
         std::shared_ptr<funcheadertype> funcheader;
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
