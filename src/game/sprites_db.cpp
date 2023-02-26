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

#include "sprites_db.h"

#include <filesystem>

namespace game
{

/** @brief Constructor */
sprites_db::sprites_db(sdl::renderer& renderer) : m_renderer(renderer), m_animations() { }

/** @brief Load an animation from a path */
bool sprites_db::load_animation(const std::string& name, const std::string& path, const std::string& base_name)
{
    // Build corresponding regex
    std::string regex_str = base_name + "_([0-9]+)\\..*";
    std::regex  regex(regex_str.c_str());

    // Load animation
    return load_animation(name, path, regex, 0);
}

/** @brief Load an animation from a path */
bool sprites_db::load_animation(const std::string& name, const std::string& path, const std::regex& filter, unsigned int capture_group)
{
    bool                ret = true;
    widgets::image_list animation;

    // Browse directory
    for (const auto& dir_entry : std::filesystem::directory_iterator(std::filesystem::path(path)))
    {
        // Apply filter
        std::smatch match;
        std::string file = dir_entry.path().filename().string();
        if (std::regex_match(file, match, filter))
        {
            // Check match
            if (match.size() > capture_group)
            {
                // Extract number
                std::string img_number = match[capture_group + 1].str();
                int         number     = std::atoi(img_number.c_str());

                // Load image
                auto part = std::make_unique<widgets::image>(m_renderer);
                ret       = ret && part->load(dir_entry.path().string());
                if (ret)
                {
                    animation.emplace_back(number, std::move(part));
                }
            }
        }
    }
    ret = ret && !animation.empty();
    if (ret)
    {
        // Sort animation
        animation.sort([](const widgets::image_anim& a, const widgets::image_anim& b) { return (a.first < b.first); });

        // Save animation
        m_animations[name] = std::move(animation);
    }

    return ret;
}

/** @brief Get an animation */
const widgets::image_list* sprites_db::get(const std::string& name)
{
    const widgets::image_list* anim      = nullptr;
    auto                       iter_anim = m_animations.find(name);
    if (iter_anim != m_animations.end())
    {
        anim = &iter_anim->second;
    }
    return anim;
}

} // namespace game
