#include "macros.h"

bool startsWith(const std::string& longStr, const std::string& shortStr)
{
    return shortStr.length() <= longStr.length()
        && std::equal(shortStr.begin(), shortStr.end(), longStr.begin());
}
