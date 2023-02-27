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

#ifndef SDL_RENDERER_H
#define SDL_RENDERER_H

#include <SDL2/SDL.h>
#include <array>
#include <memory>
#include <stack>
#include <vector>

#include "sdl_surface.h"
#include "sdl_texture.h"

namespace sdl
{

// Forward declarations
class sdl_renderer;
class sdl_window;

/** @brief SDL renderer */
using renderer = std::shared_ptr<sdl_renderer>;

/** @brief Wrapper for SDL renderer */
class sdl_renderer
{
    // SDL window wrapper is friend to allow constructing a renderer
    friend class sdl_window;

  public:
    /** @brief Destructor */
    ~sdl_renderer();

    /** @brief Get information about a rendering context */
    bool get_info(SDL_RendererInfo& info) const;

    /**
     * @brief Create a texture associated to the renderer
     * @param format Color format
     * @param access Access restrictions
     * @param w Width
     * @param h Height
     * @return SDL texture object if the creation was successfull, nullptr otherwise
     */
    texture create_texture(Uint32 format, int access, int w, int h);

    /**
     * @brief Create a texture associated to the renderer from a surface
     * @param surface Surface to use
     * @return SDL texture object if the creation was successfull, nullptr otherwise
     */
    texture create_texture(const surface& surface);

    /**
     * @brief Create a texture associated to the renderer from an image file
     * @param file Path to the image file
     * @return SDL texture object if the creation was successfull, nullptr otherwise
     */
    texture create_texture(const std::string& file);

    /** @brief Present the renderer to update the screen */
    void present();
    /** @brief Clear the contents of the renderer */
    bool clear();

    /** @brief Get the rectangle in which the renderer can draw */
    SDL_Rect get_draw_rect() const;

    /** @brief Set the texture as the current target for drawing */
    bool set_target(texture& texture);
    /** @brief Restore the renderer as the current target for drawing */
    bool restore_target();
    /** @brief Push a texture as the current target for drawing on the texture stack */
    bool push_texture(texture& texture);
    /** @brief Pop the current texture from the texture stack */
    bool pop_texture();

    /** @brief Set the blend mode */
    bool set_blend_mode(SDL_BlendMode blend_mode);

    /** @brief Set the draw color */
    bool set_draw_color(const SDL_Color& color);
    /** @brief Set the draw color */
    bool set_draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    /** @brief Draw a point */
    bool draw_point(const SDL_Point& p);
    /** @brief Draw a point */
    bool draw_point(int x, int y);

    /** @brief Draw a list of points */
    template <size_t COUNT>
    bool draw_points(const std::array<SDL_Point, COUNT>& points)
    {
        return draw_points(&points[0], static_cast<int>(COUNT));
    }
    /** @brief Draw a list of points */
    bool draw_points(const std::vector<SDL_Point>& points);
    /** @brief Draw a list of points */
    bool draw_points(const SDL_Point* points, int count);

    /** @brief Draw a line */
    bool draw_line(const SDL_Point& p1, const SDL_Point& p2);
    /** @brief Draw a point */
    bool draw_line(int x1, int y1, int x2, int y2);

    /** @brief Draw lines between points */
    template <size_t COUNT>
    bool draw_lines(const std::array<SDL_Point, COUNT>& points)
    {
        return draw_lines(&points[0], static_cast<int>(COUNT));
    }
    /** @brief Draw lines between points */
    bool draw_lines(const std::vector<SDL_Point>& points);
    /** @brief Draw lines between points */
    bool draw_lines(const SDL_Point* points, int count);

    /** @brief Draw a rectangle */
    bool draw_rect(const SDL_Rect& rect);
    /** @brief Fill a rectangle */
    bool fill_rect(const SDL_Rect& rect);

    /** @brief Draw a list of rectangles */
    template <size_t COUNT>
    bool draw_rects(const std::array<SDL_Rect, COUNT>& rects)
    {
        return draw_rects(&rects[0], static_cast<int>(COUNT));
    }
    /** @brief Draw a list of rectangles */
    bool draw_rects(const std::vector<SDL_Rect>& rects);
    /** @brief Draw a list of rectangles */
    bool draw_rects(const SDL_Rect* rects, int count);

    /** @brief Fill a list of rectangles */
    template <size_t COUNT>
    bool fill_rects(const std::array<SDL_Rect, COUNT>& rects)
    {
        return fill_rects(&rects[0], static_cast<int>(COUNT));
    }
    /** @brief Fill a list of rectangles */
    bool fill_rects(const std::vector<SDL_Rect>& rects);
    /** @brief Fill a list of rectangles */
    bool fill_rects(const SDL_Rect* rects, int count);

    /** @brief Draw a texture */
    bool copy(texture& texture, const SDL_Rect* src_rect, const SDL_Rect* dst_rect);
    /** @brief Draw a texture */
    bool copy(texture&               texture,
              const SDL_Rect*        src_rect,
              const SDL_Rect*        dst_rect,
              const double           angle,
              const SDL_Point*       center,
              const SDL_RendererFlip flip);

  private:
    /** @brief SDL handle */
    SDL_Renderer* m_handle;
    /** @brief Stack of target textures */
    std::stack<texture> m_texture_stack;

    /** 
     * @brief Constructor 
     * @param handle SDL handle
     */
    sdl_renderer(SDL_Renderer* handle);
};

} // namespace sdl

#endif // SDL_RENDERER_H
