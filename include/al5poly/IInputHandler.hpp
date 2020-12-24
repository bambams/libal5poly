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

#ifndef IINPUT_HANDLER_HPP
    #define IINPUT_HANDLER_HPP

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
