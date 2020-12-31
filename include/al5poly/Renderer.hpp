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

#ifndef RENDERER_HPP
    #define RENDERER_HPP

namespace al5poly
{
    class Renderer;
}

    #include "al5poly/altypedef.hpp"
    #include "al5poly/ICamera.hpp"
    #include "al5poly/IGameTime.hpp"
    #include "al5poly/IRenderer.hpp"

namespace al5poly
{
    class Renderer:
        public IRenderer
    {
    private:
        ALLEGRO_DISPLAY_Ptr display_;
    public:
        Renderer(const ALLEGRO_DISPLAY_Ptr);

        int getScreenX(const IRenderable &, const ICamera &) const;
        int getScreenY(const IRenderable &, const ICamera &) const;

        void paint(void) const;
        void paint(ALLEGRO_COLOR) const;
        void paint(
                ALLEGRO_COLOR,
                ALLEGRO_BITMAP_Ptr,
                int = 0,
                int = 0,
                int = 0) const;

        void render(
                const IGameTime &,
                const ICamera &,
                const IRenderable &);
    };
}

#endif

