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

#ifndef SDLPP_COLOR_HPP
#define SDLPP_COLOR_HPP

#include <SDL_pixels.h>
#include <cstdint>

namespace sdl {
/**
 * @brief A simple structure representing color
 * @details An alternative to SDL_Color. Made for interacting with
 * the SDL++ API.
 */
struct color {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 255;

    color() = default;
    color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255): r(r), g(g), b(b), a(a) {}

    static const color red;
    static const color green;
    static const color blue;
    static const color black;
    static const color white;
    static const color transparent;
    static const color yellow;
    static const color magenta;
    static const color cyan;
};

const color color::red         = { 255, 0, 0, 255 };
const color color::green       = { 0, 255, 0, 255 };
const color color::blue        = { 0, 0, 255, 255 };
const color color::black       = { 0, 0, 0, 255 };
const color color::white       = { 255, 255, 255, 255 };
const color color::transparent = { 0, 0, 0, 0 };
const color color::yellow      = { 255, 255, 0, 255 };
const color color::magenta     = { 255, 0, 255, 255 };
const color color::cyan        = { 0, 255, 255, 255 };

using colour = color;
} // sdl

#endif // SDLPP_COLOR_HPP
