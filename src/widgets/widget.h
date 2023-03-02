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

#ifndef GAME_WIDGET_H
#define GAME_WIDGET_H

#include "animation.h"
#include "sdl_renderer.h"
#include "transform.h"

namespace widgets
{

/** @brief Base class for the graphical Widgets to display */
class widget
{
  public:
    /** @brief Horizontal alignment */
    enum class halign
    {
        left,
        center,
        right
    };

    /** @brief Vertical alignment */
    enum class valign
    {
        top,
        center,
        bottom
    };

    /** @brief Adjust mode */
    enum class adjust
    {
        none,
        fit,
        width,
        height
    };

    /** @brief Constructor */
    widget(sdl::renderer& renderer);
    /** @brief Destructor */
    virtual ~widget() = default;

    /** @brief Copy constructor => deleted */
    widget(const widget& copy) = delete;
    /** @brief Copy assignment => deleted */
    widget& operator=(const widget& copy) = delete;

    /** @brief Set the visibility of the widget */
    void set_visible(bool is_visible) { m_is_visible = is_visible; }
    /** @brief Get the visibility of the widget */
    bool is_visible() const { return m_is_visible; }

    /** @brief Get the animation applied to the widget */
    animation& get_animation() { return m_animation; }
    /** @brief Get the animation applied to the widget */
    const animation& get_animation() const { return m_animation; }

    /** @brief Get the geometrical transformation applied to the widget */
    transform& get_transform() { return m_transform; }
    /** @brief Get the geometrical transformation applied to the widget */
    const transform& get_transform() const { return m_transform; }

    /** @brief Enable/disable the display of the boundary box */
    void set_boundary_box(bool is_enabled) { m_draw_boundary_box = is_enabled; }

    /** @brief Set the background color */
    void set_background_color(const SDL_Color& color);
    /** @brief Get the background color */
    SDL_Color get_background_color() const { return m_bg_color; }

    /** @brief Set the position */
    void set_position(const SDL_Point& pos);
    /** @brief Get the position */
    SDL_Point get_position() const { return SDL_Point{m_position.x, m_position.y}; }

    /** @brief Set the size */
    void set_size(const SDL_Rect& size);
    /** @brief Get the size */
    SDL_Rect get_size() const { return m_size; }

    /** @brief Set the size and position */
    void set_size_position(const SDL_Rect& size_position);
    /** @brief Get the size and position */
    SDL_Rect get_size_position() const { return m_position; }

    /** @brief Set the auto size capability */
    void set_autosize(bool is_autosized);
    /** @brief Get the auto size capability */
    bool get_autosize() const { return m_is_autosized; }

    /** @brief Set the horizontal alignment of the contents */
    void set_halign(halign align);
    /** @brief Get the horizontal alignment of the contents */
    halign get_halign() const { return m_halign; }

    /** @brief Set the vertical alignment of the contents */
    void set_valign(valign align);
    /** @brief Get the vertical alignment of the contents */
    valign get_valign() const { return m_valign; }

    /** @brief Set the adjustment of the contents */
    void set_adjust(adjust adj);
    /** @brief Get the adjustment of the contents */
    adjust get_adjust() const { return m_adjust; }

    /** @brief Render the widget */
    void render();
    /** @brief Indicate that the widget texture must be updated for next rendering */
    void update_needed();

    /** @brief Update the texture representing the widget */
    virtual void update_texture() = 0;
    /** @brief Get the texture representing the widget */
    sdl::texture& get_texture() { return m_texture; }

  protected:
    /** @brief Renderer of the widget */
    sdl::renderer& m_renderer;
    /** @brief Visibility of the widget */
    bool m_is_visible;
    /** @brief Animation */
    animation m_animation;
    /** @brief Transformation */
    transform m_transform;
    /** @brief Indicate if a boundary box must be displayed around the widget */
    bool m_draw_boundary_box;
    /** @brief Background color */
    SDL_Color m_bg_color;
    /** @brief Indicate if the size of the widget is dynamic */
    bool m_is_autosized;
    /** @brief Size of the widget */
    SDL_Rect m_size;
    /** @brief Position of the widget */
    SDL_Rect m_position;
    /** @brief Horizontal alignment of the contents of the widget */
    halign m_halign;
    /** @brief Vertical alignment of the contents of the widget */
    valign m_valign;
    /** @brief Adjustment of the contents */
    adjust m_adjust;
    /** @brief Texture representing the widget */
    sdl::texture m_texture;

    /** @brief Called to notify that the rendering process starts */
    virtual void on_render() { }

    /** @brief Compute the position of a content based on its alignment */
    SDL_Rect compute_alignment(const SDL_Rect& content_size);

  private:
    /** @brief Indicate if the widget texture must be updated for next rendering */
    bool m_is_update_needed;
};

} // namespace widgets

#endif // GAME_WIDGET_H
