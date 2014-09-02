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

#ifndef GUM_VIDEO_RECTANGLE_HPP
#define GUM_VIDEO_RECTANGLE_HPP

#include "rect.hpp"
#include "vector.hpp"
#include "colour.hpp"

namespace sdl {
struct rectangle {
private:
    rect out;
    rect shape;
    colour fill_c = colour::white;
    colour out_c = colour::white;

    void update_shape_area() noexcept {
        shape.w = out.w - 2;
        shape.h = out.h - 2;
    }
public:
    rectangle(int width, int height) noexcept: out(0, 0, width, height), shape(1, 1, width - 1, height - 1) {}
    rectangle(vector size = { 0, 0 }) noexcept: rectangle(size.x, size.y) {}

    void position(int x, int y) noexcept {
        out.x   = x < 0 ? 0 : x;
        out.y   = y < 0 ? 0 : y;
        shape.x = out.x + 1;
        shape.y = out.y + 1;
        update_shape_area();
    }

    void position(const vector& pos) noexcept {
        position(pos.x, pos.y);
    }

    vector position() const noexcept {
        return { out.x, out.y };
    }

    void size(int width, int height) noexcept {
        out.w = width < 0 ? 0 : width;
        out.h = height < 0 ? 0 : height;
        update_shape_area();
    }

    void size(const vector& pos) noexcept {
        size(pos.x, pos.y);
    }

    vector size() const noexcept {
        return { out.w, out.h };
    }

    void fill(colour c) noexcept {
        fill_c = std::move(c);
    }

    colour fill() const noexcept {
        return fill_c;
    }

    void outline(colour c) noexcept {
        out_c = std::move(c);
    }

    colour outline() const noexcept {
        return out_c;
    }

    void draw(SDL_Renderer* render) {
        // handle the outline first
        SDL_SetRenderDrawColor(render, out_c.r, out_c.g, out_c.b, out_c.a);
        SDL_RenderDrawRect(render, &out);

        // set the fill colour
        SDL_SetRenderDrawColor(render, fill_c.r, fill_c.g, fill_c.b, fill_c.a);
        SDL_RenderFillRect(render, &shape);
    }
};
} // sdl

#endif // GUM_VIDEO_RECTANGLE_HPP
