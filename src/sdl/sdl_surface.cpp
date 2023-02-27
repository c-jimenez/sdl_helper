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

#include "sdl_surface.h"

#include <SDL2/SDL_image.h>

namespace sdl
{

/** @brief Create a surface */
surface create_surface(int width, int height, int depth, Uint32 r_mask, Uint32 g_mask, Uint32 b_mask, Uint32 a_mask)
{
    return sdl_surface::create_surface(width, height, depth, r_mask, g_mask, b_mask, a_mask);
}

/** @brief Create a surface */
surface create_surface(int width, int height, int depth, Uint32 format)
{
    return sdl_surface::create_surface(width, height, depth, format);
}

/** @brief Create a surface */
surface sdl_surface::create_surface(int width, int height, int depth, Uint32 r_mask, Uint32 g_mask, Uint32 b_mask, Uint32 a_mask)
{
    surface      instance;
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, depth, r_mask, g_mask, b_mask, a_mask);
    if (surface)
    {
        auto p = new sdl_surface(surface);
        instance.reset(p);
    }
    return instance;
}

/** @brief Create a surface */
surface sdl_surface::create_surface(int width, int height, int depth, Uint32 format)
{
    surface      instance;
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, depth, format);
    if (surface)
    {
        auto p = new sdl_surface(surface);
        instance.reset(p);
    }
    return instance;
}

/** @brief Create a surface from an image file */
surface create_surface(const std::string& file)
{
    return sdl_surface::create_surface(file);
}

/** @brief Create a surface from an image file */
surface sdl_surface::create_surface(const std::string& file)
{
    surface      instance;
    SDL_Surface* surface = IMG_Load(file.c_str());
    if (surface)
    {
        auto p = new sdl_surface(surface);
        instance.reset(p);
    }
    return instance;
}

/** @brief Duplicates the surface */
surface sdl_surface::duplicate() const
{
    surface      instance;
    SDL_Surface* surface = SDL_DuplicateSurface(m_handle);
    if (surface)
    {
        auto p = new sdl_surface(surface);
        instance.reset(p);
    }
    return instance;
}

/** @brief Destructor */
sdl_surface::~sdl_surface()
{
    if (m_is_owner)
    {
        SDL_FreeSurface(m_handle);
    }
}

/** @brief Constructor */
sdl_surface::sdl_surface(SDL_Surface* handle) : m_handle(handle), m_is_owner(true) { }

/** @brief Constructor */
sdl_surface::sdl_surface(SDL_Surface* handle, bool is_owner) : m_handle(handle), m_is_owner(is_owner) { }

/** @brief Get the size of the surface */
void sdl_surface::get_size(int& w, int& h)
{
    w = m_handle->w;
    h = m_handle->h;
}

/** @brief Get the size of the surface */
SDL_Rect sdl_surface::get_size()
{
    return SDL_Rect{0, 0, m_handle->w, m_handle->h};
}

/** @brief Set an additional color value used in blit operations */
bool sdl_surface::set_color_mod(Uint8 r, Uint8 g, Uint8 b)
{
    return (SDL_SetSurfaceColorMod(m_handle, r, g, b) == 0);
}

/** @brief Get the additional color value used in blit operations */
bool sdl_surface::get_color_mod(Uint8& r, Uint8& g, Uint8& b)
{
    return (SDL_GetSurfaceColorMod(m_handle, &r, &g, &b) == 0);
}

/** @brief Set an additional alpha value used in blit operations */
bool sdl_surface::set_alpha_mod(Uint8 alpha)
{
    return (SDL_SetSurfaceAlphaMod(m_handle, alpha) == 0);
}

/** @brief Get the additional alpha value used in blit operations */
bool sdl_surface::get_alpha_mod(Uint8& alpha)
{
    return (SDL_GetSurfaceAlphaMod(m_handle, &alpha) == 0);
}

/** @brief Set the blend mode used for blit operations */
bool sdl_surface::set_blend_mod(SDL_BlendMode mode)
{
    return (SDL_SetSurfaceBlendMode(m_handle, mode) == 0);
}

/** @brief Get the blend mode used for blit operations */
bool sdl_surface::get_blend_mod(SDL_BlendMode& mode)
{
    return (SDL_GetSurfaceBlendMode(m_handle, &mode) == 0);
}

/** @brief Set the clipping rectangle for the destination surface in a blit */
bool sdl_surface::set_clip_rect(const SDL_Rect* rect)
{
    return (SDL_SetClipRect(m_handle, rect) == 0);
}

/** @brief Get the clipping rectangle for the destination surface in a blit */
void sdl_surface::get_clip_rect(SDL_Rect* rect)
{
    SDL_SetClipRect(m_handle, rect);
}

/** @brief Fill a rectangle with a specified color */
bool sdl_surface::fill_rect(const SDL_Rect& rect, Uint32 color)
{
    return (SDL_FillRect(m_handle, &rect, color) == 0);
}

/** @brief Fill a rectangle with a specified color */
bool sdl_surface::fill_rect(const SDL_Rect& rect, const SDL_Color& color)
{
    return fill_rect(rect, SDL_MapRGB(m_handle->format, color.r, color.g, color.b));
}

/** @brief Fill a list of rectangles with a specified color */
bool sdl_surface::fill_rects(const std::vector<SDL_Rect>& rects, Uint32 color)
{
    return fill_rects(&rects[0], static_cast<int>(rects.size()), color);
}

/** @brief Fill a list of rectangles with a specified color */
bool sdl_surface::fill_rects(const SDL_Rect* rects, int count, Uint32 color)
{
    return (SDL_FillRects(m_handle, rects, count, color) == 0);
}

/** @brief Fill a list of rectangles with a specified color */
bool sdl_surface::fill_rects(const std::vector<SDL_Rect>& rects, const SDL_Color& color)
{
    return fill_rects(&rects[0], static_cast<int>(rects.size()), color);
}

/** @brief Fill a list of rectangles with a specified color */
bool sdl_surface::fill_rects(const SDL_Rect* rects, int count, const SDL_Color& color)
{
    return fill_rects(rects, count, SDL_MapRGB(m_handle->format, color.r, color.g, color.b));
}

/** @brief Performs a fast blit from the source surface to the destination surface */
bool sdl_surface::blit(const surface& src, const SDL_Rect* src_rect, SDL_Rect* dst_rect)
{
    return (SDL_BlitSurface(src->m_handle, src_rect, m_handle, dst_rect) == 0);
}

/** @brief Performs a blit from the source surface to the destination surface with scaling */
bool sdl_surface::blit_scaled(const surface& src, const SDL_Rect* src_rect, SDL_Rect* dst_rect)
{
    return (SDL_BlitScaled(src->m_handle, src_rect, m_handle, dst_rect) == 0);
}

} // namespace sdl
