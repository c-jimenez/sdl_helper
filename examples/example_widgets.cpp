/*
MIT License

Copyright (c) 2023 Cedric Jimenez

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <cstdlib>
#include <iostream>

#include "animation.h"
#include "fonts_db.h"
#include "image.h"
#include "label.h"
#include "scene.h"
#include "sprite.h"
#include "sprites_db.h"

using namespace std;
using namespace widgets;

/** @brief Custom scene to display animated widgets */
class my_scene : public game::scene
{
public:
    /** @brief Constructor */
    my_scene(game::fonts_db& fonts, sdl::window& window)
        : scene(fonts, window),
        m_anim_db(this->get_renderer()),
        m_image(this->get_renderer()),
        m_sprite1(this->get_renderer()),
        m_sprite2(this->get_renderer())
    {
        // Diplay framerate on the screen
        set_fps_display(true);

        // Setup a virtual screen to enable automatic resize
        set_virtual_screen(true);
        set_virtual_screen_fit(false);
        set_virtual_screen_size(1024, 768);
        set_virtual_screen_bg_color({ 128, 128, 128, 255 });

        // Image widget
        m_image.load(ASSETS_DIRECTORY "/samurai/PNG/Samurai - 02/PNG Sequences/Idle/Idle_001.png");
        m_image.set_position({ 100, 150 });
        m_image.set_size({ 0, 0, 200, 300 });
        m_image.set_autosize(false);
        m_image.set_background_color({ 128, 0, 0, 255 });
        m_image.set_adjust(widget::adjust::fit);

        // Load sprite animations
        m_anim_db.load_animation("Samurai1_Idle", ASSETS_DIRECTORY "/samurai/PNG/Samurai - 01/PNG Sequences/Idle", "Idle");
        m_anim_db.load_animation(
            "Samurai1_IdleBlinking", ASSETS_DIRECTORY "/samurai/PNG/Samurai - 01/PNG Sequences/Idle Blinking", "Idle Blinking");
        m_anim_db.load_animation("Samurai1_Walking", ASSETS_DIRECTORY "/samurai/PNG/Samurai - 01/PNG Sequences/Walking", "Walking");
        m_anim_db.load_animation("Samurai1_Attacking", ASSETS_DIRECTORY "/samurai/PNG/Samurai - 01/PNG Sequences/Attacking", "Attacking");
        m_anim_db.load_animation("Samurai1_Dying", ASSETS_DIRECTORY "/samurai/PNG/Samurai - 01/PNG Sequences/Dying", "Dying");
        m_anim_db.load_animation("Samurai1_Hurt", ASSETS_DIRECTORY "/samurai/PNG/Samurai - 01/PNG Sequences/Hurt", "Hurt");
        m_anim_db.load_animation("Samurai1_Taunt", ASSETS_DIRECTORY "/samurai/PNG/Samurai - 01/PNG Sequences/Taunt", "Taunt");
        m_anim_db.load_animation("Samurai1_JumpLoop", ASSETS_DIRECTORY "/samurai/PNG/Samurai - 01/PNG Sequences/Jump Loop", "Jump Loop");
        m_anim_db.load_animation("Samurai1_JumpStart", ASSETS_DIRECTORY "/samurai/PNG/Samurai - 01/PNG Sequences/Jump Start", "Jump Start");

        m_anim_db.load_animation("Samurai3_Idle", ASSETS_DIRECTORY "/samurai/PNG/Samurai - 03/PNG Sequences/Idle", "Idle");
        m_anim_db.load_animation(
            "Samurai3_IdleBlinking", ASSETS_DIRECTORY "/samurai/PNG/Samurai - 03/PNG Sequences/Idle Blinking", "Idle Blinking");
        m_anim_db.load_animation("Samurai3_Walking", ASSETS_DIRECTORY "/samurai/PNG/Samurai - 03/PNG Sequences/Walking", "Walking");
        m_anim_db.load_animation("Samurai3_Attacking", ASSETS_DIRECTORY "/samurai/PNG/Samurai - 03/PNG Sequences/Attacking", "Attacking");
        m_anim_db.load_animation("Samurai3_Dying", ASSETS_DIRECTORY "/samurai/PNG/Samurai - 03/PNG Sequences/Dying", "Dying");
        m_anim_db.load_animation("Samurai3_Hurt", ASSETS_DIRECTORY "/samurai/PNG/Samurai - 03/PNG Sequences/Hurt", "Hurt");
        m_anim_db.load_animation("Samurai3_Taunt", ASSETS_DIRECTORY "/samurai/PNG/Samurai - 03/PNG Sequences/Taunt", "Taunt");
        m_anim_db.load_animation("Samurai3_JumpLoop", ASSETS_DIRECTORY "/samurai/PNG/Samurai - 03/PNG Sequences/Jump Loop", "Jump Loop");
        m_anim_db.load_animation("Samurai3_JumpStart", ASSETS_DIRECTORY "/samurai/PNG/Samurai - 03/PNG Sequences/Jump Start", "Jump Start");

        // Apply animation to sprite 1
        m_sprite1.add_img_animation(0, m_anim_db.get("Samurai1_Idle"));
        m_sprite1.add_img_animation(1, m_anim_db.get("Samurai1_IdleBlinking"));
        m_sprite1.add_img_animation(2, m_anim_db.get("Samurai1_Walking"));
        m_sprite1.add_img_animation(3, m_anim_db.get("Samurai1_Attacking"));
        m_sprite1.add_img_animation(4, m_anim_db.get("Samurai1_Dying"));
        m_sprite1.add_img_animation(5, m_anim_db.get("Samurai1_Hurt"));
        m_sprite1.add_img_animation(6, m_anim_db.get("Samurai1_Taunt"));
        m_sprite1.add_img_animation(7, m_anim_db.get("Samurai1_JumpLoop"));
        m_sprite1.add_img_animation(8, m_anim_db.get("Samurai1_JumpStart"));
        m_sprite1.set_img_animation(0);
        m_sprite1.set_position({ 200, 150 });
        m_sprite1.set_framerate(30.f);

        // Apply animation to sprite 2
        m_sprite2.add_img_animation(0, m_anim_db.get("Samurai3_Idle"));
        m_sprite2.add_img_animation(1, m_anim_db.get("Samurai3_IdleBlinking"));
        m_sprite2.add_img_animation(2, m_anim_db.get("Samurai3_Walking"));
        m_sprite2.add_img_animation(3, m_anim_db.get("Samurai3_Attacking"));
        m_sprite2.add_img_animation(4, m_anim_db.get("Samurai3_Dying"));
        m_sprite2.add_img_animation(5, m_anim_db.get("Samurai3_Hurt"));
        m_sprite2.add_img_animation(6, m_anim_db.get("Samurai3_Taunt"));
        m_sprite2.add_img_animation(7, m_anim_db.get("Samurai3_JumpLoop"));
        m_sprite2.add_img_animation(8, m_anim_db.get("Samurai3_JumpStart"));
        m_sprite2.set_img_animation(3);
        m_sprite2.set_position({ 400, 150 });
        m_sprite2.set_framerate(30.f);
        m_sprite2.get_transform().set_flip(SDL_FLIP_HORIZONTAL);

        // Initialize transformations to sprite 1
        m_anim = 0;
        m_scale = 1.f;
        m_rot = 0.;

        // Start animation on sprite 2
        m_sprite2.get_animation() = animation(true,
            { {2.f, 270., SDL_FLIP_NONE, 1s},
             animation::scaling_step(1.2f, 250ms),
             animation::scaling_step(1.f, 250ms),
             animation::scaling_step(1.5f, 250ms),
             animation::scaling_step(1.2f, 250ms),
             animation::scaling_step(2.f, 250ms),
             animation::rotation_step(180., 500ms),
             animation::scaling_step(1.f, 250ms),
             animation::rotation_step(0., 250ms),
             animation::flip_step(SDL_FLIP_HORIZONTAL, 250ms),
             animation::flip_step(SDL_FLIP_VERTICAL, 250ms),
             animation::flip_step(SDL_FLIP_HORIZONTAL, 250ms),
             animation::flip_step(SDL_FLIP_NONE, 250ms) });
        m_sprite2.get_animation().start();
    }

protected:
    /** @brief Called to handle an input event */
    void on_input_event(const SDL_Event& event) override
    {
        if (event.type == SDL_KEYDOWN)
        {
            int anim = m_anim;
            if (event.key.keysym.sym == SDLK_LEFT)
            {
                anim--;
            }
            if (event.key.keysym.sym == SDLK_RIGHT)
            {
                anim++;
            }
            if (event.key.keysym.sym == SDLK_UP)
            {
                m_scale += 0.1f;
            }
            if (event.key.keysym.sym == SDLK_DOWN)
            {
                m_scale -= 0.1f;
            }
            if (event.key.keysym.sym == SDLK_a)
            {
                m_rot += 5.;
            }
            if (event.key.keysym.sym == SDLK_z)
            {
                m_rot -= 5.;
            }
            if (anim != m_anim)
            {
                m_anim = anim;
                m_sprite1.set_img_animation(m_anim);
            }
            m_sprite1.get_transform().set_scaling(m_scale);
            m_sprite1.get_transform().set_rot_angle(m_rot);
        }

        // This event is triggered when all the textures must be redrawn
        if (event.type == SDL_RENDER_TARGETS_RESET)
        {
            m_image.update_needed();
            m_sprite1.update_needed();
            m_sprite2.update_needed();
        }
    }

