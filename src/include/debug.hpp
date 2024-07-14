#ifndef SRC_INCLUDE_DEBUG_HPP_
#define SRC_INCLUDE_DEBUG_HPP_

#ifdef DEBUGON
#ifndef DEBUG
#define DEBUG
#define YYDEBUG 1
#endif
#endif

#ifndef DEBUG
#define debugprint(x, y)

#endif

#include <config.h>
#include <string>

namespace njnr
{
class Debug
{
public:
    Debug();
    ~Debug();
    static int get_yydebug();
    static void set_yydebug(const int value);
private:
    static int yydebug;
};

#ifdef DEBUG
void debugprint(std::string, std::string);
void debugprint(std::string, int);
#endif

}  // namespace njnr
#endif  // SRC_INCLUDE_DEBUG_HPP_
