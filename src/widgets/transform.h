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

#ifndef GAME_TRANSFORM_H
#define GAME_TRANSFORM_H

#include "sdl_renderer.h"

namespace widgets
{

// Forward declarations
class widget;

/** @brief Class for the geometrical tranformations on graphical widgets */
class transform
{
  public:
    /** @brief Constructor */
    transform(widget& w);
    /** @brief Destructor */
    virtual ~transform() = default;

    /** @brief Copy constructor => deleted */
    transform(const transform& copy) = delete;
    /** @brief Copy assignment */
    transform& operator=(const transform& copy);

    /** @brief Reset the transformation back to identity transform */
    void reset();

    /** @brief Set the scaling */
    void set_scaling(float scaling) { m_scaling = scaling; }
    /** @brief Get the scaling */
    float get_scaling() const { return m_scaling; }

    /** @brief Set the rotation angle */
    void set_rot_angle(double rot_angle) { m_rot_angle = rot_angle; }
    /** @brief Get the rotation angle */
    double get_rot_angle() const { return m_rot_angle; }

    /** @brief Set the center of rotation */
    void set_rot_center(const SDL_Point* rot_center);
    /** @brief Get the center of rotation */
    SDL_Point* set_rot_center() const { return m_rot_center_ptr; }

    /** @brief Set the flip */
    void set_flip(SDL_RendererFlip flip) { m_flip = flip; }
    /** @brief Get the flip */
    SDL_RendererFlip get_flip() const { return m_flip; }

    /** @brief Apply the transformation */
    bool apply(sdl::renderer& renderer);

  private:
    /** @brief Associated widget */
    widget& m_widget;
    /** @brief Scaling */
    float m_scaling;
    /** @brief Rotation angle in degrees */
    double m_rot_angle;
    /** @brief Rotation center */
    SDL_Point m_rot_center;
    /** @brief Pointer to rotation center */
    SDL_Point* m_rot_center_ptr;
    /** @brief Flip */
    SDL_RendererFlip m_flip;
};

} // namespace widgets

#endif // GAME_TRANSFORM_H
