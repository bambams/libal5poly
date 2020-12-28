#include <algorithm>

#include "al5poly/string.hpp"

namespace al5poly::string
{
    std::string replace(std::string s, const std::string & substring, const std::string & replacement)
    {
        while (true)
        {
            size_t index = s.find(substring);

            if (index == std::string::npos)
            {
                return s;
            }

            s.replace(
                    index,
                    substring.length(),
                    replacement);
        }

        return s;
    }
}
