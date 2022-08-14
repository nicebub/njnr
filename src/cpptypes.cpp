#include "cpptypes.hpp"
#include "type.hpp"

namespace njnr {
ReturnPacket::ReturnPacket() :
    params{0},
    offset{0},
    lval{false},
    numeric{false},
    ttype{njnr::type::INT}
{}

ReturnPacket::ReturnPacket(bool lval,
                           njnr::type ttype=njnr::type::INT,
                           bool ifnum=false,
                           int inoffset=0) :
    params{0},
    offset{inoffset},
    lval{lval},
    numeric{ifnum},
    ttype{ttype}
{}

ReturnPacket::~ReturnPacket() {}

bool ReturnPacket::getlval() const {
    return lval;
}
void ReturnPacket::setlval(const bool in) {
    lval = in;
}
njnr::type  ReturnPacket::gettype() const {
    return ttype;
}
void ReturnPacket::settype(const njnr::type in) {
    ttype = in;
}
bool ReturnPacket::getnumeric() const {
    return numeric;
}
void ReturnPacket::setnumeric(const bool in) {
    numeric = in;
}
int ReturnPacket::getoffset() const {
    return offset;
}
void ReturnPacket::setoffset(const int in) {
    offset = in;
}


Constant::~Constant() {}

Constant::Constant() : ReturnPacket{} {}
Constant::Constant(bool lval, njnr::type ttype, bool ifnum, int offset) : ReturnPacket{lval,ttype,ifnum,offset} {}

IntConstant::IntConstant() : Constant{false,njnr::type::INT, true, 0}, value{0} {}

IntConstant::IntConstant(const int invalue) : Constant{false,njnr::type::INT, true, 0}, value{invalue} {}

IntConstant::IntConstant(const IntConstant& in) : Constant{false,njnr::type::INT, true, 0}, value{in.value} {}

IntConstant::~IntConstant() {}

IntConstant& IntConstant::operator=(const IntConstant& in) {
    if(&in != this) {
        value = in.value;
        lval = false;
        numeric = true;
        ttype = njnr::type::INT;
    }
    return *this;
}
int IntConstant::getvalue() const {
    return value;
}

void IntConstant::setvalue(const int in) {
    value = in;
}

StrConstant::StrConstant() : Constant{false,njnr::type::STR, false, 0} {}

StrConstant::StrConstant(const std::string invalue) : Constant{false,njnr::type::STR, false, 0}, value{invalue} {}

StrConstant::StrConstant(const StrConstant& in) : Constant{false,njnr::type::STR, false, in.offset}, value{in.value} {}

StrConstant::~StrConstant() {}

StrConstant& StrConstant::operator=(const StrConstant& in) {
    if(&in != this) {
        value = in.value;
        lval = false;
        numeric = false;
        ttype = njnr::type::STR;
        offset = in.offset;
    }
    return *this;
}
std::string StrConstant::getvalue() const {
    return value;
}

void StrConstant::setvalue(const std::string in) {
    value = in;
}

FloatConstant::FloatConstant() : Constant{false,njnr::type::FLOAT, true, 0}, value{0.0f} {}

FloatConstant::FloatConstant(const float invalue ) : Constant{false,njnr::type::FLOAT, true, 0}, value{invalue } {}


FloatConstant::FloatConstant(const FloatConstant& in ) : Constant{false,njnr::type::FLOAT, true, in.offset}, value{in.value } {}

FloatConstant::~FloatConstant() {}

FloatConstant& FloatConstant::operator=(const FloatConstant& in) {
    if(&in != this) {
        value = in.value;
        lval = false;
        numeric = true;
        ttype = njnr::type::FLOAT;
        offset = in.offset;
    }
    return *this;
}
float FloatConstant::getvalue() const {
    return value;
}
void FloatConstant::setvalue(const float in) {
    value = in;
}

Identifier::Identifier() : Constant{false,njnr::type::IDENT, false, 0} {}

Identifier::Identifier(const std::string invalue) : Constant{false,njnr::type::IDENT, false, 0}, value{invalue} {}

Identifier::Identifier(const StrConstant& in) : Constant{in.getlval(),njnr::type::IDENT, false, in.getoffset()}, value{in.getvalue()} {}

Identifier::~Identifier() {}

Identifier& Identifier::operator=(const Identifier& in) {
    if(&in != this) {
        value = in.value;
        lval = in.lval;
        numeric = false;
        ttype = njnr::type::IDENT;
        offset = in.offset;
    }
    return *this;
}
std::string Identifier::getvalue() const {
    return value;
}

void Identifier::setvalue(const std::string in) {
    value = in;
}

Funcb::Funcb() :	param_type{},
    returntype{njnr::type::VOID},
    bodydef{false},
    num_param{0},
    label{0},
    localcount{0},
    actual_num{0}
{}
Funcb::Funcb(njnr::type returntype, bool bodydef, int num_param, std::vector<njnr::type> param_type, int label, int localcount, int actual_num) :
    param_type{param_type},
    returntype{returntype},
    bodydef{bodydef},
    num_param{num_param},
    label{label},
    localcount{localcount},
    actual_num{actual_num}
{}
Funcb::Funcb(njnr::type returntype) : Funcb{} {
    this->returntype = returntype;
}
Funcb::Funcb(const Funcb& in) :
    param_type{in.param_type},
    returntype{in.returntype},
    bodydef{in.bodydef},
    num_param{in.num_param},
    label{in.label},
    localcount{in.localcount},
    actual_num{in.actual_num}
{
    setvalue(in.getvalue());
}

Funcb& Funcb::operator=(const Funcb& in) {
    if(&in != this) {
        returntype = in.returntype;
        bodydef = in.bodydef;
        num_param = in.num_param;
        label = in.label;
        localcount = in.localcount;
        actual_num = in.actual_num;
        param_type = in.param_type;
        setvalue(in.getvalue());
    }
    return *this;
}
Funcb::~Funcb() {}
std::vector<njnr::type>& Funcb::getparam_type() {
    return param_type;
}
njnr::type Funcb::getreturntype() {
    return returntype;
}
bool Funcb::getbodydef() {
    return bodydef;
}
int Funcb::getnum_param() {
    return num_param;
}
int Funcb::getlabel() {
    return label;
}
int Funcb::getlocalcount() {
    return localcount;
}
int Funcb::getactual_num() {
    return actual_num;
}
void Funcb::Funcb::setparam_type(std::vector<njnr::type> param_type) {
    this->param_type = param_type;
}
void Funcb::setreturntype( njnr::type returntype ) {
    this->returntype = returntype;
}
void Funcb::setbodydef(bool bodydef) {
    this->bodydef = bodydef;
}
void Funcb::setnum_param(int num_param) {
    this->num_param = num_param;
}
void Funcb::setlabel(int label) {
    this->label = label;
}
void Funcb::setlocalcount(int localcount) {
    this->localcount = localcount;
}
void Funcb::setactual_num(int actual_num ) {
    this->actual_num = actual_num;
}

Varb::Varb() : Identifier{} {}
Varb::~Varb() {}

Paramb::Paramb() : ReturnPacket{} {}
Paramb::~Paramb() {}
}

