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

#include "fonts_db.h"

namespace game
{

/** @brief Load a font */
bool fonts_db::load(const std::string& file, int ptsize, const std::string& name)
{
    bool ret       = false;
    auto iter_font = m_fonts.find(name);
    if (iter_font == m_fonts.end())
    {
        sdl::font font = sdl::create_font(file, ptsize);
        if (font)
        {
            m_fonts[name] = font;
            ret           = true;
        }
    }
    return ret;
}

/** @brief Unload a font */
bool fonts_db::unload(const std::string& name)
{
    bool ret       = false;
    auto iter_font = m_fonts.find(name);
    if (iter_font != m_fonts.end())
    {
        m_fonts.erase(iter_font);
        ret = true;
    }
    return ret;
}

/** @brief Get a font */
sdl::font fonts_db::get(const std::string& name)
{
    sdl::font font;
    auto      iter_font = m_fonts.find(name);
    if (iter_font != m_fonts.end())
    {
        font = iter_font->second;
    }
    return font;
}

} // namespace game
