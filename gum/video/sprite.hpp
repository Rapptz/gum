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

#ifndef GUM_VIDEO_SPRITE_HPP
#define GUM_VIDEO_SPRITE_HPP

#include <gum/video/texture.hpp>
#include <gum/video/rect.hpp>
#include <gum/video/vector.hpp>

namespace sdl {
enum class flip : int {
    none       = SDL_FLIP_NONE,
    vertical   = SDL_FLIP_VERTICAL,
    horizontal = SDL_FLIP_HORIZONTAL,
    diagonal   = SDL_FLIP_VERTICAL | SDL_FLIP_HORIZONTAL
};

struct sprite {
private:
    rect subtex;                            // area of the texture used to render
    rect destination;                       // stores the location amongst other things
    vector center;                          // the center of the sprite
    double angle = 0;                       // rotation in degrees
    const texture* tex = nullptr;           // non owning
    SDL_RendererFlip flip_ = SDL_FLIP_NONE; // the flip position
public:
    sprite() = default;
    sprite(const texture& tex) {
        texture(tex);
    }

    sprite(const texture& tex, const rect& area) noexcept: subtex(area), tex(&tex) {
        destination.w = area.w;
        destination.h = area.h;
    }

    void texture(const texture& tex, bool recalculate = true) {
        this->tex = &tex;
        // sets the area of the texture to the entire texture
        if(recalculate) {
            auto&& texture_size = tex.size();
            subtex.x = 0;
            subtex.y = 0;
            subtex.w = texture_size.x;
            subtex.h = texture_size.y;
            destination.w = texture_size.x;
            destination.h = texture_size.y;
        }
    }

    auto texture() const noexcept -> decltype(tex) {
        return tex;
    }

    void subtexture(const rect& area) noexcept {
        subtex = area;
        destination.w = area.w;
        destination.h = area.h;
    }

    rect subtexture() const noexcept {
        return subtex;
    }

    void position(int x, int y) noexcept {
        destination.x = x;
        destination.y = y;
    }

    void position(const vector& pos) noexcept {
        position(pos.x, pos.y);
    }

    vector position() const noexcept {
        return { destination.x, destination.y };
    }

    void move(int x, int y) noexcept {
        destination.x += x;
        destination.y += y;
    }

    void move(const vector& pos) noexcept {
        move(pos.x, pos.y);
    }

    void rotation(double degrees) noexcept {
        angle = degrees;
    }

    double rotation() const noexcept {
        return angle;
    }

    void rotate(double degrees) noexcept {
        angle += degrees;
    }

    void origin(int x, int y) noexcept {
        center.x = x;
        center.y = y;
    }

    void origin(const vector& center) noexcept {
        this->center = center;
    }

    vector origin() const noexcept {
        return center;
    }

    void flip(sdl::flip f) noexcept {
        flip_ = static_cast<SDL_RendererFlip>(f);
    }

    sdl::flip flip() const noexcept {
        return static_cast<sdl::flip>(flip_);
    }

    void draw(SDL_Renderer* render) const {
        // error reporting is suppressed for performance reasons
        SDL_RenderCopyEx(render, tex ? tex->data() : nullptr, &subtex, &destination, angle, &center, flip_);
    }
};
} // sdl

#endif // GUM_VIDEO_SPRITE_HPP
