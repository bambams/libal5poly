/*
 * libal5poly is a game library abstraction library. xD
 * Copyright (C) 2011, 2012, 2015, 2016, 2020 Brandon McCaig
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

#ifndef PLAYEREXCEPTION_HPP
    #define PLAYEREXCEPTION_HPP

    #include <string>

namespace al5poly
{
    class PlayerException;
}

    #include "al5poly/Exception.hpp"
    #include "al5poly/IAnimation.hpp"
    #include "al5poly/IFrame.hpp"
    #include "al5poly/IGameTime.hpp"
    #include "al5poly/IRenderable.hpp"

namespace al5poly
{
    class PlayerException:
        public Exception
    {
    public:
        PlayerException(const std::string &);
    };
}

#endif

