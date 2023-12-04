#ifndef S_TABLE_ENTRY_H
#define S_TABLE_ENTRY_H

#include <string>

#include "type.hpp"
#include "cpptypes.hpp"
namespace njnr
{
   /* A Generic Symbol Table Entry */
   class S_TableEntry
   {
      public:
         /* Default Constructor */
         S_TableEntry();

         /* Constructor with arguments */
         S_TableEntry(std::string& key, void* value,
                      type entry_type) noexcept;

         /* Copy Constructor */
         S_TableEntry(const S_TableEntry& in) noexcept;

         /* Equivalence operator overload */
         S_TableEntry& operator=(const S_TableEntry& in);

         /* Return a stringized version of the object */
         std::string toString() const  noexcept;

         /* return the key for the table entry */
         std::string getKey(void) const noexcept;

         /* return the value for the table entry */
         void* getValue(void) const noexcept;

         /* return the type for the table entry */
         njnr::type getType(void) const noexcept;

         /* return the type for the table entry */
         njnr::btype getGroup(void) const noexcept;

         void* getBinding();
         std::string getName() const;
         void setName(std::string name);

      private:
         std::string  key;
         void*      value;
         /* element type */
         njnr::type entry_type;
         /* group type */
         njnr::btype group_type;
         ReturnPacket* binding;
         std::string name;

   };
}
#endif // S_TABLE_ENTRY_H
