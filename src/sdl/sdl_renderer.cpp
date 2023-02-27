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

#include "sdl_renderer.h"

#include <SDL2/SDL_image.h>

namespace sdl
{

/** @brief Destructor */
sdl_renderer::~sdl_renderer()
{
    SDL_DestroyRenderer(m_handle);
}

/** @brief Constructor */
sdl_renderer::sdl_renderer(SDL_Renderer* handle) : m_handle(handle) { }

/** @brief Get information about a rendering context */
bool sdl_renderer::get_info(SDL_RendererInfo& info) const
{
    return (SDL_GetRendererInfo(m_handle, &info) == 0);
}

/** @brief Create a texture associated to the renderer */
texture sdl_renderer::create_texture(Uint32 format, int access, int w, int h)
{
    texture      instance;
    SDL_Texture* texture = SDL_CreateTexture(m_handle, format, access, w, h);
    if (texture)
    {
        auto p = new sdl_texture(texture);
        instance.reset(p);
    }
    return instance;
}

/** @brief Create a texture associated to the renderer from a surface */
texture sdl_renderer::create_texture(const surface& surface)
{
    texture      instance;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_handle, surface->m_handle);
    if (texture)
    {
        auto p = new sdl_texture(texture);
        instance.reset(p);
    }
    return instance;
}

/** @brief Create a texture associated to the renderer from an image file */
texture sdl_renderer::create_texture(const std::string& file)
{
    texture      instance;
    SDL_Texture* texture = IMG_LoadTexture(m_handle, file.c_str());
    if (texture)
    {
        auto p = new sdl_texture(texture);
        instance.reset(p);
    }
    return instance;
}

/** @brief Present the renderer to update the screen */
void sdl_renderer::present()
{
    SDL_RenderPresent(m_handle);
}

/** @brief Clear the contents of the renderer */
bool sdl_renderer::clear()
{
    return (SDL_RenderClear(m_handle) == 0);
}

/** @brief Get the rectangle in which the renderer can draw */
SDL_Rect sdl_renderer::get_draw_rect() const
{
    SDL_Rect rect{0, 0, 0, 0};
    SDL_GetRendererOutputSize(m_handle, &rect.w, &rect.h);
    return rect;
}

/** @brief Set the texture as the current target for drawing */
bool sdl_renderer::set_target(texture& texture)
{
    return (SDL_SetRenderTarget(m_handle, texture->m_handle) == 0);
}

/** @brief Restore the renderer as the current target for drawing */
bool sdl_renderer::restore_target()
{
    return (SDL_SetRenderTarget(m_handle, nullptr) == 0);
}

/** @brief Push a texture as the current target for drawing on the texture stack */
bool sdl_renderer::push_texture(texture& texture)
{
    bool ret = set_target(texture);
    if (ret)
    {
        m_texture_stack.push(texture);
    }
    return ret;
}
/** @brief Pop the current texture from the texture stack */
bool sdl_renderer::pop_texture()
{
    bool ret = false;
    if (!m_texture_stack.empty())
    {
        m_texture_stack.pop();
        if (m_texture_stack.empty())
        {
            ret = restore_target();
        }
        else
        {
            ret = set_target(m_texture_stack.top());
        }
    }
    return ret;
}

/** @brief Set the blend mode */
bool sdl_renderer::set_blend_mode(SDL_BlendMode blend_mode)
{
    return (SDL_SetRenderDrawBlendMode(m_handle, blend_mode) == 0);
}

/** @brief Set the draw color */
bool sdl_renderer::set_draw_color(const SDL_Color& color)
{
    return set_draw_color(color.r, color.g, color.b, color.a);
}

/** @brief Set the draw color */
bool sdl_renderer::set_draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    return (SDL_SetRenderDrawColor(m_handle, r, g, b, a) == 0);
}

/** @brief Draw a point */
bool sdl_renderer::draw_point(const SDL_Point& p)
{
    return draw_point(p.x, p.y);
}

/** @brief Draw a point */
bool sdl_renderer::draw_point(int x, int y)
{
    return (SDL_RenderDrawPoint(m_handle, x, y) == 0);
}

/** @brief Draw a list of points */
bool sdl_renderer::draw_points(const std::vector<SDL_Point>& points)
{
    return draw_points(&points[0], static_cast<int>(points.size()));
}

/** @brief Draw a list of points */
bool sdl_renderer::draw_points(const SDL_Point* points, int count)
{
    return (SDL_RenderDrawPoints(m_handle, points, count) == 0);
}

/** @brief Draw a line */
bool sdl_renderer::draw_line(const SDL_Point& p1, const SDL_Point& p2)
{
    return draw_line(p1.x, p1.y, p2.x, p2.y);
}

/** @brief Draw a point */
bool sdl_renderer::draw_line(int x1, int y1, int x2, int y2)
{
    return (SDL_RenderDrawLine(m_handle, x1, y1, x2, y2) == 0);
}

/** @brief Draw lines between points */
bool sdl_renderer::draw_lines(const std::vector<SDL_Point>& points)
{
    return draw_lines(&points[0], static_cast<int>(points.size()));
}

/** @brief Draw lines between points */
bool sdl_renderer::draw_lines(const SDL_Point* points, int count)
{
    return (SDL_RenderDrawLines(m_handle, points, count) == 0);
}

/** @brief Draw a rectangle */
bool sdl_renderer::draw_rect(const SDL_Rect& rect)
{
    return (SDL_RenderDrawRect(m_handle, &rect) == 0);
}

/** @brief Fill a rectangle */
bool sdl_renderer::fill_rect(const SDL_Rect& rect)
{
    return (SDL_RenderFillRect(m_handle, &rect) == 0);
}

/** @brief Draw a list of rectangles */
bool sdl_renderer::draw_rects(const std::vector<SDL_Rect>& rects)
{
    return draw_rects(&rects[0], static_cast<int>(rects.size()));
}

/** @brief Draw a list of rectangles */
bool sdl_renderer::draw_rects(const SDL_Rect* rects, int count)
{
    return (SDL_RenderDrawRects(m_handle, rects, count) == 0);
}

/** @brief Fill a list of rectangles */
bool sdl_renderer::fill_rects(const std::vector<SDL_Rect>& rects)
{
    return fill_rects(&rects[0], static_cast<int>(rects.size()));
}

/** @brief Fill a list of rectangles */
bool sdl_renderer::fill_rects(const SDL_Rect* rects, int count)
{
    return (SDL_RenderFillRects(m_handle, rects, count) == 0);
}

/** @brief Draw a texture */
bool sdl_renderer::copy(texture& texture, const SDL_Rect* src_rect, const SDL_Rect* dst_rect)
{
    return (SDL_RenderCopy(m_handle, texture->m_handle, src_rect, dst_rect) == 0);
}

/** @brief Draw a texture */
bool sdl_renderer::copy(texture&               texture,
                        const SDL_Rect*        src_rect,
                        const SDL_Rect*        dst_rect,
                        const double           angle,
                        const SDL_Point*       center,
                        const SDL_RendererFlip flip)
{
    return (SDL_RenderCopyEx(m_handle, texture->m_handle, src_rect, dst_rect, angle, center, flip) == 0);
}

} // namespace sdl
