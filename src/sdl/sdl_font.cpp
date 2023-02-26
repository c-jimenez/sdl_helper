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

#include "sdl_font.h"

namespace sdl
{

/** @brief Create a font */
font create_font(const std::string& file, int ptsize)
{
    return sdl_font::create_font(file, ptsize);
}

/** @brief Create a font */
font sdl_font::create_font(const std::string& file, int ptsize)
{
    font      instance;
    TTF_Font* font = TTF_OpenFont(file.c_str(), ptsize);
    if (font)
    {
        auto p = new sdl_font(font);
        instance.reset(p);
    }
    return instance;
}

/** @brief Destructor */
sdl_font::~sdl_font()
{
    TTF_CloseFont(m_handle);
}

/** @brief Constructor */
sdl_font::sdl_font(TTF_Font* handle) : m_handle(handle) { }

/** @brief Create a surface with a text written with the font */
surface sdl_font::render_solid(const std::string& text, const SDL_Color& fg_color) const
{
    surface      instance;
    SDL_Surface* surface = TTF_RenderUTF8_Solid(m_handle, text.c_str(), fg_color);
    if (surface)
    {
        auto p = new sdl_surface(surface);
        instance.reset(p);
    }
    return instance;
}

/** @brief Create a surface with a text written with the font */
surface sdl_font::render_shaded(const std::string& text, const SDL_Color& fg_color, const SDL_Color& bg_color) const
{
    surface      instance;
    SDL_Surface* surface = TTF_RenderUTF8_Shaded(m_handle, text.c_str(), fg_color, bg_color);
    if (surface)
    {
        auto p = new sdl_surface(surface);
        instance.reset(p);
    }
    return instance;
}

/** @brief Create a surface with a text written with the font */
surface sdl_font::render_blended(const std::string& text, const SDL_Color& fg_color) const
{
    surface      instance;
    SDL_Surface* surface = TTF_RenderUTF8_Blended(m_handle, text.c_str(), fg_color);
    if (surface)
    {
        auto p = new sdl_surface(surface);
        instance.reset(p);
    }
    return instance;
}

/** @brief Create a surface with a text written with the font  with wrapping */
surface sdl_font::render_blended_wrapped(const std::string& text, const SDL_Color& fg_color, Uint32 wrap_length) const
{
    surface      instance;
    SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(m_handle, text.c_str(), fg_color, wrap_length);
    if (surface)
    {
        auto p = new sdl_surface(surface);
        instance.reset(p);
    }
    return instance;
}

} // namespace sdl
