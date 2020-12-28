#ifndef AL5POLY_ISTRINGABLE_HPP
    #define AL5POLY_ISTRINGABLE_HPP

    #include <string>

namespace al5poly
{
    class IStringable;
}

namespace al5poly
{
    class IStringable
    {
    public:
        virtual ~IStringable(void);
        virtual std::string to_string(void) const = 0;
    };
}

#endif
