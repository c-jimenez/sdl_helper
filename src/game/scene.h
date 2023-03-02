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

#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "sdl.h"
#include "widget.h"

#include <set>

namespace game
{

// Forward declarations
class fonts_db;

/** @brief Base class for a game scene */
class scene
{
  public:
    /** 
     * @brief Constructor 
     * @param fonts Fonts database
     * @param window Window which displays the scene
     * @param is_fixed_fps Indicate if the framerate must be fixed
     * @param fps Fixed framerate
     */
    scene(fonts_db& fonts, sdl::window& window, bool is_fixed_fps = true, float fps = 40.f);

    /** @brief Destructor */
    virtual ~scene();

    /** @brief Start the scene */
    void start();

    /** @brief Add a widget to the scene */
    bool add_widget(widgets::widget& widget);
    /** @brief Remove a widget from the scene */
    bool remove_widget(widgets::widget& widget);

  protected:
    /**
     * @brief Called to handle an input event
     * @param event Input event to handle
     */
    virtual void on_input_event(const SDL_Event& event) { (void)event; }

    /** @brief Called to render the scene */
    virtual void on_render();

    /** @brief Get the window which displays the scene */
    sdl::window& get_window() { return m_window; }

    /** @brief Get the renderer for the scene */
    sdl::renderer& get_renderer() { return m_renderer; }

    /** @brief Set the background of the scene */
    void set_bg_color(const SDL_Color& color) { m_bg_color = color; }

    /** @brief Enable/disable display of current framerate 
     *         The font database must have a "SCENE_FPS" font registered */
    void set_fps_display(bool is_enabled) { m_is_fps_display_enabled = is_enabled; }
    /** @brief Get the current framerate */
    float get_fps() const { return m_fps; }

    // Virtual screen allow to resize rendering automatically to the actual window's size
    // This functions must be called before starting the scene

    /** @brief Enabled/disable virtual screen */
    void set_virtual_screen(bool is_enabled) { m_is_virtual_screen_enabled = is_enabled; }
    /** @brief Indicate if the rendering of the virtual screen must fit the window */
    void set_virtual_screen_fit(bool fit) { m_virtual_screen_fit = fit; }
    /** @brief Set the size of the virtual screen */
    void set_virtual_screen_size(int width, int height);
    /** @brief Set the background of the virtual screen */
    void set_virtual_screen_bg_color(const SDL_Color& color) { m_virtual_screen_bg_color = color; }

  private:
    /** @brief Fonts database */
    fonts_db& m_fonts;
    /** @brief Window which displays the scene */
    sdl::window m_window;
    /** @brief Renderer for the scene */
    sdl::renderer m_renderer;
    /** @brief Background color */
    SDL_Color m_bg_color;
    /** @brief Indicate if the framerate must be fixed */
    bool m_is_fixed_fps;
    /** @brief Fixed framerate */
    float m_fixed_fps;
    /** @brief Current framerate */
    float m_fps;
    /** @brief Indicate if the current framerate must be displayed */
    bool m_is_fps_display_enabled;
    /** @brief Indicate if the virtual screen is enabled */
    bool m_is_virtual_screen_enabled;
    /** @brief Indicate if the rendering of the virtual screen must fit the window */
    bool m_virtual_screen_fit;
    /** @brief Size of the virtual screen */
    SDL_Rect m_virtual_screen_size;
    /** @brief Background color of the virtual screen */
    SDL_Color m_virtual_screen_bg_color;

    /** @brief Widgets cmopsing the scene */
    std::set<widgets::widget*> m_widgets;
};

} // namespace game

#endif // GAME_SCENE_H
