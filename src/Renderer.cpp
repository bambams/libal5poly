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

#include "al5poly/Renderer.hpp"

namespace al5poly
{
    Renderer::Renderer(const ALLEGRO_DISPLAY_Ptr display):
        display_(display)
    {
        assert(display);
    }

    int Renderer::getScreenX(
            const IRenderable & renderable,
            const ICamera & camera) const
    {
        return renderable.getX() - camera.getX();
    }

    int Renderer::getScreenY(
            const IRenderable & renderable,
            const ICamera & camera) const
    {
        return renderable.getY() - camera.getY();
    }

    void Renderer::paint(void) const
    {
        this->paint(al_map_rgb(0, 0, 0));
    }

    void Renderer::paint(ALLEGRO_COLOR color) const
    {
        al_flip_display();

        al_set_target_bitmap(al_get_backbuffer(this->display_.get()));

        al_clear_to_color(color);
    }

    void Renderer::paint(
            ALLEGRO_COLOR color,
            ALLEGRO_BITMAP_Ptr bitmap,
            int x,
            int y,
            int flags) const
    {
        al_flip_display();

        al_set_target_bitmap(al_get_backbuffer(this->display_.get()));

        al_clear_to_color(color);

        al_draw_bitmap(bitmap.get(), x, y, flags);
    }

    void Renderer::render(
            const IGameTime & gameTime,
            const ICamera & camera,
            const IRenderable & renderable)
    {
        IFrame::Ptr frame = renderable.getCurrentFrame(gameTime);
        ALLEGRO_BITMAP_Ptr sprite = frame->getSprite();
        int x = this->getScreenX(renderable, camera);
        int y = this->getScreenY(renderable, camera);

        al_set_target_bitmap(al_get_backbuffer(this->display_.get()));

        int flags = 0;

        switch(renderable.getOrientation())
        {
            case AL5POLY_ORIENTATION_FLIPPED_HORIZONTAL:
                flags |= ALLEGRO_FLIP_HORIZONTAL;
                break;
            case AL5POLY_ORIENTATION_FLIPPED_VERTICAL:
                flags |= ALLEGRO_FLIP_VERTICAL;
                break;
        }

        al_draw_bitmap(sprite.get(), x, y, flags);
    }
}

