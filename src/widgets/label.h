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

#ifndef GAME_LABEL_H
#define GAME_LABEL_H

#include <string>

#include "sdl_font.h"
#include "widget.h"

namespace widgets
{

/** @brief Label widget to display text */
class label : public widget
{
  public:
    /** @brief Constructor */
    label(sdl::renderer& renderer);
    /** @brief Destructor */
    virtual ~label() = default;

    /** @brief Copy constructor => deleted */
    label(const label& copy) = delete;
    /** @brief Copy assignment => deleted */
    label& operator=(const label& copy) = delete;

    /** @brief Set the text to display */
    void set_text(const std::string& text);
    /** @brief Get the displayed text */
    const std::string& get_text() const { return m_text; }

    /** @brief Set the font to use */
    void set_font(const sdl::font& font);
    /** @brief Get the font to use */
    sdl::font get_font() const { return m_font; }

    /** @brief Set the text color */
    void set_text_color(const SDL_Color& color);
    /** @brief Get the text color */
    SDL_Color get_text_color() const { return m_text_color; }

    /** @brief Update the texture representing the widget */
    void update_texture() override;

  private:
    /** @brief Text to display */
    std::string m_text;
    /** @brief Font to use */
    sdl::font m_font;
    /** @brief Text color */
    SDL_Color m_text_color;
};

} // namespace widgets

#endif // GAME_LABEL_H
