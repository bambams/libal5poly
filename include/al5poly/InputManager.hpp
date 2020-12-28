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

#ifndef INPUT_MANAGER_HPP
    #define INPUT_MANAGER_HPP

    #include <allegro5/allegro5.h>
    #include <cstring>
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

        // h4x.
        int keysDown_;
        bool keyStates_[ALLEGRO_KEY_MAX];

        IInputHandler::List & getActionHandlers(const std::string &);
    public:
        InputManager(void);

        void addActionHandler(
                const std::string &,
                const IInputHandler::Ptr);

        void keyPress(const int);
        void keyRelease(const int);

        void mapKeyAction(const int, const std::string &, const IInputHandler::Ptr);

        void sendEvents(const IGameTime &) const;
        void sendKeyDown(const IGameTime &, const int) const;

        void setKeyAction(const int, const std::string &);
    };
}

#endif
