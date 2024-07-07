#ifndef _CPPSTYPES_HPP
#define _CPPSTYPES_HPP

#include <string>

#include "type.hpp"

namespace njnr
{
//   class S_TableEntry;

   class BaseData
   {
      public:
         virtual ~BaseData() {};
         virtual const std::string toString() const = 0;
         virtual const bool getlval() const = 0;
         virtual void setlval(const bool in) = 0;
         virtual const njnr::type gettype() const = 0;
         virtual void settype(const njnr::type in) = 0;
         virtual const bool getnumeric() const = 0;
         virtual void setnumeric(const bool in) = 0;
   };

   class ReturnPacket : public BaseData
   {
      public:
         ReturnPacket();
         ReturnPacket(bool lval, njnr::type ttype, bool ifnum, int offset);
         const bool getlval() const;
         void setlval(const bool in);
         const njnr::type gettype() const;
         void settype(const njnr::type in);
         const bool getnumeric() const;
         void setnumeric(const bool in);
         virtual ~ReturnPacket();
         int getoffset() const;
         void setoffset(const int in);
         const std::string toString() const;

         struct Pair m_pair;
         void* funcent;
         int params;
      protected:
         int offset;
         bool lval;
         bool numeric;
         njnr::type ttype;
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
         Identifier(const std::string invalue);
         Identifier(const Constant&);
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
         Funcb(njnr::type returntype);
         Funcb(njnr::type returntype, bool bodydef, int num_param, std::vector<njnr::type> param_type,
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
         void setreturntype( njnr::type returntype );
         void setbodydef(bool bodydef);
         void setnum_param(int num_param);
         void setlabel(int label);
         void setlocalcount(int localcount);
         void setactual_num(int actual_num);
         void setfuncbody_list(List* funcbody);
         List* getfuncbody_list(void);
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
         List* funcbody_list;
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

   class Statement : public ReturnPacket
   {
      public:
         Statement();
         statement_type getstype();
         ReturnPacket* getexpr();
         void setexpr(ReturnPacket* expr);
         void setstype(statement_type t);
         virtual ~Statement();
         type getrettype();
         void setrettype(njnr::type t);
         const std::string toString() const;
         std::string printCheckReturn(void) const;
      private:
         statement_type stype;
         ReturnPacket*  expr;
         njnr::type     rettype;
   };

   class Translation_Unit : public ReturnPacket
   {
      public:
         Translation_Unit();
//         Translation_Unit(Funcb* func);
//         Translation_Unit(Varb* varb); // placeholder type -- needs to change
         virtual ~Translation_Unit();
         ReturnPacket* get_translation();
         void set_translation(ReturnPacket* translation);
         void set_trans_unit_type(trans_unit_type intype);
         trans_unit_type get_trans_unit_type();
         const std::string toString() const;
      private:
         ReturnPacket* translation;
         trans_unit_type trans_type;
   };

}
#endif
