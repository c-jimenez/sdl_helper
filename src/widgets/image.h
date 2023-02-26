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

#ifndef GAME_IMAGE_H
#define GAME_IMAGE_H

#include <string>

#include "widget.h"

namespace widgets
{

/** @brief Image widget */
class image : public widget
{
  public:
    /** @brief Constructor */
    image(sdl::renderer& renderer);
    /** @brief Destructor */
    virtual ~image() = default;

    /** @brief Copy constructor */
    image(const image& copy);
    /** @brief Copy assignment */
    image& operator=(const image& copy);

    /** @brief Load the image from a file */
    bool load(const std::string& file);

    /** @brief Update the texture representing the widget */
    void update_texture() override;

  private:
    /** @brief Texture representing the untouched image */
    sdl::texture m_image;
    /** @brief Size of the untouched image */
    SDL_Rect m_image_size;
    /** @brief Ratio of the untouched image */
    float m_image_ratio;
};

} // namespace widgets

#endif // GAME_IMAGE_H
