/*
 * libal5poly is a game library abstraction library. xD
 * Copyright (C) 2011 Brandon McCaig
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

#ifndef IANIMATION_HPP
    #define IANIMATION_HPP

    #include <boost/shared_ptr.hpp>
    #include <map>
    #include <string>

class IAnimation;

    #include "IFrame.hpp"
    #include "IGameTime.hpp"

class IAnimation
{
public:
    typedef boost::shared_ptr<IAnimation> Ptr;
    typedef std::map<std::string, Ptr> StringMap;

    virtual ~IAnimation(void) = 0;

    virtual void begin(const int, const IGameTime &) = 0;
    virtual IFrame::Ptr getCurrentFrame(const IGameTime &) const = 0;
};

#endif

