#ifndef SRC_INCLUDE_CONSTANT_HPP_
#define SRC_INCLUDE_CONSTANT_HPP_

#include <config.h>
#include <vector>
#include <string>
#include "cpptypes.hpp"

namespace njnr
{
class TSConstantType: public TSType
{
   virtual ~TSConstantType();
   TSConstantType();
   explicit TSConstantType(std::string s);
   explicit TSConstantType(njnr::type t);
};

class Constant : public ReturnPacket
{
   public:
      Constant();
      Constant(bool lval, njnr::type ttype, bool ifnum, int offset);
      Constant(std::string val, njnr::type t);
      virtual ~Constant();
      std::string getValue() const;
      void setValue(const std::string in);
      njnr::type getType() const;
      void setType(const njnr::type t);
      //  ReturnPacket
   private:
      std::string val;
      njnr::type typ;
};


class Identifier : public Constant
{
   public:
      Identifier();
      explicit Identifier(const std::string invalue);
      explicit Identifier(const Constant&);
      virtual ~Identifier();
      Identifier& operator=(const Identifier& in);
      std::string getvalue() const;
      void setvalue(const std::string in);
      const std::string toString() const;
   private:
      std::string value;
};

class Funcb : public Identifier
{
   public:
      Funcb();
      explicit Funcb(njnr::type returntype);
      Funcb(njnr::type returntype, bool bodydef, int num_param,
            std::vector<njnr::type> param_type,
            int label, int localcount, int actual_num);
      Funcb(const Funcb& in);
      Funcb& operator=(const Funcb& in);
      virtual ~Funcb();
      std::vector<njnr::type>& getparam_type();
      njnr::type getreturntype();
      bool getbodydef();
      int getnum_param();
      int getlabel();
      int getlocalcount();
      int getactual_num();
      void setparam_type(std::vector<njnr::type> param_type);
      void setreturntype(njnr::type returntype);
      void setbodydef(bool bodydef);
      void setnum_param(int num_param);
      void setlabel(int label);
      void setlocalcount(int localcount);
      void setactual_num(int actual_num);
      void setfuncbody_list(std::shared_ptr<List> funcbody);
      std::shared_ptr<List> getfuncbody_list(void);
      void setfuncheader(funcheadertype* funcheader);
      funcheadertype* getfuncheader(void);
      const std::string toString() const;
   private:
      std::vector<njnr::type> param_type;
      njnr::type  returntype;
      bool  bodydef;
      int   num_param;
      int   label;
      int   localcount;
      int   actual_num;
      funcheadertype* funcheader;
      std::shared_ptr<List> funcbody_list;
};

class Varb : public Identifier
{
   public:
      Varb();
      virtual ~Varb();
      const std::string toString() const;
   private:
};

class Paramb : public ReturnPacket
{
   public:
      Paramb();
      virtual ~Paramb();
      const std::string toString() const;
   private:
};

}  // namespace njnr
#endif  // SRC_INCLUDE_CONSTANT_HPP_
