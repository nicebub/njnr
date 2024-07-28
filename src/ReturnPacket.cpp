#include <config.h>
#include <string>

#include "ReturnPacket.hpp"
#include "type.hpp"
#include "symbol_table_entry.hpp"
using namespace njnr;

   ReturnPacket::ReturnPacket() : m_pair{},
                                  funcent{nullptr},
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
                                                 m_pair{},
                                                 funcent{nullptr},
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
