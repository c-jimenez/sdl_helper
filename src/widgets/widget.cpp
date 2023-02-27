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

#include "widget.h"

namespace widgets
{

/** @brief Constructor */
widget::widget(sdl::renderer& renderer)
    : m_renderer(renderer),
      m_animation(),
      m_transform(),
      m_draw_boundary_box(false),
      m_bg_color{0, 0, 0, 0},
      m_is_autosized(true),
      m_size{0, 0, 0, 0},
      m_position{0, 0, 0, 0},
      m_halign(halign::center),
      m_valign(valign::center),
      m_adjust(adjust::fit),
      m_texture(),
      m_is_update_needed(true)
{
}

/** @brief Set the background color */
void widget::set_background_color(const SDL_Color& color)
{
    m_bg_color = color;
    update_needed();
}

/** @brief Set the position */
void widget::set_position(const SDL_Point& pos)
{
    m_position.x = pos.x;
    m_position.y = pos.y;
}

/** @brief Set the size */
void widget::set_size(const SDL_Rect& size)
{
    m_size = size;
    update_needed();
}
/** @brief Set the size and position */
void widget::set_size_position(const SDL_Rect& size_position)
{
    m_position = size_position;
    m_size.w   = size_position.w;
    m_size.h   = size_position.h;
    update_needed();
}

/** @brief Set the auto size capability */
void widget::set_autosize(bool is_autosized)
{
    m_is_autosized = is_autosized;
    update_needed();
}

/** @brief Set the horizontal alignment of the text of the widget */
void widget::set_halign(halign align)
{
    m_halign = align;
    update_needed();
}

/** @brief Set the vertical alignment of the text of the widget */
void widget::set_valign(valign align)
{
    m_valign = align;
    update_needed();
}

/** @brief Set the adjustment of the contents */
void widget::set_adjust(adjust adj)
{
    m_adjust = adj;
    update_needed();
}

/** @brief Render the widget */
void widget::render()
{
    // Notify widget that rendering process starts
    on_render();

    // Check if the texture must be updated
    if (m_is_update_needed)
    {
        // Widget specific implementation
        update_texture();
        m_is_update_needed = false;
    }

    // Render widget's texture
    if (m_texture)
    {
        // Draw boundary box
        if (m_draw_boundary_box)
        {
            m_renderer->set_draw_color(SDL_Color{0, 255, 0, 255});
            m_renderer->push_texture(m_texture);
            m_renderer->draw_rect(m_texture->get_size());
            m_renderer->pop_texture();
        }

        // Render with transformation
        m_animation.apply(*this);
        m_transform.apply(m_renderer, *this);
    }
}

/** @brief Indicate that the widget texture must be updated for next rendering */
void widget::update_needed()
{
    // Texture must be updated
    m_is_update_needed = true;
}

/** @brief Compute the position of a content based on its alignment */
SDL_Rect widget::compute_alignment(const SDL_Rect& content_size)
{
    SDL_Rect position = content_size;

    if (m_halign == halign::left)
    {
        position.x = 0;
    }
    else if (m_halign == halign::right)
    {
        position.x = m_size.w - content_size.w;
    }
    else
    {
        position.x = (m_size.w - content_size.w) / 2;
    }
    if (m_valign == valign::top)
    {
        position.y = 0;
    }
    else if (m_valign == valign::bottom)
    {
        position.y = m_size.h - content_size.h;
    }
    else
    {
        position.y = (m_size.h - content_size.h) / 2;
    }

    return position;
}

} // namespace widgets
