#include <config.h>
#include "cpptypes.hpp"
#include "type.hpp"
#include "list.hpp"
#include "symbol_table_entry.hpp"
#include "compiler.hpp"
namespace njnr
{
   ReturnPacket::ReturnPacket() :
       params{0},
       offset{0},
       lval{false},
       numeric{false},
       ttype{njnr::type::INT}
   {}

   ReturnPacket::ReturnPacket(bool lval,
                              njnr::type ttype = njnr::type::INT,
                              bool ifnum = false,
                              int inoffset = 0) :
       params{0},
       offset{inoffset},
       lval{lval},
       numeric{ifnum},
       ttype{ttype}
   {}

   const bool ReturnPacket::getlval() const
   {
       return lval;
   }
   void ReturnPacket::setlval(const bool in)
   {
       lval = in;
   }
   const njnr::type  ReturnPacket::gettype() const
   {
       return ttype;
   }
   void ReturnPacket::settype(const njnr::type in)
   {
       ttype = in;
   }
   const bool ReturnPacket::getnumeric() const {
       return numeric;
   }
   void ReturnPacket::setnumeric(const bool in)
   {
       numeric = in;
   }
   int ReturnPacket::getoffset() const
   {
       return offset;
   }
   void ReturnPacket::setoffset(const int in)
   {
       offset = in;
   }

   const std::string ReturnPacket::toString() const
   {
    /**
         int offset;
         bool lval;
         bool numeric;
         njnr::type ttype;

         struct Pair m_pair;
         S_TableEntry* funcent;
         int params;
     */
      std::string r{"lval: "};
      r += (lval == true ? "true" : "false");
      r += "\noffset: ";
      r += std::to_string(offset);
      r += "\nnumeric: ";
      r += (numeric == true ? "true" : "false");
      r += "\nparameters: ";
      r += std::to_string(params);
      r += "\nttype: ";
      r += std::to_string(static_cast<int>(ttype));

      r += "\n" + m_pair.toString() + "\n";
      if (nullptr != funcent)
      {
        r += static_pointer_cast<S_TableEntryX>(funcent)->toString() + "\n";
      }
      return r;
   };


   Constant::Constant() : ReturnPacket{} {}
   Constant::Constant(bool lval, njnr::type ttype, bool ifnum, int offset) :
                      ReturnPacket{lval, ttype, ifnum, offset} {}
   Constant::Constant(std::string val, njnr::type t): val{val}, typ{t} {}

   std::string Constant::getValue() const
   {
      return val;
   }

   void Constant::setValue(const std::string in)
   {
      val = in;
   }

   njnr::type Constant::getType() const
   {
      return typ;
   }

   void Constant::setType(const njnr::type t)
   {
      typ = t;
   }


   const std::string Identifier::toString() const
   {
      std::string ret = ReturnPacket::toString();
      return "\nvalue: " + value + "\n" + ret;
   }
   Identifier::Identifier() : Constant{false, njnr::type::IDENT, false, 0} {}

   Identifier::Identifier(const std::string invalue) :
                          Constant{false, njnr::type::IDENT, false, 0},
                          value{invalue}
                          {}

   Identifier::Identifier(const Constant& in) :
                          Constant{in.getlval(),
                          njnr::type::IDENT, false, in.getoffset()},
                          value{in.getValue()}
                          {}

   Identifier& Identifier::operator=(const Identifier& in)
   {
       if (&in != this)
       {
           value = in.value;
           lval = in.lval;
           numeric = false;
           ttype = njnr::type::IDENT;
           offset = in.offset;
       }
       return *this;
   }
   std::string Identifier::getvalue() const
   {
       return value;
   }

   void Identifier::setvalue(const std::string in)
   {
       value = in;
   }

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
      if (funcbody_list) funcbody_list = nullptr;
      funcbody_list = nullptr;
      funcheader = nullptr;
    }
   std::vector<njnr::type>& Funcb::getparam_type()
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
      r += "Current Set Return Type: ";
      r += Compiler::getStringFromType(returntype);
      r += "bodydef:? " + (true == bodydef) ? "true\n" : "false\n";
//      r += "label: " + label + "\n";
//      r += "localcount: " + localcount + "\n";
//      r += "actual_num" + actual_num + "\n";
//      r += "num_param" + num_param + "\n";
/* TODO : params list vector */
      if (nullptr != funcheader)
      {
//         r += funcheader->toString() + "\n";
      }
      if (nullptr != funcbody_list)
      {
         r += funcbody_list->toString();
      }
      return r;
   }

   Varb::Varb() : Identifier{} {}
   Varb::~Varb() { report(njnr::logType::debug, "running Varb() Destructor"); }

   const std::string Varb::toString() const
   {
      return ReturnPacket::toString();
   }

   const std::string Paramb::toString() const
   {
      return ReturnPacket::toString();
   }
   Paramb::Paramb() : ReturnPacket{} {}
   Paramb::~Paramb()
   {
      report(njnr::logType::debug,
             "running Paramb() Destructor");
   }

   const std::string Translation_Unit::toString() const
   {
      std::string ret{ReturnPacket::toString()};
//         std::shared_ptr<ReturnPacket> translation{nullptr};
//         trans_unit_type trans_type;

      return "translation unit: " + this->toString() + "\n" + ret;
   }
   Translation_Unit::Translation_Unit() : translation{nullptr},
                                          trans_type{trans_unit_type::INVALID}
                                          {}

   Translation_Unit::~Translation_Unit()
   {
      report(njnr::logType::debug,
             "running Translation_Unit() Destructor");
   }

   std::shared_ptr<ReturnPacket> Translation_Unit::get_translation()
   {
      return translation;
   }
   void Translation_Unit::set_translation(std::shared_ptr<ReturnPacket> translation)
   {
      this->translation = translation;
   }
   void Translation_Unit::set_trans_unit_type(trans_unit_type intype)
   {
      trans_type = intype;
   }
   trans_unit_type Translation_Unit::get_trans_unit_type()
   {
      return trans_type;
   }
   funcheadertype::~funcheadertype()
   {
      report(njnr::logType::debug,
             "running funcheadertype() Destructor");
      if (paramlist){
         paramlist = nullptr;
      }
   }
}  // namespace njnr
