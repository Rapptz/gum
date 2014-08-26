// SDL++
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

#ifndef SDLPP_CORE_VERSION_HPP
#define SDLPP_CORE_VERSION_HPP

#include <SDL_version.h>
#include <cstdint>

namespace sdl {
/**
 * @brief Retrieves the compiled version of SDL.
 * @details This is basically the equivalent to the
 * `SDL_version` struct except it's specifically for
 * fetching the compiled version of the SDL library.
 */
struct compiled_version {
    uint8_t major = SDL_MAJOR_VERSION;    ///< The major version.
    uint8_t minor = SDL_MINOR_VERSION;    ///< The minor version.
    uint8_t patch = SDL_PATCHLEVEL;       ///< The update version.

    /**
     * @brief Default constructor.
     */
    constexpr compiled_version() = default;

    /**
     * @brief Converts the version to a single number.
     * @details This is similar to the `SDL_VERSIONNUM` macro.
     * For example, if the SDL version is 1.2.3 then the single_number
     * version is 1203.
     */
    static constexpr unsigned single_number() noexcept {
        return SDL_COMPILEDVERSION;
    }

    /**
     * @brief Checks if the SDL version is at least a specified version.
     * @details This is useful to check if version is less than a specified
     * version at compile time. For example:
     *
     * @code
     * static_assert(sdl::compiled_version::is_at_least(2, 0), "Must use SDL v2.0 or higher");
     * @endcode
     *
     * @param mj The major version to check against.
     * @param mi The minor version to check against.
     * @param pt The patch level to check against. Defaults to zero.
     * @return `true` if the version is at least as specified, `false` otherwise.
     */
    static constexpr bool is_at_least(uint8_t mj, uint8_t mi, uint8_t pt = 0) noexcept {
        return SDL_VERSION_ATLEAST(mj, mi, pt);
    }
};

/**
 * @brief Retrieves the linked version of SDL.
 * @details This is basically the equivalent to the
 * `SDL_version` struct except it's specifically for
 * fetching the linked version of the SDL library.
 * The linked version is retrieved by calling `SDL_GetVersion`.
 */
struct linked_version {
    uint8_t major;    ///< The major version.
    uint8_t minor;    ///< The minor version.
    uint8_t patch;    ///< The update version.

    /**
     * @brief Default constructor.
     * @details Retrieves the version number as if calling
     * `SDL_GetVersion`.
     */
    linked_version() {
        SDL_version temp;
        SDL_GetVersion(&temp);
        major = temp.major;
        minor = temp.minor;
        patch = temp.patch;
    }
};
} // sdl

#endif // SDLPP_CORE_VERSION_HPP
