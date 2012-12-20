#ifndef ASSET_MANAGER_HPP
    #define ASSET_MANAGER_HPP

    #include <allegro5/allegro5.h>
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

namespace al5poly
{
    class AssetManager
    {
        typedef std::map<std::string, al5poly::IAnimation::Ptr> AnimationMap;
        typedef std::map<std::string, al5poly::ALLEGRO_BITMAP_Ptr> BitmapMap;

        AnimationMap animations_;
        BitmapMap bitmaps_;
    public:
        std::string getAssetPath(const std::string &) const;
        ALLEGRO_PATH * getAssetsRootPath(void) const;

        al5poly::IAnimation::Ptr getAnimation(const std::string &) const;
        al5poly::IAnimation::Ptr loadAnimation(
                const std::string name,
                const int numFrames,
                ...);

        al5poly::ALLEGRO_BITMAP_Ptr getBitmap(const std::string &) const;
        al5poly::ALLEGRO_BITMAP_Ptr loadBitmap(
                const std::string &,
                const std::string &,
                const bool);
    };
}

#endif
