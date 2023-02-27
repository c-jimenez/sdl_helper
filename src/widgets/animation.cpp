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

#include "animation.h"
#include "widget.h"

#include <cmath>

namespace widgets
{

/** @brief Constructor */
animation::animation()
    : m_steps(),
      m_current_transform(),
      m_loop(false),
      m_is_started(false),
      m_current_step(m_steps.cend()),
      m_start_step_ts(),
      m_next_step_ts()
{
    reset();
}

/** @brief Constructor */
animation::animation(bool loop, std::vector<step>&& steps)
    : m_steps(steps),
      m_current_transform(),
      m_loop(loop),
      m_is_started(false),
      m_restart(false),
      m_current_step(m_steps.cend()),
      m_start_step_ts(),
      m_next_step_ts()
{
    reset();
}

/** @brief Copy constructor */
animation::animation(const animation& copy)
    : m_steps(copy.m_steps),
      m_current_transform(),
      m_loop(copy.m_loop),
      m_is_started(false),
      m_restart(false),
      m_current_step(m_steps.cend()),
      m_start_step_ts(),
      m_next_step_ts()
{
    reset();
}

/** @brief Copy assignment */
animation& animation::operator=(const animation& copy)
{
    m_is_started = false;
    m_restart    = false;
    m_loop       = copy.m_loop;
    m_steps      = copy.m_steps;
    reset();
    return (*this);
}

/** @brief Move constructor */
animation::animation(animation&& move) noexcept
    : m_steps(std::move(move.m_steps)),
      m_current_transform(),
      m_loop(move.m_loop),
      m_is_started(false),
      m_restart(false),
      m_current_step(m_steps.cend()),
      m_start_step_ts(),
      m_next_step_ts()
{
    reset();
    move.m_is_started = false;
    move.reset();
}

/** @brief Move assignment */
animation& animation::operator = (animation && move) noexcept
{
    m_is_started = false;
    m_restart    = false;
    m_loop       = move.m_loop;
    m_steps      = std::move(move.m_steps);
    reset();
    move.m_is_started = false;
    move.reset();
    return (*this);
}

/** @brief Start the animation */
bool animation::start()
{
    bool ret = false;

    // Check if the animation is started
    if (!m_is_started)
    {
        // Check if there are steps left
        if (!is_done())
        {
            // Compute start and next step timestamps
            m_start_step_ts = std::chrono::steady_clock::now();
            m_next_step_ts  = m_start_step_ts + m_current_step->duration;

            m_is_started = true;
            m_restart    = true;
        }

        ret = true;
    }

    return ret;
}

/** @brief Stop the animation */
bool animation::stop()
{
    bool ret = false;

    // Check if the animation is started
    if (m_is_started)
    {
        // Stop the animation
        m_is_started = false;
    }

    return ret;
}
/** @brief Reset the animation to its first step */
void animation::reset()
{
    // Reset animation to first step
    m_current_step = m_steps.begin();
}

/** @brief Apply the animation */
void animation::apply(widget& w)
{
    // Check if the animation is started
    if (m_is_started)
    {
        // Save initial transform state
        if (m_restart)
        {
            m_current_transform = w.get_transform();
            m_restart           = false;
        }

        // Check the end of current step
        auto now = std::chrono::steady_clock::now();
        if (now >= m_next_step_ts)
        {
            // Apply the targeted transformation to avoid rounding issues
            transform& widget_transform = w.get_transform();
            if (m_current_step->scaling.has_value())
            {
                widget_transform.set_scaling(m_current_step->scaling.value());
            }
            if (m_current_step->rot_angle.has_value())
            {
                widget_transform.set_rot_angle(m_current_step->rot_angle.value());
            }

            // Go to next step
            m_current_step++;

            // Check end of animation
            if (is_done())
            {
                // Check if the animation must be restarted
                if (m_loop)
                {
                    reset();
                }
                else
                {
                    m_is_started = false;
                }
            }

            // Initialize step
            if (!is_done())
            {
                // Compute timestamps
                m_start_step_ts = now;
                m_next_step_ts  = now + m_current_step->duration;

                // Save initial transform state for dynamic transformations
                m_current_transform = w.get_transform();

                // Apply static transformations
                if (m_current_step->flip.has_value())
                {
                    w.get_transform().set_flip(m_current_step->flip.value());
                }
            }
        }
        if (!is_done())
        {
            // Compute progression ratio
            auto  diff     = now - m_start_step_ts;
            float progress = static_cast<float>(diff.count()) / static_cast<float>(m_current_step->duration.count());

            // Apply dynamic transformations
            transform& widget_transform = w.get_transform();
            if (m_current_step->scaling.has_value())
            {
                float current_scaling = m_current_transform.get_scaling();
                widget_transform.set_scaling(current_scaling + progress * (m_current_step->scaling.value() - current_scaling));
            }
            if (m_current_step->rot_angle.has_value())
            {
                double current_rot_angle = m_current_transform.get_rot_angle();
                widget_transform.set_rot_angle(current_rot_angle +
                                               static_cast<double>(progress) * (m_current_step->rot_angle.value() - current_rot_angle));
            }
        }
    }
}

} // namespace widgets
