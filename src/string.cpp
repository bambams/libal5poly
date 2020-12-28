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

    std::pair<std::function<void (void)>, std::function<void (void)>>
    create_maybe_comma(std::stringstream & ss)
    {
        std::function<void (void)> append_comma = [&ss](){ ss << ", "; };
        std::function<void (void)> maybe_comma = nullptr;
        std::function<void (void)> ready([&maybe_comma, append_comma]() { maybe_comma = append_comma; });
        std::function<void (void)> reset_comma([&maybe_comma, ready]() { maybe_comma = ready; });

        reset_comma();

        return std::pair(maybe_comma, reset_comma);
    }
}
