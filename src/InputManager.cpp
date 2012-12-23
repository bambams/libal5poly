/*
 * libal5poly is a game library abstraction library. xD
 * Copyright (C) 2011, 2012 Brandon McCaig
 *
 * This file is part of libal5poly.
 *
 * libal5poly is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libal5poly is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libal5poly.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <al5poly/InputManager.hpp>

namespace al5poly
{
    InputManager::InputManager(void):
        keysDown_(0)
    {
        memset(this->keyStates_, false, sizeof(bool) * ALLEGRO_KEY_MAX);
    }

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

    void InputManager::keyPress(const int keycode)
    {
        this->keyStates_[keycode] = true;
        this->keysDown_++;
    }

    void InputManager::keyRelease(const int keycode)
    {
        this->keyStates_[keycode] = false;
        this->keysDown_--;
    }

    void InputManager::setKeyAction(const int key, const std::string & action)
    {
        this->keys_[key] = action;
    }

    void InputManager::sendEvents(const IGameTime & time) const
    {
        if(this->keysDown_ == 0)
        {
            return;
        }

        for(int i=0; i<ALLEGRO_KEY_MAX; i++)
        {
            if(this->keyStates_[i])
            {
                this->sendKeyDown(time, i);
            }
        }
    }

    void InputManager::sendKeyDown(
            const IGameTime & time,
            const int keycode) const
    {
        KeyActionMap::const_iterator it = this->keys_.find(keycode);

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
            (*handler)(action, time);
        }
    }
}
