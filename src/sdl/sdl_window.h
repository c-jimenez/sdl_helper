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

#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include <SDL2/SDL.h>
#include <memory>
#include <string>

#include "sdl_renderer.h"
#include "sdl_surface.h"

namespace sdl
{

// Forward declarations
class sdl_window;

/** @brief SDL window */
using window = std::shared_ptr<sdl_window>;

/**
 * @brief Create a window
 * @param title Title
 * @param x X position
 * @param y Y position
 * @param w Width
 * @param h Height
 * @param flags Creation flags
 * @return SDL window object if the creation was successfull, nullptr otherwise
 */
window create_window(const std::string& title, int x, int y, int w, int h, Uint32 flags);

/** @brief Wrapper for SDL window */
class sdl_window
{
  public:
    /**
     * @brief Create a window
     * @param title Title
     * @param x X position
     * @param y Y position
     * @param w Width
     * @param h Height
     * @param flags Creation flags
     * @return SDL window object if the creation was successfull, nullptr otherwise
     */
    static window create(const std::string& title, int x, int y, int w, int h, Uint32 flags);

    /** @brief Destructor */
    ~sdl_window();

    /**
     * @brief Create a renderer associated to the window
     * @param index Driver index (set to -1 for automatic selection)
     * @param flags Creation flags (set to 0 for automatic selection)
     * @return SDL renderer object if the creation was successfull, nullptr otherwise
     */
    renderer create_renderer(int index = -1, Uint32 flags = 0);

    /** @brief Get the title of the window */
    const char* get_title() const;
    /** @brief Set the title of the window */
    void set_title(const std::string& title);

    /** @brief Set the icon of the window */
    void set_icon(surface& icon);

    /** @brief Get the position of the window */
    void get_position(int& x, int& y) const;
    /** @brief Set the position of the window */
    void set_position(int x, int y);

    /** @brief Get the size of the window */
    void get_size(int& w, int& h) const;
    /** @brief Set the size of the window */
    void set_size(int w, int h);

    /** @brief Minimize the window */
    void minimize();
    /** @brief Maximize the window */
    void maximize();
    /** @brief Restore the window */
    void restore();
    /** @brief Hide the window */
    void hide();
    /** @brief Show the window */
    void show();
    /** @brief Raise the window */
    void raise();
    /** @brief Set the window fullscreen */
    bool set_fullscreen(Uint32 flags);

    /** @brief Get the surface associated with the window */
    surface get_surface() const;
    /** @brief Update the window with its associated surface */
    bool update();

  private:
    /** @brief SDL handle */
    SDL_Window* m_handle;

    /** 
     * @brief Constructor 
     * @param handle SDL handle
     */
    sdl_window(SDL_Window* handle);
};

} // namespace sdl

#endif // SDL_WINDOW_H
