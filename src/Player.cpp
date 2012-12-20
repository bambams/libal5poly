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

#include "al5poly/Player.hpp"

namespace al5poly
{
    Player::Player(const IAnimation::StringMap & animations):
        x_(0),
        y_(0),
        animations_(animations),
        facing_(AL5POLY_DIRECTION_NONE),
        jumpLastUpdate_(0),
        jumpTimeRemaining_(0)
    {
    }

    void Player::beginAnimation(
            const int ticksPerFrame,
            const IGameTime & gameTime)
    {
        if(!this->currentAnimation_)
            PlayerException("Player is not animated.").raise();

        this->currentAnimation_->begin(ticksPerFrame, gameTime);
    }

    void Player::setCurrentAnimation(const std::string & name)
    {
        IAnimation::StringMap::iterator match =
                this->animations_.find(name);

        if(match == this->animations_.end())
        {
            PlayerException(
                    "The specified animation name is invalid.").raise();
        }

        this->currentAnimation_ = (*match).second;
    }

    IFrame::Ptr Player::getCurrentFrame(const IGameTime & gameTime) const
    {
        if(!this->currentAnimation_)
            PlayerException("Player is not animated.").raise();

        return this->currentAnimation_->getCurrentFrame(gameTime);
    }

    int Player::getX(void) const
    {
        return this->x_;
    }

    int Player::getY(void) const
    {
        return this->y_;
    }

    int Player::setX(const int x)
    {
        return this->x_ = x;
    }

    int Player::setY(const int y)
    {
        return this->y_ = y;
    }

    // h4x.
    void Player::face(const Direction direction)
    {
        this->facing_ = direction;
    }

    //h4x.
    bool Player::isJumping(void) const
    {
        return this->jumpTimeRemaining_ != 0;
    }

    void Player::jump(const IGameTime & time)
    {
        this->jumpLastUpdate_ = time.getTicks();
        this->jumpTimeRemaining_ = 4;
    }

    void Player::land(void)
    {
        this->jumpLastUpdate_ = 0;
    }

    void Player::updateJump(const IGameTime & time, int * const delta)
    {
        if(!this->isJumping())
        {
            PlayerException("Player is not jumping.").raise();
        }

        int ticks = time.getTicks();

        *delta = ticks - this->jumpLastUpdate_;

        this->jumpLastUpdate_ = ticks;
        this->jumpTimeRemaining_ -= *delta;

        if(this->jumpTimeRemaining_ < 0)
        {
            this->jumpTimeRemaining_ = 0;
        }
    }
}

