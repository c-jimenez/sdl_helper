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

#include "transform.h"
#include "widget.h"

namespace widgets
{

/** @brief Constructor */
transform::transform(widget& w) : m_widget(w), m_scaling(1.f), m_rot_angle(0.), m_rot_center(), m_flip()
{
    reset();
}

/** @brief Copy assignment */
transform& transform::operator=(const transform& copy)
{
    m_scaling    = copy.m_scaling;
    m_rot_angle  = copy.m_rot_angle;
    m_rot_center = copy.m_rot_center;
    if (copy.m_rot_center_ptr)
    {
        m_rot_center_ptr = &m_rot_center;
    }
    m_flip = copy.m_flip;
    return *this;
}

/** @brief Reset the transformation back to identity transform */
void transform::reset()
{
    m_scaling        = 1.f;
    m_rot_angle      = 0.;
    m_rot_center_ptr = nullptr;
    m_flip           = SDL_FLIP_NONE;
}

/** @brief Set the center of rotation */
void transform::set_rot_center(const SDL_Point* rot_center)
{
    if (rot_center)
    {
        m_rot_center     = *rot_center;
        m_rot_center_ptr = &m_rot_center;
    }
    else
    {
        m_rot_center_ptr = nullptr;
    }
}

/** @brief Apply the transformation */
bool transform::apply(sdl::renderer& renderer)
{
    bool ret = false;

    // Compute new size
    SDL_Rect size = m_widget.get_size_position();
    size.w        = static_cast<int>(static_cast<float>(size.w) * m_scaling);
    size.h        = static_cast<int>(static_cast<float>(size.h) * m_scaling);

    // Render widget
    ret = renderer->copy(m_widget.get_texture(), nullptr, &size, m_rot_angle, m_rot_center_ptr, m_flip);

    return ret;
}

} // namespace widgets
