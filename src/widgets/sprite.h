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

#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include <chrono>
#include <list>
#include <unordered_map>

#include "image.h"

namespace widgets
{

/** @brief Image composing an animation */
using image_anim = std::pair<unsigned int, std::unique_ptr<image>>;
/** @brief List of images composing an animation */
using image_list = std::list<image_anim>;

/** @brief Sprite widget to display animated images */
class sprite : public widget
{
  public:
    /** @brief Constructor */
    sprite(sdl::renderer& renderer);
    /** @brief Destructor */
    virtual ~sprite() = default;

    /** @brief Copy constructor => deleted */
    sprite(const sprite& copy) = delete;
    /** @brief Copy assignment => deleted */
    sprite& operator=(const sprite& copy) = delete;

    /** @brief Add an animation */
    bool add_animation(int id, const image_list* animation);
    /** @brief Add an animation */
    bool add_animation(int id, const image_list& animation);

    /** @brief Set the current animation */
    bool set_animation(int id);

    /** @brief Set the framerate */
    void set_framerate(float fps);
    /** @brief Get the framerate */
    float get_framerate() const { return m_fps; }

    /** @brief Update the texture representing the widget */
    void update_texture() override;

  protected:
    /** @brief Called to notify that the rendering process starts */
    void on_render() override;

  private:
    /** @brief Framerate */
    float m_fps;
    /** @brief Framerate period in µs */
    std::chrono::microseconds m_fps_period;
    /** @brief Timestamp of the next image */
    std::chrono::steady_clock::time_point m_next_image_ts;
    /** @brief Animations */
    std::unordered_map<int, image_list> m_animations;
    /** @brief Current animation */
    image_list* m_current_anim;
    /** @brief Current image in the current animation */
    image_list::iterator m_current_img;
};

} // namespace widgets

#endif // GAME_SPRITE_H
