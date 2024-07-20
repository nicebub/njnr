#ifndef SRC_INCLUDE_CPPTYPES_HPP_
#define SRC_INCLUDE_CPPTYPES_HPP_

#include <config.h>
#include <string>

#include "type.hpp"

namespace njnr
{
//   class S_TableEntry;

class BaseData
{
   public:
      virtual ~BaseData()
      {
         report(njnr::logType::debug,
                "running BaseData() Destructor");
      }
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
      virtual ~ReturnPacket()
      {
         report(njnr::logType::debug,
               "running ReturnPacket() Destructor");
      }
      const bool getlval() const;
      void setlval(const bool in);
      const njnr::type gettype() const;
      void settype(const njnr::type in);
      const bool getnumeric() const;
      void setnumeric(const bool in);
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
//      Translation_Unit(Funcb* func);
//      Translation_Unit(Varb* varb); // placeholder type -- needs to change
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

}  // namespace njnr
#endif  // SRC_INCLUDE_CPPTYPES_HPP_
