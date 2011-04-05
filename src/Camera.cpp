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

#include "Camera.hpp"

Camera::Camera(void):
    x_(0),
    y_(0)
{
}

int Camera::getX(void) const
{
    return this->x_;
}

int Camera::getY(void) const
{
    return this->y_;
}

int Camera::setX(const int x)
{
    return this->x_ = x;
}

int Camera::setY(const int y)
{
    return this->y_ = y;
}

