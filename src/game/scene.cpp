/*
Copyright (c) 2023 Cedric Jimenez
This file is part of SDLHelper.

SDLHelper is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 2.1 of the License, or
(at your option) any later version.

SDLHelper is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with SDLHelper. If not, see <http://www.gnu.org/licenses/>.
*/

#include "scene.h"
#include "fonts_db.h"
#include "label.h"

#include <chrono>
#include <iomanip>
#include <sstream>
#include <thread>

using namespace std::chrono_literals;

namespace game
{

/** @brief Constructor */
scene::scene(fonts_db& fonts, sdl::window& window, bool is_fixed_fps, float fps)
    : m_fonts(fonts),
      m_window(window),
      m_renderer(m_window->create_renderer()),
      m_bg_color{0, 0, 0, 255},
      m_is_fixed_fps(is_fixed_fps),
      m_fixed_fps(fps),
      m_fps(0.f),
      m_is_fps_display_enabled(false),
      m_is_virtual_screen_enabled(false),
      m_virtual_screen_fit(false),
      m_virtual_screen_size{0, 0, 0, 0},
      m_virtual_screen_bg_color{0, 0, 0, 255}
{
    // Initialize the renderer for the scene
    m_renderer->set_blend_mode(SDL_BLENDMODE_BLEND);
}

/** @brief Destructor */
scene::~scene() { }

/** @brief Start the scene */
void scene::start()
{
    // Label for framerate display
    widgets::label fps_label(m_renderer);
    fps_label.set_text("0 FPS");
    fps_label.set_font(m_fonts.get("SCENE_FPS"));
    fps_label.set_text_color({0, 255, 0, 0});

    // Compute framerate period in case of fixed framerate
    float scene_period_us = 1000000.f / m_fixed_fps;
    auto  scene_period    = std::chrono::microseconds(static_cast<int64_t>(scene_period_us));

    // Initialize virtual screen
    float        virtual_screen_ratio = 0.f;
    sdl::texture virtual_screen_texture;
    if (m_is_virtual_screen_enabled)
    {
        virtual_screen_texture = m_renderer->create_texture(
            SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, m_virtual_screen_size.w, m_virtual_screen_size.h);
        if (virtual_screen_texture)
        {
            virtual_screen_ratio = static_cast<float>(m_virtual_screen_size.w) / static_cast<float>(m_virtual_screen_size.h);
        }
    }

    // Scene loop
    bool exit                 = false;
    auto next_period          = std::chrono::steady_clock::now();
    auto last_fps_computation = std::chrono::steady_clock::now();
    do
    {
        // Compute next period in case of fixed framerate
        next_period += scene_period;

        // Handle inputs
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0)
        {
            // Window closing event
            if ((event.type == SDL_WINDOWEVENT) && (event.window.event == SDL_WINDOWEVENT_CLOSE))
            {
                exit = true;
            }

            // Notify event
            on_input_event(event);
        }

        // Cleanup background
        m_renderer->set_draw_color(m_bg_color);
        m_renderer->clear();

        // Cleanup virtual screen
        if (virtual_screen_texture)
        {
            m_renderer->push_texture(virtual_screen_texture);
            m_renderer->set_draw_color(m_virtual_screen_bg_color);
            m_renderer->fill_rect(m_renderer->get_draw_rect());
        }

        // Render scene
        on_render();

        // Regulate framerate
        if (m_is_fixed_fps)
        {
            std::this_thread::sleep_until(next_period);
        }

        // Compute framerate
        auto now             = std::chrono::steady_clock::now();
        auto delta           = now - last_fps_computation;
        m_fps                = 1000000000.f / static_cast<float>(delta.count());
        last_fps_computation = now;

        // Displaye famerate
        if (m_is_fps_display_enabled)
        {
            std::stringstream ss;
            ss << std::setw(6) << std::setprecision(1) << std::fixed << m_fps << " FPS";
            fps_label.set_text(ss.str());
            fps_label.render();
        }

        // Render virtual screen
        if (virtual_screen_texture)
        {
            m_renderer->pop_texture();
            if (m_virtual_screen_fit)
            {
                m_renderer->copy(virtual_screen_texture, nullptr, nullptr);
            }
            else
            {
                // Compute output rectangle with the virtual screen ratio
                SDL_Rect dst_rect        = m_renderer->get_draw_rect();
                int      renderer_width  = dst_rect.w;
                int      renderer_height = dst_rect.h;
                float    renderer_ratio  = static_cast<float>(renderer_width) / static_cast<float>(renderer_height);
                if (virtual_screen_ratio >= renderer_ratio)
                {
                    dst_rect.h = static_cast<int>(static_cast<float>(renderer_width) / virtual_screen_ratio);
                    dst_rect.y = (renderer_height - dst_rect.h) / 2;
                }
                else
                {
                    dst_rect.w = static_cast<int>(static_cast<float>(renderer_height) * virtual_screen_ratio);
                    dst_rect.x = (renderer_width - dst_rect.w) / 2;
                }
                m_renderer->copy(virtual_screen_texture, nullptr, &dst_rect);
            }
        }

        // Display the scene
        m_renderer->present();
    } while (!exit);
}

/** @brief Set the size of the virtual screen (must be called before start()) */
void scene::set_virtual_screen_size(int width, int height)
{
    m_virtual_screen_size.w = width;
    m_virtual_screen_size.h = height;
}

} // namespace game
