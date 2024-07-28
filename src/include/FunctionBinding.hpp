#ifndef SRC_INCLUDE_FUNCTIONBINDING_HPP_
#define SRC_INCLUDE_FUNCTIONBINDING_HPP_

#include <config.h>
#include <vector>
#include <string>
#include <memory>

#include "type.hpp"
//#include "Constant.hpp"
#include "Identifier.hpp"
//#include "List.hpp"
#include "FunctionHeader.hpp"
namespace njnr
{
class FunctionBinding : public Identifier
{
   public:
      FunctionBinding();

      explicit FunctionBinding(njnr::type returntype);

      FunctionBinding(njnr::type returntype, bool bodydef, int num_param,
            std::vector<njnr::type> param_type,
            int label, int localcount, int actual_num);

      FunctionBinding(njnr::type returntype, bool bodydef, int num_param,
            std::vector<njnr::type> param_type, int label,
            int localcount, int actual_num,
            std::shared_ptr<FunctionHeader> funcheader,
            std::shared_ptr<List> funcbody_list);

      FunctionBinding(const FunctionBinding& in);
      FunctionBinding& operator=(const FunctionBinding& in);
      virtual ~FunctionBinding();
      std::vector<njnr::type> getparam_type();
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
      void setfuncheader(std::shared_ptr<FunctionHeader> funcheader);
      std::shared_ptr<FunctionHeader> getfuncheader(void);
      const std::string toString() const;
   private:
      std::vector<njnr::type> param_type;
      njnr::type  returntype;
      bool  bodydef;
      int   num_param;
      int   label;
      int   localcount;
      int   actual_num;
      std::shared_ptr<FunctionHeader> funcheader;
      std::shared_ptr<List> funcbody_list;
};
}  // namespace njnr
#endif  // SRC_INCLUDE_FUNCTIONBINDING_HPP_
