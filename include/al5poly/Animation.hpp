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

#ifndef ANIMATION_HPP
    #define ANIMATION_HPP

namespace al5poly
{
    class Animation;
}

    #include "al5poly/altypedef.hpp"
    #include "al5poly/AnimationException.hpp"
    #include "al5poly/Frame.hpp"
    #include "al5poly/GameTime.hpp"
    #include "al5poly/IAnimation.hpp"
    #include "al5poly/IFrame.hpp"

namespace al5poly
{
    class Animation:
        public IAnimation
    {
    private:
        ALLEGRO_BITMAP_Ptr_Vector sprites_;
        GameTime startTime_;
        int ticksPerFrame_;
    public:
        Animation(const ALLEGRO_BITMAP_Ptr_Vector &);

        void begin(const int, const IGameTime &);
        IFrame::Ptr getCurrentFrame(const IGameTime &) const;

        virtual std::string to_string(void) const;
    };
}

#endif

