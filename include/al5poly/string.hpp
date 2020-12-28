#include <functional>
#include <string>
#include <sstream>
#include <string>

namespace al5poly::string
{
    std::string replace(std::string, const std::string &, const std::string &);

    std::pair<std::function<void (void)>,std::function<void (void)>>
    create_maybe_comma(std::stringstream &);
}
