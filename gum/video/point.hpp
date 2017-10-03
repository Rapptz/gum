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

#ifndef GUM_VIDEO_POINT_HPP
#define GUM_VIDEO_POINT_HPP

#include <gum/core/config.hpp>
#include <gum/video/colour.hpp>

namespace sdl {
struct point : SDL_Point {
private:
    colour c = colour::white();
public:
    point(int x = 0, int y = 0) noexcept: SDL_Point{x, y} {}

    void fill(colour c) noexcept {
        this->c = std::move(c);
    }

    colour fill() const noexcept {
        return c;
    }

    void draw(SDL_Renderer* render) {
        SDL_SetRenderDrawColor(render, c.r, c.g, c.b, c.a);
        SDL_RenderDrawPoint(render, x, y);
    }
};
} // sdl

#endif // GUM_VIDEO_POINT_HPP
