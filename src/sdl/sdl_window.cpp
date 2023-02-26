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

#include "sdl_window.h"

namespace sdl
{
/** @brief Create a window */
window create_window(const std::string& title, int x, int y, int w, int h, Uint32 flags)
{
    return sdl_window::create(title, x, y, w, h, flags);
}

/** @brief Create a window */
window sdl_window::create(const std::string& title, int x, int y, int w, int h, Uint32 flags)
{
    window      instance;
    SDL_Window* handle = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
    if (handle)
    {
        auto p = new sdl_window(handle);
        instance.reset(p);
    }
    return instance;
}

/** @brief Destructor */
sdl_window::~sdl_window()
{
    SDL_DestroyWindow(m_handle);
}

/** @brief Constructor */
sdl_window::sdl_window(SDL_Window* handle) : m_handle(handle) { }

/** @brief Create a renderer associated to the window */
renderer sdl_window::create_renderer(int index, Uint32 flags)
{
    renderer      instance;
    SDL_Renderer* renderer = SDL_CreateRenderer(m_handle, index, flags);
    if (renderer)
    {
        auto p = new sdl_renderer(renderer);
        instance.reset(p);
    }
    return instance;
}

/** @brief Get the title of the window */
const char* sdl_window::get_title() const
{
    return SDL_GetWindowTitle(m_handle);
}

/** @brief Set the title of the window */
void sdl_window::set_title(const std::string& title)
{
    SDL_SetWindowTitle(m_handle, title.c_str());
}

/** @brief Set the icon of the window */
void sdl_window::set_icon(surface& icon)
{
    SDL_SetWindowIcon(m_handle, icon->m_handle);
}

/** @brief Get the position of the window */
void sdl_window::get_position(int& x, int& y) const
{
    SDL_GetWindowPosition(m_handle, &x, &y);
}

/** @brief Set the position of the window */
void sdl_window::set_position(int x, int y)
{
    SDL_SetWindowPosition(m_handle, x, y);
}

/** @brief Get the size of the window */
void sdl_window::get_size(int& w, int& h) const
{
    SDL_GetWindowSize(m_handle, &w, &h);
}

/** @brief Set the size of the window */
void sdl_window::set_size(int w, int h)
{
    SDL_SetWindowSize(m_handle, w, h);
}

/** @brief Minimize the window */
void sdl_window::minimize()
{
    SDL_MinimizeWindow(m_handle);
}

/** @brief Maximize the window */
void sdl_window::maximize()
{
    SDL_MaximizeWindow(m_handle);
}

/** @brief Restore the window */
void sdl_window::restore()
{
    SDL_RestoreWindow(m_handle);
}

/** @brief Hide the window */
void sdl_window::hide()
{
    SDL_HideWindow(m_handle);
}

/** @brief Show the window */
void sdl_window::show()
{
    SDL_ShowWindow(m_handle);
}

/** @brief Raise the window */
void sdl_window::raise()
{
    SDL_RaiseWindow(m_handle);
}

/** @brief Set the window fullscreen */
bool sdl_window::set_fullscreen(Uint32 flags)
{
    return (SDL_SetWindowFullscreen(m_handle, flags) == 0);
}

/** @brief Get the surface associated with the window */
surface sdl_window::get_surface() const
{
    surface      instance;
    SDL_Surface* surface = SDL_GetWindowSurface(m_handle);
    if (surface)
    {
        auto p = new sdl_surface(surface, false);
        instance.reset(p);
    }
    return instance;
}

/** @brief Update the window with its associated surface */
bool sdl_window::update()
{
    return (SDL_UpdateWindowSurface(m_handle) == 0);
}

} // namespace sdl
