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

#include "image.h"

namespace widgets
{

/** @brief Constructor */
image::image(sdl::renderer& renderer) : widget(renderer), m_image(), m_image_size{0, 0, 0, 0}, m_image_ratio(1.f) { }

/** @brief Copy constructor */
image::image(const image& copy)
    : widget(copy.m_renderer), m_image(copy.m_image), m_image_size(copy.m_image_size), m_image_ratio(copy.m_image_ratio)
{
}

/** @brief Copy assignment */
image& image::operator=(const image& copy)
{
    m_image      = copy.m_image;
    m_image_size = copy.m_image_size;
    update_needed();
    return (*this);
}

/** @brief Load the image from a file */
bool image::load(const std::string& file)
{
    bool ret = false;
    m_image  = m_renderer->create_texture(file);
    if (m_image)
    {
        m_image_size  = m_image->get_size();
        m_image_ratio = static_cast<float>(m_image_size.w) / static_cast<float>(m_image_size.h);
        update_needed();
        ret = true;
    }
    return ret;
}

/** @brief Update the texture representing the widget */
void image::update_texture()
{
    // Compute image texture size
    SDL_Rect img_size = m_size;
    if (m_image)
    {
        if (m_is_autosized)
        {
            img_size = m_image_size;
        }
    }
    m_position.w = img_size.w;
    m_position.h = img_size.h;

    // Create image texture
    m_texture = m_renderer->create_texture(SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, img_size.w, img_size.h);
    if (m_texture)
    {
        // Prepare texture for rendering
        m_texture->set_blend_mode(SDL_BLENDMODE_BLEND);
        m_renderer->push_texture(m_texture);

        // Fill background
        m_renderer->set_draw_color(m_bg_color);
        m_renderer->clear();

        // Put the image over
        if (m_image)
        {
            if (m_is_autosized)
            {
                m_renderer->copy(m_image, nullptr, &img_size);
            }
            else
            {
                // Compute the image size
                if (m_adjust == adjust::none)
                {
                    img_size = m_image_size;
                }
                else if (m_adjust == adjust::width)
                {
                    img_size.h = static_cast<int>(static_cast<float>(img_size.w) / m_image_ratio);
                }
                else if (m_adjust == adjust::height)
                {
                    img_size.w = static_cast<int>(static_cast<float>(img_size.h) * m_image_ratio);
                }
                else
                {
                    // adjust::fit
                }

                // Compute the destination position
                SDL_Rect dest = compute_alignment(img_size);
                m_renderer->copy(m_image, nullptr, &dest);
            }
        }

        // Restore renderer state
        m_renderer->pop_texture();
    }
}

} // namespace widgets
