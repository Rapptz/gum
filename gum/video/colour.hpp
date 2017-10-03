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

#ifndef GUM_VIDEO_COLOUR_HPP
#define GUM_VIDEO_COLOUR_HPP

#include <gum/core/config.hpp>
#include <cstdint>

namespace sdl {
struct colour : SDL_Color {
    colour() noexcept: SDL_Color{0, 0, 0, 255} {}
    colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) noexcept: SDL_Color{r, g, b, a} {}

    static colour red() noexcept {
        static const colour red = { 255, 0, 0, 255 };
        return red;
    }

    static colour green() noexcept {
        static const colour green = { 0, 255, 0, 255 };
        return green;
    }

    static colour blue() noexcept {
        static const colour blue = { 0, 0, 255, 255 };
        return blue;
    }

    static colour black() noexcept {
        static const colour black = { 0, 0, 0, 255 };
        return black;
    }

    static colour white() noexcept {
        static const colour white = { 255, 255, 255, 255 };
        return white;
    }

    static colour transparent() noexcept {
        static const colour transparent  { 0, 0, 0, 0 };
        return transparent;
    }

    static colour yellow() noexcept {
        static const colour yellow = { 255, 255, 0, 255 };
        return yellow;
    }

    static colour magenta() noexcept {
        static const colour magenta = { 255, 0, 255, 255 };
        return magenta;
    }

    static colour cyan() noexcept {
        static const colour cyan = { 0, 255, 255, 255 };
        return cyan;
    }

};

using color = colour;
} // sdl

#endif // GUM_VIDEO_COLOUR_HPP
