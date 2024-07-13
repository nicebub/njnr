#ifndef S_TABLE_ENTRY_H
#define S_TABLE_ENTRY_H

#include <config.h>
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

         virtual ~S_TableEntry(){};

         /* Constructor with arguments */
         S_TableEntry(std::string& key, void* value,
                      njnr::type eType) noexcept;

         /* Copy Constructor */
         S_TableEntry(const S_TableEntry& in) noexcept;

         /* Equivalence operator overload */
         virtual S_TableEntry& operator=(const S_TableEntry& in);

         /* Return a stringized version of the object */
         virtual std::string toString() const  noexcept;

         /* return the key for the table entry */
         std::string getKey(void) const noexcept;

         /* return the value for the table entry */
         void* getValue(void) const noexcept;

         /* return the type for the table entry */
         njnr::type getType(void) const noexcept;

         void setType(njnr::type type);
      private:
         std::string  key;
         void*      value;
         njnr::type eType;
   };

   class S_TableEntryX : public S_TableEntry
   {
      public:
         /* Default Constructor */
         S_TableEntryX() = default;

         virtual ~S_TableEntryX(){};

         /* Constructor with arguments */
         S_TableEntryX(std::string& key, void* value,
                      njnr::type eType) noexcept;

         /* Copy Constructor */
//         S_TableEntryX(const S_TableEntryX& in) noexcept;

         /* Equivalence operator overload */
  //       virtual S_TableEntryX& operator=(const S_TableEntryX& in);

         /* Return a stringized version of the object */
         virtual std::string toString() const  noexcept;

         /* return the type for the table entry */
         njnr::btype getGroup(void) const noexcept;

         void* getBinding();

         std::string getName() const;
         void setName(std::string name);

      private:
         /* group type */
         njnr::btype group_type;

         ReturnPacket* binding;

         std::string name;
   };
}
#endif // S_TABLE_ENTRY_H
