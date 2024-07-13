#include <config.h>
#include <string>

#include "type.hpp"
#include "symbol_table_entry.hpp"
using namespace njnr;

S_TableEntry::S_TableEntry() : key{""},
                               value{NULL},
                               eType{njnr::type::VOID} {}


S_TableEntry::S_TableEntry(std::string& key,
                           void* value = nullptr,
                           njnr::type eType = njnr::type::VOID) noexcept : key{key},
                                                                          value{value},
                                                                          eType{eType} {}

S_TableEntryX::S_TableEntryX(std::string& key,
                           void* value = nullptr,
                           njnr::type eType = njnr::type::VOID) noexcept : S_TableEntry(key,
                                                                          value,
                                                                          eType) {}
S_TableEntry::S_TableEntry(const S_TableEntry& in) noexcept : key{in.key},
                                                              value{in.value},
                                                              eType{in.eType}
{
  // TODO: need to make deep copy - 'value' needs to be casted then copied
}  // copy constructor

S_TableEntry& S_TableEntry::operator=(const S_TableEntry& in)
{
   if(this != &in)
   {
      this->key        = in.getKey();
      this->eType = in.getType();
      // TODO: need to do this as a deep copy of value instead; cast then copy
      this->value      = in.getValue();
   }
   return *this;
}

std::string S_TableEntry::toString() const  noexcept
{
   return "key: " + key + " type: " + std::to_string((int)eType);
}

std::string S_TableEntryX::toString() const  noexcept
{
   return S_TableEntry{*this}.toString() + "other";
}

std::string S_TableEntry::getKey(void) const noexcept
{
   return key;
}

void* S_TableEntry::getValue(void) const noexcept
{
   return value;
}

njnr::type S_TableEntry::getType(void) const noexcept
{
   return eType;
}
njnr::btype S_TableEntryX::getGroup() const noexcept
{
    return group_type;
}

void* S_TableEntryX::getBinding()
{
    return binding;
}

std::string S_TableEntryX::getName() const
{
    return name;
}

void S_TableEntryX::setName(std::string inName)
{
    name = inName;
}

void S_TableEntry::setType(njnr::type inType)
{
    eType = inType;
}
