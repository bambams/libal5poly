#include <al5poly/InputManager.hpp>

namespace al5poly
{
    void InputManager::addActionHandler(
            const std::string & action,
            const IInputHandler::Ptr handler)
    {
        IInputHandler::List & handlers = this->getActionHandlers(action);

        handlers.push_back(handler);
    }

    IInputHandler::List & InputManager::getActionHandlers(
            const std::string & action)
    {
        ActionHandlerMap::iterator it = this->handlers_.find(action);

        if(it != this->handlers_.end())
        {
            return (*it).second;
        }

        // This won't work... I'm sure of it. ->
        return this->handlers_[action] = IInputHandler::List();
    }

    void InputManager::keyPress(
            const IGameTime & time,
            ALLEGRO_EVENT * const event)
    {
        KeyActionMap::const_iterator it =
                this->keys_.find(event->keyboard.keycode);

        if(it == this->keys_.end())
        {
            return;
        }

        const std::string & action = (*it).second;

        ActionHandlerMap::const_iterator it2 =
                this->handlers_.find(action);

        if(it2 == this->handlers_.end())
        {
            return;
        }

        const IInputHandler::List & handlers = (*it2).second;

        for(IInputHandler::List::const_iterator it3 = handlers.begin();
                it3 != handlers.end();
                it3++)
        {
            boost::shared_ptr<IInputHandler> handler = (*it3);

            // Too Perl-ish???
            (*handler)(time);
        }
    }

    void InputManager::setKeyAction(const int key, const std::string & action)
    {
        this->keys_[key] = action;
    }
}
