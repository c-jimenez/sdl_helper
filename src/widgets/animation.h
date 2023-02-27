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

#ifndef GAME_ANIMATION_H
#define GAME_ANIMATION_H

#include <chrono>
#include <optional>

#include "transform.h"

namespace widgets
{

/** @brief Class to handle an animation on a graphical widget */
class animation
{
  public:
    // Forward declarations
    struct step;

    /** @brief Constructor */
    animation();
    /** @brief Constructor */
    animation(bool loop, std::vector<step>&& steps);
    /** @brief Destructor */
    virtual ~animation() = default;

    /** @brief Copy constructor */
    animation(const animation& copy);
    /** @brief Copy assignment */
    animation& operator=(const animation& copy);

    /** @brief Move constructor */
    animation(animation&& move) noexcept;
    /** @brief Move assignment */
    animation& operator=(animation&& move) noexcept;

    /** @brief Start the animation */
    bool start();
    /** @brief Stop the animation */
    bool stop();
    /** @brief Reset the animation to its first step */
    void reset();

    /** @brief Apply the animation */
    void apply(widget& w);

    /** @brief Indicate if the animation is done */
    bool is_done() const { return (m_current_step == m_steps.cend()); }

    /** @brief Step of an animation */
    struct step
    {
        /** @brief Scaling */
        std::optional<float> scaling;
        /** @brief Rotation angle in degrees */
        std::optional<double> rot_angle;
        /** @brief Flip */
        std::optional<SDL_RendererFlip> flip;
        /** @brief Duration */
        std::chrono::nanoseconds duration;
    };

    /** @brief Initialize a scaling only step */
    static step scaling_step(float scaling, const std::chrono::milliseconds& duration)
    {
        return {scaling, std::optional<double>(), std::optional<SDL_RendererFlip>(), duration};
    }
    /** @brief Initialize a rotation only step */
    static step rotation_step(double rot_angle, const std::chrono::milliseconds& duration)
    {
        return {std::optional<float>(), rot_angle, std::optional<SDL_RendererFlip>(), duration};
    }
    /** @brief Initialize a flip only step */
    static step flip_step(SDL_RendererFlip flip, const std::chrono::milliseconds& duration)
    {
        return {std::optional<float>(), std::optional<double>(), flip, duration};
    }

  private:
    /** @brief Animation steps */
    std::vector<step> m_steps;
    /** @brief Current transform */
    transform m_current_transform;
    /** @brief Indicate if the animation must loop forever */
    bool m_loop;
    /** @brief Indicate if the animation is started */
    bool m_is_started;
    /** @brief Indicate a restart of the animation */
    bool m_restart;

    /** @brief Current step */
    std::vector<step>::const_iterator m_current_step;
    /** @brief Timestamp of the start of the step */
    std::chrono::steady_clock::time_point m_start_step_ts;
    /** @brief Timestamp of the next step */
    std::chrono::steady_clock::time_point m_next_step_ts;
};

} // namespace widgets

#endif // GAME_ANIMATION_H
