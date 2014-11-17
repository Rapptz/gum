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

#ifndef GUM_VIDEO_LINE_HPP
#define GUM_VIDEO_LINE_HPP

#include <gum/video/vector.hpp>
#include <gum/video/colour.hpp>
#include <SDL_render.h>

namespace sdl {
struct line {
private:
    vector one;
    vector two;
    colour c = colour::white();
public:
    line() noexcept = default;
    line(int x1, int y1, int x2, int y2) noexcept: one{x1, y1}, two{x2, y2} {}
    line(const vector& one, const vector& two) noexcept: line(one.x, one.y, two.x, two.y) {}

    void first_point(int x, int y) noexcept {
        one.x = x;
        one.y = y;
    }

    void first_point(const vector& v) noexcept {
        first_point(v.x, v.y);
    }

    vector first_point() const noexcept {
        return one;
    }

    void second_point(int x, int y) noexcept {
        two.x = x;
        two.y = y;
    }

    void second_point(const vector& v) noexcept {
        second_point(v.x, v.y);
    }

    vector second_point() const noexcept {
        return two;
    }

    void fill(colour c) noexcept {
        this->c = std::move(c);
    }

    colour fill() const noexcept {
        return c;
    }

    void draw(SDL_Renderer* render) {
        SDL_SetRenderDrawColor(render, c.r, c.g, c.b, c.a);
        SDL_RenderDrawLine(render, one.x, one.y, two.x, two.y);
    }
};
} // sdl

#endif // GUM_VIDEO_LINE_HPP