    /** @brief Called to render the scene */
    void on_render() override
    {
        // Render widgets
        m_image.render();
        m_sprite1.render();
        m_sprite2.render();
    }

private:
    game::sprites_db        m_anim_db;
    image                   m_image;
    sprite                  m_sprite1;
    sprite                  m_sprite2;
    int                     m_anim;
    float                   m_scale;
    double                  m_rot;
};

/** @brief Entry point */
int main(int argc, char* argv[])
{
    // Ignore parameters
    (void)argc;
    (void)argv;

    // Initalize SDL
    auto sdl_lib = sdl::init(SDL_INIT_VIDEO);
    if (sdl_lib)
    {
        // Create a window
        sdl::window window = sdl::create_window(
            "My window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE  | SDL_WINDOW_OPENGL);
        if (window)
        {
            // Load font to display framerate
            game::fonts_db fonts;
            if (fonts.load(ASSETS_DIRECTORY "/freefont/FreeSans.woff", 20, "SCENE_FPS"))
            {
                cout << "Entering main loop" << endl;

                // Start scene
                my_scene scene(fonts, window);
                scene.start();

                cout << "Exiting main loop" << endl;
            }
            else
            {
                cout << "Unable to load font : " << sdl_lib->last_error() << endl;
            }
        }
        else
        {
            cout << "Unable to create window : " << sdl_lib->last_error() << endl;
        }
    }
    else
    {
        cout << "Unable to initialize SDL library : " << sdl::last_error() << endl;
    }

    return EXIT_SUCCESS;
}
