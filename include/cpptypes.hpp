#ifndef _CPPSTYPES_HPP
#define _CPPSTYPES_HPP

#include <string>

#include "type.hpp"
namespace njnr
{
   class TableEntry;

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
         TableEntry* funcent;
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
         virtual ~Constant();
         //		ReturnPacket
      private:
   };

   class CharConstant : public Constant
   {
      public:
         CharConstant();
         CharConstant(const char invalue);
         CharConstant(const CharConstant&);
         virtual ~CharConstant();
         CharConstant& operator=(const CharConstant& in);
         char getvalue() const;
         void setvalue(const char in);
         const std::string toString() const;
      private:
         char value;
   };

   class IntConstant : public Constant
   {
      public:
         IntConstant();
         IntConstant(const int invalue);
         IntConstant(const IntConstant&);
         virtual ~IntConstant();
         IntConstant& operator=(const IntConstant& in);
         int getvalue() const;
         void setvalue(const int in);
         const std::string toString() const;
      private:
         int value;
   };

   class StrConstant : public Constant
   {
      public:
         StrConstant();
         StrConstant(const std::string invalue);
         StrConstant(const StrConstant&);
         virtual ~StrConstant();
         StrConstant& operator=(const StrConstant& in);
         std::string getvalue() const;
         void setvalue(const std::string in);
         const std::string toString() const;
      private:
         std::string value;
   };

   class FloatConstant : public Constant
   {
      public:
         FloatConstant();
         FloatConstant(const float invalue);
         FloatConstant(const FloatConstant&);
         virtual ~FloatConstant();
         FloatConstant& operator=(const FloatConstant& in);
         float getvalue() const;
         void setvalue(const float in);
         const std::string toString() const;
      private:
         float value;
   };

   class Identifier : public Constant
   {
      public:
         Identifier();
         Identifier(const std::string invalue);
         Identifier(const StrConstant&);
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
         std::vector<type>& getparam_type();
         type getreturntype();
         bool getbodydef();
         int getnum_param();
         int getlabel();
         int getlocalcount();
         int getactual_num();
         void setparam_type(std::vector<type> param_type);
         void setreturntype( njnr::type returntype );
         void setbodydef(bool bodydef);
         void setnum_param(int num_param);
         void setlabel(int label);
         void setlocalcount(int localcount);
         void setactual_num(int actual_num);
      private:
         std::vector<njnr::type> param_type;
         type 	returntype;
         bool 	bodydef;
         int 	num_param;
         int 	label;
         int 	localcount;
         int 	actual_num;
   };

   class Varb : public Identifier
   {
      public:
         Varb();
         virtual ~Varb();
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
         ReturnPacket* getstmt();
         void setstmt(ReturnPacket* stmt);
         void setstype(statement_type t);
         virtual ~Statement();
         type getrettype();
         void setrettype(njnr::type t);
         const std::string toString() const;
      private:
         statement_type stype;
         ReturnPacket* stmt;
         type         rettype;
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
