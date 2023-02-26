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

#include "sdl.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace sdl
{

/** @brief Initialize SDL subsystems */
sdl_instance init(Uint32 flags)
{
    return sdl_wrapper::init(flags);
}

/** @brief Get the last error description */
std::string last_error()
{
    char err_string[255];
    SDL_GetErrorMsg(err_string, sizeof(err_string));
    return std::string(err_string);
}

/** @brief Initialize SDL subsystems */
sdl_instance sdl_wrapper::init(Uint32 flags)
{
    sdl_instance instance;

    if (SDL_InitSubSystem(flags) == 0)
    {
        if (TTF_Init() == 0)
        {
            if (IMG_Init(-1) != 0)
            {
                auto p = new sdl_wrapper(flags);
                instance.reset(p);
            }
            else
            {
                TTF_Quit();
                SDL_QuitSubSystem(flags);
            }
        }
        else
        {
            SDL_QuitSubSystem(flags);
        }
    }

    return instance;
}

/** @brief Destructor */
sdl_wrapper::~sdl_wrapper()
{
    IMG_Quit();
    TTF_Quit();
    SDL_QuitSubSystem(m_flags);
}

/** @brief Get the last error description */
std::string sdl_wrapper::last_error()
{
    return ::sdl::last_error();
}

/** @brief Constructor */
sdl_wrapper::sdl_wrapper(Uint32 flags) : m_flags(flags) { }

} // namespace sdl
