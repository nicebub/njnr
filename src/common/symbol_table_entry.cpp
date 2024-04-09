#include <string>

#include "type.hpp"
#include "symbol_table_entry.hpp"
using namespace njnr;

S_TableEntry::S_TableEntry() : key{""},
                               value{NULL},
                               entry_type{njnr::type::VOID}
{
}

S_TableEntry::S_TableEntry(std::string& key,
                           void* value = nullptr,
                           type entry_type = njnr::type::VOID) noexcept : key{key},
                                                                          value{value},
                                                                          entry_type{entry_type}
{
}
S_TableEntry::S_TableEntry(const S_TableEntry& in) noexcept : key{in.key},
                                                              value{in.value},
                                                              entry_type{in.entry_type}
{
  // TODO: need to make deep copy - 'value' needs to be casted then copied
}  // copy constructor

S_TableEntry& S_TableEntry::operator=(const S_TableEntry& in)
{
   if(this != &in)
   {
      this->key        = in.getKey();
      this->entry_type = in.getType();
      // TODO: need to do this as a deep copy of value instead; cast then copy
      this->value      = in.getValue();
   }
   return *this;
}

std::string S_TableEntry::toString() const  noexcept
{
   return "key: " + key + " type: " + std::to_string((int)entry_type);
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
   return entry_type;
}
njnr::btype S_TableEntry::getGroup() const noexcept
{
    return group_type;
}

void* S_TableEntry::getBinding()
{
    return binding;
}

   std::string S_TableEntry::getName() const
   {
       return name;
   }

   void S_TableEntry::setName(std::string inName)
   {
       name = inName;
   }
