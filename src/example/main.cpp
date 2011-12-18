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

#include <allegro5/allegro5.h>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

#include "al5poly/altypedef.hpp"
#include "al5poly/Animation.hpp"
#include "al5poly/Camera.hpp"
#include "al5poly/Clock.hpp"
#include "al5poly/IAnimation.hpp"
#include "al5poly/IException.hpp"
#include "al5poly/IGameTime.hpp"
#include "al5poly/Player.hpp"
#include "al5poly/Renderer.hpp"

al5poly::ALLEGRO_BITMAP_Ptr createColoredBoxSprite(
        const int w,
        const int h,
        const ALLEGRO_COLOR);

void initializeAllegro5(
        al5poly::ALLEGRO_DISPLAY_Ptr &,
        al5poly::ALLEGRO_TIMER_Ptr &,
        al5poly::ALLEGRO_EVENT_QUEUE_Ptr &);

al5poly::IAnimation::StringMap loadAnimations(const int, const int);

void centerPlayer(
        al5poly::Player &,
        const int,
        const int,
        const al5poly::ALLEGRO_DISPLAY_Ptr);

int main(int argc, char * argv[]) try
{
    al5poly::ALLEGRO_DISPLAY_Ptr display;
    al5poly::ALLEGRO_TIMER_Ptr timer;
    al5poly::ALLEGRO_EVENT_QUEUE_Ptr eventQueue;

    initializeAllegro5(display, timer, eventQueue);

    al_set_target_bitmap(al_get_backbuffer(display.get()));

    al_clear_to_color(al_map_rgb(0, 0, 0));

    const int boxWidth = 100;
    const int boxHeight = 100;

    al5poly::Camera camera;
    al5poly::Clock clock;
    al5poly::Player player(loadAnimations(boxWidth, boxHeight));
    al5poly::Renderer renderer(display);

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

            al5poly::IGameTime::Ptr gameTime(clock.getGameTime());
            int ticks = gameTime->getTicks();

            if(ticks == 400)
            {
                player.setCurrentAnimation("br");
                player.beginAnimation(5, *gameTime);
            }
            else if(ticks == 200)
            {
                player.setCurrentAnimation("gb");
                player.beginAnimation(15, *gameTime);
            }
            else if(ticks == 10)
            {
                player.setCurrentAnimation("rg");
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
            catch(al5poly::IException & ex)
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
        al5poly::Player & player,
        const int w,
        const int h,
        const al5poly::ALLEGRO_DISPLAY_Ptr display)
{
    ALLEGRO_BITMAP * backbuffer = al_get_backbuffer(display.get());
    int displayWidth = al_get_bitmap_width(backbuffer);
    int displayHeight = al_get_bitmap_height(backbuffer);

    player.setX(displayWidth / 2.0 - w / 2.0);
    player.setY(displayHeight / 2.0 - h / 2.0);
}

al5poly::ALLEGRO_BITMAP_Ptr createColoredBoxSprite(
        int w,
        int h,
        ALLEGRO_COLOR color)
{
    al5poly::ALLEGRO_BITMAP_Ptr sprite(
            al_create_bitmap(w, h),
            al_destroy_bitmap);

    if(!sprite)
        al5poly::Exception("Failed to create colored box sprite!").raise();

    al_set_target_bitmap(sprite.get());

    al_clear_to_color(color);

    return sprite;
}

void initializeAllegro5(
        al5poly::ALLEGRO_DISPLAY_Ptr & display,
        al5poly::ALLEGRO_TIMER_Ptr & timer,
        al5poly::ALLEGRO_EVENT_QUEUE_Ptr & eventQueue)
{
    const int FPS = 30;

    if(!al_init())
        al5poly::Exception("Failed to initialize Allegro 5!").raise();

    al_set_new_display_flags(ALLEGRO_WINDOWED);

    al5poly::ALLEGRO_DISPLAY_Ptr d(
            al_create_display(800, 600),
            al_destroy_display);

    if(!d)
        al5poly::Exception("Failed to create Allegro 5 display!").raise();

    display = d;

    if(!al_install_keyboard())
        al5poly::Exception("Failed to install Allegro 5 keyboard!").raise();

    al5poly::ALLEGRO_TIMER_Ptr t(
            al_create_timer(1.0 / FPS),
            al_destroy_timer);

    if(!t)
        al5poly::Exception("Failed to create Allegro 5 timer!").raise();

    timer = t;

    al5poly::ALLEGRO_EVENT_QUEUE_Ptr eQ(
            al_create_event_queue(),
            al_destroy_event_queue);

    if(!eQ)
        al5poly::Exception("Failed to create Allegro 5 event queue!").raise();

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

al5poly::IAnimation::StringMap loadAnimations(
        const int boxWidth,
        const int boxHeight)
{
    al5poly::ALLEGRO_BITMAP_Ptr redBox(createColoredBoxSprite(
            boxWidth,
            boxHeight,
            al_map_rgb(255, 0, 0)));

    al5poly::ALLEGRO_BITMAP_Ptr greenBox(createColoredBoxSprite(
            boxWidth,
            boxHeight,
            al_map_rgb(0, 255, 0)));

    al5poly::ALLEGRO_BITMAP_Ptr blueBox(createColoredBoxSprite(
            boxWidth,
            boxHeight,
            al_map_rgb(0, 0, 255)));

    al5poly::ALLEGRO_BITMAP_Ptr_Vector rg_sprites;

    rg_sprites.push_back(redBox);
    rg_sprites.push_back(greenBox);

    al5poly::IAnimation::Ptr rg_animation(new al5poly::Animation(rg_sprites));

    al5poly::ALLEGRO_BITMAP_Ptr_Vector gb_sprites;

    gb_sprites.push_back(greenBox);
    gb_sprites.push_back(blueBox);

    al5poly::IAnimation::Ptr gb_animation(new al5poly::Animation(gb_sprites));

    al5poly::ALLEGRO_BITMAP_Ptr_Vector br_sprites;

    br_sprites.push_back(blueBox);
    br_sprites.push_back(redBox);

    al5poly::IAnimation::Ptr br_animation(new al5poly::Animation(br_sprites));

    al5poly::IAnimation::StringMap animations;

    animations.insert(std::make_pair("rg", rg_animation));
    animations.insert(std::make_pair("gb", gb_animation));
    animations.insert(std::make_pair("br", br_animation));

    return animations;
}

