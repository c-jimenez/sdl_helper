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

#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL.h>
#include <memory>
#include <string>

#include "sdl_font.h"
#include "sdl_window.h"

namespace sdl
{

// Forward declarations
class sdl_wrapper;

/** @brief SDL wrapper */
using sdl_instance = std::unique_ptr<sdl_wrapper>;

/**
 * @brief Initialize SDL subsystems
 * @param flags Selected subsystems
 * @return SDL wrapper object is the initialization was successfull, false otherwise
 */
sdl_instance init(Uint32 flags);

/**
 * @brief Get the last error description
 * @return Last error description
 */
std::string last_error();

/** @brief Wrapper for SDL initialization */
class sdl_wrapper
{
  public:
    /**
     * @brief Initialize SDL subsystems
     * @param flags Selected subsystems
     * @return SDL wrapper object if the initialization was successfull, nullptr otherwise
     */
    static sdl_instance init(Uint32 flags);

    /** @brief Destructor */
    ~sdl_wrapper();

    /**
     * @brief Get the last error description
     * @return Last error description
     */
    std::string last_error();

  private:
    /** @brief Selected subsystems */
    Uint32 m_flags;

    /** 
     * @brief Constructor 
     * @param flags Selected subsystems
     */
    sdl_wrapper(Uint32 flags);
};

} // namespace sdl

#endif // SDL_H
