#include <typeinfo>

#include "al5poly/IStringable.hpp"
#include "al5poly/string.hpp"

namespace al5poly
{
    IStringable::~IStringable(void) {}

    std::string IStringable::to_string(void) const
    {
        return typeid(*this).name();
    }
}
