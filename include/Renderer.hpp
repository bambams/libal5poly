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

#ifndef RENDERER_HPP
    #define RENDERER_HPP

class Renderer;

    #include "altypedef.hpp"
    #include "ICamera.hpp"
    #include "IGameTime.hpp"
    #include "IRenderer.hpp"

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
    void render(
            const IGameTime &,
            const ICamera &,
            const IRenderable &);
};

#endif

