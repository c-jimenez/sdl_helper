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

#ifndef SDL_FONT_H
#define SDL_FONT_H

#include <SDL2/SDL_ttf.h>
#include <memory>
#include <string>

#include "sdl_surface.h"

namespace sdl
{

// Forward declarations
class sdl_font;

/** @brief SDL font */
using font = std::shared_ptr<sdl_font>;

/**
 * @brief Create a font
 * @param file Path to the font file
 * @param ptsize Point size
 * @return SDL font object if the creation was successfull, nullptr otherwise
 */
font create_font(const std::string& file, int ptsize);

/** @brief Wrapper for SDL font */
class sdl_font
{
  public:
    /**
     * @brief Create a font
     * @param file Path to the font file
     * @param ptsize Point size
     * @return SDL font object if the creation was successfull, nullptr otherwise
     */
    static font create_font(const std::string& file, int ptsize);

    /** @brief Destructor */
    ~sdl_font();

    /**
     * @brief Create a surface with a text written with the font
     * @param text Text to write
     * @param fg_color Text color
     * @return SDL surface object if the rendering was successfull, nullptr otherwise
     */
    surface render_solid(const std::string& text, const SDL_Color& fg_color) const;

    /**
     * @brief Create a surface with a text written with the font
     * @param text Text to write
     * @param fg_color Text color
     * @param bg_color Text background color
     * @return SDL surface object if the rendering was successfull, nullptr otherwise
     */
    surface render_shaded(const std::string& text, const SDL_Color& fg_color, const SDL_Color& bg_color) const;

    /**
     * @brief Create a surface with a text written with the font
     * @param text Text to write
     * @param fg_color Text color
     * @return SDL surface object if the rendering was successfull, nullptr otherwise
     */
    surface render_blended(const std::string& text, const SDL_Color& fg_color) const;

    /**
     * @brief Create a surface with a text written with the font with wrapping
     * @param text Text to write
     * @param fg_color Text color
     * @param wrap_length Length in pixel before wrapping
     * @return SDL surface object if the rendering was successfull, nullptr otherwise
     */
    surface render_blended_wrapped(const std::string& text, const SDL_Color& fg_color, Uint32 wrap_length) const;

  private:
    /** @brief SDL handle */
    TTF_Font* m_handle;

    /** 
     * @brief Constructor 
     * @param handle SDL handle
     */
    sdl_font(TTF_Font* handle);
};

} // namespace sdl

#endif // SDL_FONT_H
