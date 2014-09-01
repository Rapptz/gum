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

#include <SDL_pixels.h>
#include <cstdint>

namespace sdl {
struct colour : SDL_Color {
    colour() noexcept: SDL_Color{0, 0, 0, 255} {}
    colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) noexcept: SDL_Color{r, g, b, a} {}

    static const colour red;
    static const colour green;
    static const colour blue;
    static const colour black;
    static const colour white;
    static const colour transparent;
    static const colour yellow;
    static const colour magenta;
    static const colour cyan;
};

const colour colour::red         = { 255, 0, 0, 255 };
const colour colour::green       = { 0, 255, 0, 255 };
const colour colour::blue        = { 0, 0, 255, 255 };
const colour colour::black       = { 0, 0, 0, 255 };
const colour colour::white       = { 255, 255, 255, 255 };
const colour colour::transparent = { 0, 0, 0, 0 };
const colour colour::yellow      = { 255, 255, 0, 255 };
const colour colour::magenta     = { 255, 0, 255, 255 };
const colour colour::cyan        = { 0, 255, 255, 255 };

using color = colour;
} // sdl

#endif // GUM_VIDEO_COLOUR_HPP
