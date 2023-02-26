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

#include "sdl_texture.h"

namespace sdl
{

/** @brief Destructor */
sdl_texture::~sdl_texture()
{
    SDL_DestroyTexture(m_handle);
}

/** @brief Constructor */
sdl_texture::sdl_texture(SDL_Texture* handle) : m_handle(handle) { }

/** @brief Get the format of the texture */
Uint32 sdl_texture::get_format() const
{
    Uint32 format;
    SDL_QueryTexture(m_handle, &format, nullptr, nullptr, nullptr);
    return format;
}

/** @brief Get the access restrictions of the texture */
int sdl_texture::get_access() const
{
    int access;
    SDL_QueryTexture(m_handle, nullptr, &access, nullptr, nullptr);
    return access;
}

/** @brief Get the size of the texture */
SDL_Rect sdl_texture::get_size() const
{
    SDL_Rect size{0, 0, 0, 0};
    SDL_QueryTexture(m_handle, nullptr, nullptr, &size.w, &size.h);
    return size;
}

/** @brief Set the blend mode */
bool sdl_texture::set_blend_mode(SDL_BlendMode blend_mode)
{
    return (SDL_SetTextureBlendMode(m_handle, blend_mode) == 0);
}

} // namespace sdl
