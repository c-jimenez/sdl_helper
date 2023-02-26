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

#ifndef SDL_TEXTURE_H
#define SDL_TEXTURE_H

#include <SDL2/SDL.h>
#include <memory>

namespace sdl
{

// Forward declarations
class sdl_renderer;
class sdl_texture;

/** @brief SDL texture */
using texture = std::shared_ptr<sdl_texture>;

/** @brief Wrapper for SDL texture */
class sdl_texture
{
    // SDL renderer wrapper is friend to allow constructing a texture
    friend class sdl_renderer;

  public:
    /** @brief Destructor */
    ~sdl_texture();

    /** @brief Get the format of the texture */
    Uint32 get_format() const;
    /** @brief Get the access restrictions of the texture */
    int get_access() const;
    /** @brief Get the size of the texture */
    SDL_Rect get_size() const;

    /** @brief Set the blend mode */
    bool set_blend_mode(SDL_BlendMode blend_mode);

  private:
    /** @brief SDL handle */
    SDL_Texture* m_handle;

    /** 
     * @brief Constructor 
     * @param handle SDL handle
     */
    sdl_texture(SDL_Texture* handle);
};

} // namespace sdl

#endif // SDL_TEXTURE_H
