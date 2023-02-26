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

#include "sprite.h"

namespace widgets
{

/** @brief Constructor */
sprite::sprite(sdl::renderer& renderer)
    : widget(renderer), m_fps(), m_fps_period(), m_next_image_ts(), m_animations(), m_current_anim(nullptr)
{
    set_framerate(30.f);
}

/** @brief Add an animation */
bool sprite::add_animation(int id, const image_list* animation)
{
    bool ret = false;
    if (animation)
    {
        ret = add_animation(id, *animation);
    }
    return ret;
}

/** @brief Add an animation */
bool sprite::add_animation(int id, const image_list& animation)
{
    bool ret = false;

    // Check if the animation exists
    auto iter_anim = m_animations.find(id);
    if (iter_anim == m_animations.end())
    {
        // Copy the image list
        image_list anim;
        for (auto& img : animation)
        {
            auto part = std::make_unique<image>(*img.second);
            anim.emplace_back(img.first, std::move(part));
        }

        // Save animation
        m_animations[id] = std::move(anim);

        // Update rendering
        update_needed();

        ret = true;
    }

    return ret;
}

/** @brief Set the framerate */
void sprite::set_framerate(float fps)
{
    // Save framerate
    m_fps = fps;

    // Compute corresponding period
    float period_us = 1000000.f / m_fps;
    m_fps_period    = std::chrono::microseconds(static_cast<int64_t>(period_us));

    // Next image timestamp
    m_next_image_ts = std::chrono::steady_clock::now() + m_fps_period;
}

/** @brief Set the current animation */
bool sprite::set_animation(int id)
{
    bool ret = false;

    // Check if the animation exists
    auto iter_anim = m_animations.find(id);
    if (iter_anim != m_animations.end())
    {
        // Switch to new animation
        m_current_anim = &iter_anim->second;
        m_current_img  = m_current_anim->begin();

        ret = true;
    }

    return ret;
}

/** @brief Update the texture representing the widget */
void sprite::update_texture()
{
    // For each animation
    for (auto& animation : m_animations)
    {
        // For each image
        for (auto& [id, image] : animation.second)
        {
            // Apply settings
            image->set_background_color(get_background_color());
            image->set_size(get_size());
            image->set_autosize(get_autosize());
            image->set_halign(get_halign());
            image->set_valign(get_valign());
            image->set_adjust(get_adjust());

            // Update texture
            image->update_texture();
        }
    }
}

/** @brief Called to notify that the rendering process starts */
void sprite::on_render()
{
    if (m_current_anim)
    {
        // Check if the image must be updated
        auto now = std::chrono::steady_clock::now();
        if (now >= m_next_image_ts)
        {
            // Switch to next image
            m_current_img++;
            if (m_current_img == m_current_anim->end())
            {
                m_current_img = m_current_anim->begin();
            }

            // Get corresponding texture
            m_texture = m_current_img->second->get_texture();
            if (m_texture)
            {
                SDL_Rect size = m_texture->get_size();
                m_position.w  = size.w;
                m_position.h  = size.h;
            }

            // Next image timestamp
            m_next_image_ts = now + m_fps_period;
        }
    }
}

} // namespace widgets
