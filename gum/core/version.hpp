// gum
// Copyright (C) 2014 Rapptz

// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.

// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:

// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#ifndef GUM_CORE_VERSION_HPP
#define GUM_CORE_VERSION_HPP

#include <gum/core/config.hpp>
#include <cstdint>

namespace sdl {
struct compiled_version {
    uint8_t major = SDL_MAJOR_VERSION;
    uint8_t minor = SDL_MINOR_VERSION;
    uint8_t patch = SDL_PATCHLEVEL;

    constexpr compiled_version() = default;
    static constexpr unsigned single_number() noexcept {
        return SDL_COMPILEDVERSION;
    }

    static constexpr bool is_at_least(uint8_t mj, uint8_t mi, uint8_t pt = 0) noexcept {
        return SDL_VERSION_ATLEAST(mj, mi, pt);
    }
};

struct linked_version {
    uint8_t major;
    uint8_t minor;
    uint8_t patch;

    linked_version() noexcept {
        SDL_version temp;
        SDL_GetVersion(&temp);
        major = temp.major;
        minor = temp.minor;
        patch = temp.patch;
    }
};
} // sdl

#endif // GUM_CORE_VERSION_HPP
