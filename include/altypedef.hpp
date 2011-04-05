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

#ifndef ALTYPEDEF_HPP
    #define ALTYPEDEF_HPP

    #include <allegro5/allegro5.h>
    #include <boost/shared_ptr.hpp>
    #include <vector>

typedef boost::shared_ptr<ALLEGRO_BITMAP> ALLEGRO_BITMAP_Ptr;
typedef std::vector<ALLEGRO_BITMAP_Ptr> ALLEGRO_BITMAP_Ptr_Vector;
typedef boost::shared_ptr<ALLEGRO_DISPLAY> ALLEGRO_DISPLAY_Ptr;
typedef boost::shared_ptr<ALLEGRO_EVENT_QUEUE> ALLEGRO_EVENT_QUEUE_Ptr;
typedef boost::shared_ptr<ALLEGRO_TIMER> ALLEGRO_TIMER_Ptr;

#endif

