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

#ifndef GUM_VIDEO_TEXTURE_HPP
#define GUM_VIDEO_TEXTURE_HPP

#include "../core/error.hpp"
#include <SDL_render.h>
#include <SDL_surface.h>
#include <memory>

namespace sdl {
struct texture_deleter {
    void operator()(SDL_Texture* tex) const noexcept {
        if(tex != nullptr) {
            SDL_DestroyTexture(tex);
            tex = nullptr;
        }
    }
};

struct surface_deleter {
    void operator()(SDL_Surface* surface) const noexcept {
        if(surface != nullptr) {
            SDL_FreeSurface(surface);
            surface = nullptr;
        }
    }
};

struct texture {
private:
    std::unique_ptr<SDL_Texture, texture_deleter> ptr;
    std::unique_ptr<SDL_Surface, surface_deleter> surface_ptr;
    friend struct window;
public:
    texture() = default;
    texture(const std::string& filename) {
        load_file(filename);
    }

    void load_file(const std::string& filename) {
        surface_ptr.reset(SDL_LoadBMP(filename.c_str()));
        if(surface_ptr == nullptr) {
            GUM_ERROR_HANDLER();
        }
    }

    bool is_texture() const noexcept {
        return ptr != nullptr;
    }

    bool is_surface() const noexcept {
        return surface_ptr != nullptr;
    }

    SDL_Texture* data() const noexcept {
        return ptr.get();
    }

    SDL_Surface* surface() const noexcept {
        return surface_ptr.get();
    }
};
} // sdl

#endif // GUM_VIDEO_TEXTURE_HPP
