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

#ifndef ASSET_MANAGER_HPP
    #define ASSET_MANAGER_HPP

    #include <allegro5/allegro.h>
    #include <cstdarg>
    #include <map>

namespace al5poly
{
    class AssetManager;
}

    #include "al5poly/altypedef.hpp"
    #include "al5poly/Animation.hpp"
    #include "al5poly/IAnimation.hpp"
    #include "AssetManagerException.hpp"

#define AL5POLY_ERROR_COLOR (al_map_rgb(255, 0, 254))
#define AL5POLY_MAGIC_PINK (al_map_rgb(255, 0, 255))

namespace al5poly
{
    class AssetManager
    {
        typedef std::map<std::string, al5poly::IAnimation::Ptr> AnimationMap;
        typedef std::map<std::string, al5poly::ALLEGRO_BITMAP_Ptr> BitmapMap;
        typedef std::map<std::string, ALLEGRO_COLOR> ColorMap;

        AnimationMap animations_;
        BitmapMap bitmaps_;
        ColorMap colors_;
    public:
        std::string dumpToJson(void) const;
        std::string getAssetPath(const std::string &) const;
        ALLEGRO_PATH * getAssetsRootPath(void) const;

        void addAnimation(
                    const std::string &,
                    const al5poly::IAnimation::Ptr &);
        al5poly::IAnimation::Ptr getAnimation(const std::string &) const;
        al5poly::IAnimation::Ptr loadAnimation(
                const std::string name,
                const int numFrames,
                ...);

        void addBitmap(
                    const std::string &,
                    const al5poly::ALLEGRO_BITMAP_Ptr &);
        al5poly::ALLEGRO_BITMAP_Ptr getBitmap(const std::string &) const;
        al5poly::ALLEGRO_BITMAP_Ptr loadBitmap(
                const std::string &,
                const std::string &,
                const bool);

        void addColor(const std::string &, ALLEGRO_COLOR);
        ALLEGRO_COLOR createColor(
                const std::string &,
                unsigned char,
                unsigned char,
                unsigned char,
                unsigned char = 255);
        ALLEGRO_COLOR createColor(
                const std::string &,
                int,
                int,
                int,
                int = 255);
        ALLEGRO_COLOR createColor(
                const std::string &,
                float,
                float,
                float,
                float = 1.0);
        ALLEGRO_COLOR getColor(
                const std::string &,
                bool throwOnMismatch = true) const;

        const char * printColor(const std::string &) const;

        static const char * printColor(ALLEGRO_COLOR);
    };
}

#endif
