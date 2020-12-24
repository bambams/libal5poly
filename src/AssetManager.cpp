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

#include "al5poly/AssetManager.hpp"

namespace al5poly
{
    void AssetManager::addAnimation(
                const std::string & name,
                const al5poly::IAnimation::Ptr & animation)
    {
        this->animations_[name] = animation;
    }

    void AssetManager::addBitmap(
                const std::string & name,
                const al5poly::ALLEGRO_BITMAP_Ptr & bitmap)
    {
        this->bitmaps_[name] = bitmap;
    }

    IAnimation::Ptr AssetManager::getAnimation(
            const std::string & name) const
    {
        AnimationMap::const_iterator it = this->animations_.find(name);

        if(it == this->animations_.end())
        {
            std::string msg = "Animation asset not found: " + name;
            AssetManagerException(msg).raise();
        }

        return (*it).second;
    }

    std::string AssetManager::getAssetPath(const std::string & asset) const
    {
        ALLEGRO_PATH * path = this->getAssetsRootPath();
        ALLEGRO_PATH * assetPath = al_create_path(asset.c_str());

        if(assetPath == 0 || !al_join_paths(path, assetPath))
        {
            std::string msg = "Failed to build asset path: " + asset;
            AssetManagerException(msg).raise();
        }

        al_destroy_path(assetPath);

        std::string str(al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP));

        al_destroy_path(path);

        return str;
    }

    ALLEGRO_PATH * AssetManager::getAssetsRootPath(void) const
    {
        ALLEGRO_PATH * path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);

        if(path == 0)
        {
            AssetManagerException("Failed to find asset root:").raise();
        }

        al_drop_path_tail(path);
        al_append_path_component(path, "assets");

        return path;
    }

    ALLEGRO_BITMAP_Ptr AssetManager::getBitmap(
            const std::string & name) const
    {
        BitmapMap::const_iterator it = this->bitmaps_.find(name);

        if(it == this->bitmaps_.end())
        {
            std::string msg = std::string("Bitmap asset not found: ") + name;
            AssetManagerException(msg).raise();
        }

        return (*it).second;
    }

    IAnimation::Ptr AssetManager::loadAnimation(
            const std::string name,
            const int numFrames,
            ...)
    {
        ALLEGRO_BITMAP_Ptr_Vector sprites;
        va_list ap;

        va_start(ap, numFrames);

        for(int i=0; i<numFrames; i++)
        {
            const char * const name = va_arg(ap, const char *);

            sprites.push_back(this->getBitmap(name));
        }

        va_end(ap);

        IAnimation::Ptr animation(
                new Animation(sprites));

        this->animations_.insert(std::make_pair(name, animation));

        return animation;
    }

    ALLEGRO_BITMAP_Ptr AssetManager::loadBitmap(
            const std::string & name,
            const std::string & path,
            const bool magicPinkAlpha = false)
    {
        const ALLEGRO_COLOR MAGIC_PINK = al_map_rgb(255, 0, 255);

        ALLEGRO_BITMAP_Ptr bitmap(
                al_load_bitmap(this->getAssetPath(path).c_str()),
                al_destroy_bitmap);

        if(bitmap.get() == 0)
        {
            std::string msg = std::string(
                    "Failed to load bitmap asset: " + name +
                    " (" + path + ")");
            Exception(msg).raise();
        }

        if(magicPinkAlpha)
        {
            al_convert_mask_to_alpha(bitmap.get(), MAGIC_PINK);
        }

        this->bitmaps_.insert(std::make_pair(name, bitmap));

        return bitmap;
    }

    void AssetManager::addColor(
            const std::string & name,
            ALLEGRO_COLOR color)
    {
        this->colors_.insert(std::make_pair(name, color));
    }

    ALLEGRO_COLOR AssetManager::createColor(
            const std::string & name,
            unsigned char red,
            unsigned char green,
            unsigned char blue,
            unsigned char alpha)
    {
        ALLEGRO_COLOR value = al_map_rgba(red, green, blue, alpha);

        this->colors_.insert(std::make_pair(name, value));

        return value;
    }

    ALLEGRO_COLOR AssetManager::createColor(
            const std::string & name,
            int red,
            int green,
            int blue,
            int alpha)
    {
        return this->createColor(
                name,
                (unsigned char)red,
                (unsigned char)green,
                (unsigned char)blue);
    }

    ALLEGRO_COLOR AssetManager::createColor(
            const std::string & name,
            float red,
            float green,
            float blue,
            float alpha)
    {
        ALLEGRO_COLOR value = al_map_rgba_f(red, green, blue, alpha);

        this->colors_.insert(std::make_pair(name, value));

        return value;
    }

    ALLEGRO_COLOR AssetManager::getColor(const std::string & name) const
    {
        ColorMap::const_iterator it = this->colors_.find(name);

        if(it == this->colors_.end())
        {
            std::string msg = "Color asset not found: " + name;

            AssetManagerException(msg).raise();
        }

        return (*it).second;
    }

    const char * AssetManager::printColor(const std::string & name) const
    {
        return printColor(this->getColor(name));
    }

    const char * AssetManager::printColor(ALLEGRO_COLOR color)
    {
        static char buffer[50] = {0};

        unsigned char red, green, blue, alpha;

        al_unmap_rgba(color, &red, &green, &blue, &alpha);

        snprintf(buffer, 50, "{\"r\": %d, \"g\": %d, \"b\": %d, \"a\": %d}",
                (int)red, (int)green, (int)blue, (int)alpha);

        return buffer;
    }
}
