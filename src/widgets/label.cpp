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

#include "label.h"

namespace widgets
{

/** @brief Constructor */
label::label(sdl::renderer& renderer) : widget(renderer), m_text(), m_font(), m_text_color{255, 255, 255, 0} { }

/** @brief Set the text to display */
void label::set_text(const std::string& text)
{
    m_text = text;
    update_needed();
}

/** @brief Set the font to use */
void label::set_font(const sdl::font& font)
{
    m_font = font;
    update_needed();
}

/** @brief Set the text color */
void label::set_text_color(const SDL_Color& color)
{
    m_text_color = color;
    update_needed();
}

/** @brief Update the texture representing the widget */
void label::update_texture()
{
    // Render text to a texture
    sdl::texture text_texture;
    if (m_font)
    {
        auto text_surface = m_font->render_blended(m_text, m_text_color);
        if (text_surface)
        {
            if (m_is_autosized)
            {
                m_size = text_surface->get_size();
            }
            text_texture = m_renderer->create_texture(text_surface);
        }
    }
    m_position.w = m_size.w;
    m_position.h = m_size.h;

    // Create label texture
    m_texture = m_renderer->create_texture(SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, m_size.w, m_size.h);
    if (m_texture)
    {
        // Prepare texture for rendering
        m_texture->set_blend_mode(SDL_BLENDMODE_BLEND);
        m_renderer->push_texture(m_texture);

        // Fill background
        m_renderer->set_draw_color(m_bg_color);
        m_renderer->clear();

        // Put the text texture over
        if (text_texture)
        {
            SDL_Rect dest = text_texture->get_size();
            if (!m_is_autosized)
            {
                // Compute the destination position based on alignment
                dest = compute_alignment(dest);
            }
            m_renderer->copy(text_texture, nullptr, &dest);
        }

        // Restore renderer state
        m_renderer->pop_texture();
    }
}

} // namespace widgets
