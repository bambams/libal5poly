#include "al5poly/AssetManager.hpp"

namespace al5poly
{
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
        ALLEGRO_PATH * path = getAssetsRootPath();
        ALLEGRO_PATH * assetPath = al_create_path(asset.c_str());

        if(assetPath == 0)
        {
            std::string msg = "Failed to build asset path: " + asset;
            AssetManagerException(msg).raise();
        }

        al_join_paths(path, assetPath);

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
}
