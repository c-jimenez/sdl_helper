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

#ifndef GAME_ANIMATIONS_DB_H
#define GAME_ANIMATIONS_DB_H

#include <regex>
#include <string>
#include <unordered_map>

#include "sprite.h"

namespace game
{

/** @brief Sprite animations database to avoid reloading the same images multiple times */
class sprites_db
{
  public:
    /** @brief Constructor */
    sprites_db(sdl::renderer& renderer);

    /** 
     * @brief Load an animation from a path 
     * @param name Name of the animation
     * @param path Path where the images composing the animation are stored
     * @param base_name Base name for the image
     * @return true if the animation has been loaded, false otherwise
     */
    bool load_animation(const std::string& name, const std::string& path, const std::string& base_name);

    /** 
     * @brief Load an animation from a path 
     * @param name Name of the animation
     * @param path Path where the images composing the animation are stored
     * @param filter Regex filter to extract the image number
     * @param capture_group Id of the capture group of the regex containing the image number
     * @return true if the animation has been loaded, false otherwise
     */
    bool load_animation(const std::string& name, const std::string& path, const std::regex& filter, unsigned int capture_group = 0);

    /**
     * @brief Get an animation
     * @param name Name of the animation
     * @return Animation if it exists, nullptr otherwise
     */
    const widgets::image_list* get(const std::string& name);

  private:
    /** @brief Renderer to use to load the images */
    sdl::renderer& m_renderer;
    /** @brief Loaded animations */
    std::unordered_map<std::string, widgets::image_list> m_animations;
};

} // namespace game

#endif // GAME_ANIMATIONS_DB_H
