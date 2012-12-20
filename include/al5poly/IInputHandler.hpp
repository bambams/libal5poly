#ifndef INPUT_HANDLER_HPP
    #define INPUT_HANDLER_HPP

    #include <boost/shared_ptr.hpp>
    #include <boost/weak_ptr.hpp>
    #include <list>

namespace al5poly
{
    class IInputHandler;
}

    #include <al5poly/IGameTime.hpp>

namespace al5poly
{
    class IInputHandler
    {
    public:
        typedef boost::shared_ptr<IInputHandler> Ptr;
        typedef std::list<Ptr> List;

        virtual ~IInputHandler(void) = 0;

        virtual void operator()(
                const std::string &,
                const IGameTime &) const = 0;
    };
}

#endif
