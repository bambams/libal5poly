#ifndef INPUT_MANAGER_HPP
    #define INPUT_MANAGER_HPP

    #include <allegro5/allegro5.h>
    #include <map>
    #include <stdexcept>
    #include <string>

namespace al5poly
{
    class InputManager;
}

    #include <al5poly/IGameTime.hpp>
    #include <al5poly/IInputHandler.hpp>

namespace al5poly
{
    class InputManager
    {
        typedef std::map<std::string,
                IInputHandler::List> ActionHandlerMap;
        typedef std::map<int, std::string> KeyActionMap;

        ActionHandlerMap handlers_;
        KeyActionMap keys_;
    public:
        void addActionHandler(
                const std::string &,
                const IInputHandler::Ptr);

        IInputHandler::List & getActionHandlers(const std::string &);

        void keyPress(const IGameTime &, ALLEGRO_EVENT * const);

        void setKeyAction(const int, const std::string &);
    };
}

#endif
