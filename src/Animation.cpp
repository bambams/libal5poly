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

#include <sstream>

#include "al5poly/Animation.hpp"
#include "al5poly/string.hpp"

namespace al5poly
{
    Animation::Animation(const ALLEGRO_BITMAP_Ptr_Vector & sprites):
        sprites_(sprites),
        startTime_(0)
    {
        if(sprites.size() == 0)
        {
            AnimationException(
                    "Cannot make animation from empty sprite vector.").raise();
        }
    }

    void Animation::begin(const int ticksPerFrame, const IGameTime & gameTime)
    {
        this->startTime_ = gameTime.getTicks();
        this->ticksPerFrame_ = ticksPerFrame;
    }

    IFrame::Ptr Animation::getCurrentFrame(const IGameTime & gameTime) const
    {
        int ticks = gameTime.getTicks();
        int startTicks = this->startTime_.getTicks();
        int past = (ticks - startTicks) / this->ticksPerFrame_;
        int i = past % (this->sprites_.size());
        ALLEGRO_BITMAP_Ptr currentSprite = this->sprites_[i];

        IFrame::Ptr currentFrame(new Frame(currentSprite));

        return currentFrame;
    }

    std::string Animation::to_string(void) const
    {
        std::stringstream ss;

        ss << "'#<al5poly::Animation>("
           << " :start_time "
           << this->startTime_.getTicks()
           << " :ticks_per_frame "
           << this->ticksPerFrame_
           << " :sprites '#<al5poly::ALLEGRO_BITMAP_Ptr_Vector>("
           << " :count "
           << this->sprites_.size()
           << " :raw (";

        bool cont = false;

        for (auto const & sprite_ptr : this->sprites_)
        {
            if (cont)
            {
                ss << ", ";
            }

            ss << "'#<BITMAP_Ptr>("
               << "0x" << std::hex << sprite_ptr.get() << std::dec
               << ")";

            cont = true;
        }

        ss << ")"
           << ")"
           << ")";

        return ss.str();
    }
}

