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

#ifndef IRENDERABLE_HPP
    #define IRENDERABLE_HPP

    #include <boost/shared_ptr.hpp>

namespace al5poly
{
    class IRenderable;
}

    #include "al5poly/Orientation.hpp"
    #include "al5poly/IFrame.hpp"
    #include "al5poly/IGameTime.hpp"

namespace al5poly
{
    class IRenderable
    {
    public:
        typedef boost::shared_ptr<IRenderable> Ptr;

        virtual ~IRenderable(void) = 0;

        virtual IFrame::Ptr getCurrentFrame(const IGameTime &) const = 0;
        virtual Orientation getOrientation(void) const = 0;
        virtual int getX(void) const = 0;
        virtual int getY(void) const = 0;
    };
}

#endif

