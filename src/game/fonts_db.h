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

#ifndef GAME_FONTS_DB_H
#define GAME_FONTS_DB_H

#include <string>
#include <unordered_map>

#include "sdl_font.h"

namespace game
{

/** @brief Font database to avoid reloading the same fonts multiple times */
class fonts_db
{
  public:
    /**
     * @brief Load a font
     * @param file Path to the font file
     * @param ptsize Point size
     * @param name Name for the loaded font
     * @return true if the font has been loaded, false otherwise
     */
    bool load(const std::string& file, int ptsize, const std::string& name);

    /**
     * @brief Unload a font
     * @param name Name of the font
     * @return SDL font object if the font exists, nullptr otherwise
     */
    bool unload(const std::string& name);

    /**
     * @brief Get a font
     * @param name Name of the font
     * @return SDL font object if the font exists, nullptr otherwise
     */
    sdl::font get(const std::string& name);

  private:
    /** @brief Loaded fonts */
    std::unordered_map<std::string, sdl::font> m_fonts;
};

} // namespace game

#endif // GAME_FONTS_DB_H
