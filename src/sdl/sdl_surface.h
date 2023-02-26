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

#ifndef SDL_SURFACE_H
#define SDL_SURFACE_H

#include <SDL2/SDL.h>
#include <array>
#include <memory>
#include <string>
#include <vector>

namespace sdl
{

// Forward declarations
class sdl_renderer;
class sdl_surface;
class sdl_window;
class sdl_font;

/** @brief SDL surface */
using surface = std::shared_ptr<sdl_surface>;

/**
 * @brief Create a surface
 * @param width The width in pixels of the surface to create
 * @param height The height in pixels of the surface to create
 * @param depth The depth in bits of the surface to create
 * @param r_mask The red mask of the surface to create
 * @param g_mask The green mask of the surface to create
 * @param b_mask The blue mask of the surface to create
 * @param a_mask The alpha mask of the surface to create
 * @return SDL surface object if the creation was successfull, nullptr otherwise
 */
surface create_surface(int width, int height, int depth, Uint32 r_mask, Uint32 g_mask, Uint32 b_mask, Uint32 a_mask);

/**
 * @brief Create a surface
 * @param width The width in pixels of the surface to create
 * @param height The height in pixels of the surface to create
 * @param depth The depth in bits of the surface to create
 * @param format The color format of the surface to create
 * @return SDL surface object if the creation was successfull, nullptr otherwise
 */
surface create_surface(int width, int height, int depth, Uint32 format);

/**
 * @brief Create a surface from an image file
 * @param file Path to the image file
 * @return SDL surface object if the creation was successfull, nullptr otherwise
 */
surface create_surface(const std::string& file);

/** @brief Wrapper for SDL surface */
class sdl_surface
{
    // SDL window wrapper is friend to allow using surface as icon
    friend class sdl_window;
    // SDL renderer wrapper is friend to allow constructing a texture from the surface
    friend class sdl_renderer;
    // SDL font wrapper is friend to allow constructing a surface from the font
    friend class sdl_font;

  public:
    /**
     * @brief Create a surface
     * @param width The width in pixels of the surface to create.
     * @param height The height in pixels of the surface to create.
     * @param depth The depth in bits of the surface to create.
     * @param r_mask The red mask of the surface to create.
     * @param g_mask The green mask of the surface to create.
     * @param b_mask The blue mask of the surface to create.
     * @param a_mask The alpha mask of the surface to create.
     * @return SDL surface object if the creation was successfull, nullptr otherwise
     */
    static surface create_surface(int width, int height, int depth, Uint32 r_mask, Uint32 g_mask, Uint32 b_mask, Uint32 a_mask);

    /**
     * @brief Create a surface
     * @param width The width in pixels of the surface to create
     * @param height The height in pixels of the surface to create
     * @param depth The depth in bits of the surface to create
     * @param format The color format of the surface to create
     * @return SDL surface object if the creation was successfull, nullptr otherwise
     */
    static surface create_surface(int width, int height, int depth, Uint32 format);

    /**
     * @brief Create a surface from an image file
     * @param file Path to the image file
     * @return SDL surface object if the creation was successfull, nullptr otherwise
     */
    static surface create_surface(const std::string& file);

    /** 
     * @brief Duplicates the surface
     * @return New surface identical to the existing surface
     */
    surface duplicate() const;

    /** @brief Destructor */
    ~sdl_surface();

    /** @brief Get the size of the surface */
    void get_size(int& w, int& h);
    /** @brief Get the size of the surface */
    SDL_Rect get_size();

    /** @brief Set an additional color value used in blit operations */
    bool set_color_mod(Uint8 r, Uint8 g, Uint8 b);
    /** @brief Get the additional color value used in blit operations */
    bool get_color_mod(Uint8& r, Uint8& g, Uint8& b);

    /** @brief Set an additional alpha value used in blit operations */
    bool set_alpha_mod(Uint8 alpha);
    /** @brief Get the additional alpha value used in blit operations */
    bool get_alpha_mod(Uint8& alpha);

    /** @brief Set the blend mode used for blit operations */
    bool set_blend_mod(SDL_BlendMode mode);
    /** @brief Get the blend mode used for blit operations */
    bool get_blend_mod(SDL_BlendMode& mode);

    /** @brief Set the clipping rectangle for the destination surface in a blit */
    bool set_clip_rect(const SDL_Rect* rect);
    /** @brief Get the clipping rectangle for the destination surface in a blit */
    void get_clip_rect(SDL_Rect* rect);

    /** @brief Fill a rectangle with a specified color */
    bool fill_rect(const SDL_Rect& rect, Uint32 color);
    /** @brief Fill a rectangle with a specified color */
    bool fill_rect(const SDL_Rect& rect, const SDL_Color& color);

    /** @brief Fill a list of rectangles with a specified color */
    template <size_t COUNT>
    bool fill_rects(const std::array<SDL_Rect, COUNT>& rects, Uint32 color)
    {
        return fill_rects(&rects[0], static_cast<int>(COUNT), color);
    }
    /** @brief Fill a list of rectangles with a specified color */
    bool fill_rects(const std::vector<SDL_Rect>& rects, Uint32 color);
    /** @brief Fill a list of rectangles with a specified color */
    bool fill_rects(const SDL_Rect* rects, int count, Uint32 color);

    /** @brief Fill a list of rectangles with a specified color */
    template <size_t COUNT>
    bool fill_rects(const std::array<SDL_Rect, COUNT>& rects, const SDL_Color& color)
    {
        return fill_rects(&rects[0], static_cast<int>(COUNT), color);
    }
    /** @brief Fill a list of rectangles with a specified color */
    bool fill_rects(const std::vector<SDL_Rect>& rects, const SDL_Color& color);
    /** @brief Fill a list of rectangles with a specified color */
    bool fill_rects(const SDL_Rect* rects, int count, const SDL_Color& color);

    /** @brief Performs a fast blit from the source surface to the destination surface */
    bool blit(const surface& src, const SDL_Rect* src_rect, SDL_Rect* dst_rect);
    /** @brief Performs a blit from the source surface to the destination surface with scaling */
    bool blit_scaled(const surface& src, const SDL_Rect* src_rect, SDL_Rect* dst_rect);

    /** @brief Get the pixel format of the surface */
    const SDL_PixelFormat* get_pixel_format() const { return m_handle->format; }

  private:
    /** @brief SDL handle */
    SDL_Surface* m_handle;
    /** @brief Indicate if this instance is the owner of the handle */
    const bool m_is_owner;

    /** 
     * @brief Constructor 
     * @param handle SDL handle
     */
    sdl_surface(SDL_Surface* handle);

    /** 
     * @brief Constructor 
     * @param handle SDL handle
     * @param is_owner Indicate if this instance is the owner of the handle
     */
    sdl_surface(SDL_Surface* handle, bool is_owner);
};

} // namespace sdl

#endif // SDL_SURFACE_H
