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

#include "sdl.h"

using namespace std;

/** @brief Render some objects on the screen */
static void render(sdl::renderer& renderer, bool draw_texture = true);

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
            "My window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
        if (window)
        {
            // Create a render to draw some objects
            sdl::renderer renderer = window->create_renderer();
            if (renderer)
            {
                cout << "Entering main loop" << endl;

                // Main loop
                bool end = false;
                while (!end)
                {
                    // Handle events
                    SDL_Event event;
                    while (SDL_PollEvent(&event) != 0)
                    {
                        // Window closing event
                        if ((event.type == SDL_WINDOWEVENT) && (event.window.event == SDL_WINDOWEVENT_CLOSE))
                        {
                            end = true;
                        }
                    }

                    // Update screen
                    render(renderer);
                }

                cout << "Exiting main loop" << endl;
            }
            else
            {
                cout << "Unable to create renderer : " << sdl_lib->last_error() << endl;
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

/** @brief Render some objects on the screen */
static void render(sdl::renderer& renderer, bool draw_texture)
{
    // Clear screen before doing any rendering
    renderer->set_draw_color({0, 0, 0, 255});
    renderer->clear();

    // Draw a red line
    renderer->set_draw_color({255, 0, 0, 255});
    renderer->draw_line({10, 10}, {10, 50});

    // Draw a green rectangle
    renderer->set_draw_color({0, 255, 0, 255});
    renderer->draw_rect({20, 10, 100, 30});

    // Draw a rectangle filled in blue
    renderer->set_draw_color({0, 0, 255, 255});
    renderer->fill_rect({130, 10, 100, 30});

    // Load font and display text in yellow
    sdl::font font = sdl::create_font(ASSETS_DIRECTORY "/freefont/FreeSans.woff", 22);
    if (font)
    {
        auto text_surface = font->render_blended("Some text to display", {255, 255, 0, 255});
        if (text_surface)
        {
            auto text_texture = renderer->create_texture(text_surface);
            if (text_texture)
            {
                SDL_Rect text_size = text_texture->get_size();
                text_size.x        = 10;
                text_size.y        = 70;
                renderer->copy(text_texture, nullptr, &text_size);
            }
            else
            {
                cout << "Unable to create text texture : " << sdl::last_error() << endl;
            }
        }
        else
        {
            cout << "Unable to render text : " << sdl::last_error() << endl;
        }
    }
    else
    {
        cout << "Unable to create font : " << sdl::last_error() << endl;
    }

    // Load image and display it twice : 1 original and 1 flipped
    sdl::texture img_texture = renderer->create_texture(ASSETS_DIRECTORY "/samurai/PNG/Samurai - 01/PNG Sequences/Idle/Idle_001.png");
    if (img_texture)
    {
        // Display original
        SDL_Rect dst_rect = img_texture->get_size();
        dst_rect.x        = 100;
        dst_rect.y        = 70;
        renderer->copy(img_texture, nullptr, &dst_rect);

        // Display flipped
        dst_rect.x = 320;
        dst_rect.y = 70;
        renderer->copy(img_texture, nullptr, &dst_rect, 0., nullptr, SDL_FLIP_HORIZONTAL);
    }
    else
    {
        cout << "Unable to load image : " << sdl::last_error() << endl;
    }

    // Draw in a texture and render the texture
    if (draw_texture)
    {
        sdl::texture texture = renderer->create_texture(SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 768);
        if (texture)
        {
            // Push texture to renderer to draw on it
            renderer->push_texture(texture);

            // Draw to texture
            render(renderer, false);

            // Pop texture to restore original renderer drawing texture
            renderer->pop_texture();

            // Display texture in a cyan rectangle
            SDL_Rect dst_rect{10, 120, 200, 160};
            renderer->copy(texture, nullptr, &dst_rect);
            renderer->set_draw_color({0, 255, 255, 255});
            renderer->draw_rect(dst_rect);
        }
        else
        {
            cout << "Unable to create texture : " << sdl::last_error() << endl;
        }
    }

    // Display renderer contents
    renderer->present();
}
