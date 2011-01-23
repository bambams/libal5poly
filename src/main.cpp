/*
 * libal5poly is a game library abstraction library. xD
 * Copyright (C) 2010 Brandon McCaig
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

#include <allegro5/allegro5.h>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

#include "altypedef.hpp"
#include "Animation.hpp"
#include "Camera.hpp"
#include "Clock.hpp"
#include "IAnimation.hpp"
#include "IException.hpp"
#include "IGameTime.hpp"
#include "Player.hpp"
#include "Renderer.hpp"

ALLEGRO_BITMAP_Ptr createColoredBoxSprite(
        const int w,
        const int h,
        const ALLEGRO_COLOR);

void initializeAllegro5(
        ALLEGRO_DISPLAY_Ptr &,
        ALLEGRO_TIMER_Ptr &,
        ALLEGRO_EVENT_QUEUE_Ptr &);

IAnimation::StringMap loadAnimations(const int, const int);

void centerPlayer(
        Player &,
        const int,
        const int,
        const ALLEGRO_DISPLAY_Ptr);

int main(int argc, char * argv[]) try
{
    ALLEGRO_DISPLAY_Ptr display;
    ALLEGRO_TIMER_Ptr timer;
    ALLEGRO_EVENT_QUEUE_Ptr eventQueue;

    initializeAllegro5(display, timer, eventQueue);

    al_set_target_bitmap(al_get_backbuffer(display.get()));

    al_clear_to_color(al_map_rgb(0, 0, 0));

    const int boxWidth = 100;
    const int boxHeight = 100;

    Camera camera;
    Clock clock;
    Player player(loadAnimations(boxWidth, boxHeight));
    Renderer renderer(display);

    centerPlayer(player, boxWidth, boxHeight, display);

    al_start_timer(timer.get());

    int direction = 0;

    while(clock.getGameTime()->getTicks() < 600)
    {
        ALLEGRO_EVENT event;
        bool redraw = false;

        al_wait_for_event(eventQueue.get(), &event);

        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            clock.tick();

            IGameTime::Ptr gameTime(clock.getGameTime());
            int ticks = gameTime->getTicks();

            if(ticks == 400)
            {
                player.setCurrentAnimation("brg");
                player.beginAnimation(5, *gameTime);
            }
            else if(ticks == 200)
            {
                player.setCurrentAnimation("gbr");
                player.beginAnimation(15, *gameTime);
            }
            else if(ticks == 10)
            {
                player.setCurrentAnimation("rgb");
                player.beginAnimation(30, *gameTime);
            }

            // Simple camera movement. Note the "player" (i.e., box)
            // doesn't move.
            switch(direction)
            {
                case 0:
                    if(camera.getX() < 250)
                        camera.setX(camera.getX() + 5);
                    break;
                case 1:
                    if(camera.getY() < 150)
                        camera.setY(camera.getY() + 5);
                    break;
                case 2:
                    if(camera.getX() > -250)
                        camera.setX(camera.getX() - 5);
                    break;
                case 3:
                    if(camera.getY() > -150)
                        camera.setY(camera.getY() - 5);
                    break;
            }

            // When camera reaches one boundary change directions.
            if(direction == 0 && camera.getX() >= 250)
                direction = 1;
            else if(direction == 1 && camera.getY() >= 150)
                direction = 2;
            else if(direction == 2 && camera.getX() <= -250)
                direction = 3;
            else if(direction == 3 && camera.getY() <= -150)
                direction = 0;
            
            redraw = true;
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN &&
                event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            break;
        }
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }

        if(redraw)
        {
            try
            {
                renderer.render(*clock.getGameTime(), camera, player);
                renderer.paint();
            }
            catch(IException & ex)
            {
                std::cerr << ex.getMessage() << std::endl;
            }
        }
    }

    return 0;
}
catch(std::exception & ex)
{
    std::cerr << ex.what() << std::endl;

    return 1;
}

void centerPlayer(
        Player & player,
        const int w,
        const int h,
        const ALLEGRO_DISPLAY_Ptr display)
{
    ALLEGRO_BITMAP * backbuffer = al_get_backbuffer(display.get());
    int displayWidth = al_get_bitmap_width(backbuffer);
    int displayHeight = al_get_bitmap_height(backbuffer);

    player.setX(displayWidth / 2.0 - w / 2.0);
    player.setY(displayHeight / 2.0 - h / 2.0);
}

ALLEGRO_BITMAP_Ptr createColoredBoxSprite(
        int w,
        int h,
        ALLEGRO_COLOR color)
{
    ALLEGRO_BITMAP_Ptr sprite(
            al_create_bitmap(w, h),
            al_destroy_bitmap);

    if(!sprite)
        Exception("Failed to create colored box sprite!").raise();

    al_set_target_bitmap(sprite.get());

    al_clear_to_color(color);

    return sprite;
}

void initializeAllegro5(
        ALLEGRO_DISPLAY_Ptr & display,
        ALLEGRO_TIMER_Ptr & timer,
        ALLEGRO_EVENT_QUEUE_Ptr & eventQueue)
{
    const int FPS = 30;

    if(!al_init())
        Exception("Failed to initialize Allegro 5!").raise();

    al_set_new_display_flags(ALLEGRO_WINDOWED);

    ALLEGRO_DISPLAY_Ptr d(
            al_create_display(800, 600),
            al_destroy_display);

    if(!d)
        Exception("Failed to create Allegro 5 display!").raise();

    display = d;

    if(!al_install_keyboard())
        Exception("Failed to install Allegro 5 keyboard!").raise();

    ALLEGRO_TIMER_Ptr t(
            al_create_timer(1.0 / FPS),
            al_destroy_timer);

    if(!t)
        Exception("Failed to create Allegro 5 timer!").raise();

    timer = t;

    ALLEGRO_EVENT_QUEUE_Ptr eQ(
            al_create_event_queue(),
            al_destroy_event_queue);

    if(!eQ)
        Exception("Failed to create Allegro 5 event queue!").raise();

    eventQueue = eQ;

    al_register_event_source(
            eventQueue.get(),
            al_get_display_event_source(display.get()));

    al_register_event_source(
            eventQueue.get(),
            al_get_keyboard_event_source());

    al_register_event_source(
            eventQueue.get(),
            al_get_timer_event_source(timer.get()));
}

IAnimation::StringMap loadAnimations(
        const int boxWidth,
        const int boxHeight)
{
    ALLEGRO_BITMAP_Ptr redBox(createColoredBoxSprite(
            boxWidth,
            boxHeight,
            al_map_rgb(255, 0, 0)));

    ALLEGRO_BITMAP_Ptr greenBox(createColoredBoxSprite(
            boxWidth,
            boxHeight,
            al_map_rgb(0, 255, 0)));

    ALLEGRO_BITMAP_Ptr blueBox(createColoredBoxSprite(
            boxWidth,
            boxHeight,
            al_map_rgb(0, 0, 255)));

    ALLEGRO_BITMAP_Ptr_Vector rgb_sprites;

    rgb_sprites.push_back(redBox);
    rgb_sprites.push_back(blueBox);
    rgb_sprites.push_back(greenBox);

    IAnimation::Ptr rgb_animation(new Animation(rgb_sprites));

    ALLEGRO_BITMAP_Ptr_Vector gbr_sprites;

    gbr_sprites.push_back(greenBox);
    gbr_sprites.push_back(blueBox);
    gbr_sprites.push_back(redBox);

    IAnimation::Ptr gbr_animation(new Animation(gbr_sprites));

    ALLEGRO_BITMAP_Ptr_Vector brg_sprites;

    brg_sprites.push_back(blueBox);
    brg_sprites.push_back(redBox);
    brg_sprites.push_back(greenBox);

    IAnimation::Ptr brg_animation(new Animation(brg_sprites));

    IAnimation::StringMap animations;

    animations.insert(std::make_pair("rgb", rgb_animation));
    animations.insert(std::make_pair("gbr", gbr_animation));
    animations.insert(std::make_pair("brg", brg_animation));

    return animations;
}

