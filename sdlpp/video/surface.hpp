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

#ifndef SDLPP_VIDEO_SURFACE_HPP
#define SDLPP_VIDEO_SURFACE_HPP

#include "../core/error.hpp"
#include "color.hpp"
#include <SDL_surface.h>
#include <memory>

namespace sdl {
template<typename Deleter>
struct basic_surface {
private:
    std::unique_ptr<SDL_Surface, Deleter> surface;
    template<typename T> friend class basic_surface;
public:
    basic_surface() = default;
    basic_surface(SDL_Surface* surface): surface(surface) {}
    basic_surface(const std::string& bmp_filename) {
        load_bmp(bmp_filename);
    }

    void fill(const color& c) {
        SDL_FillRect(surface.get(), nullptr, SDL_MapRGBA(surface->format, c.r, c.g, c.b, c.a));
    }

    void load_bmp(const std::string& filename) {
        surface.reset(SDL_LoadBMP(filename.c_str()));

        if(surface == nullptr) {
            throw error("Failed to load Bitmap " + filename + std::string("\nMore information: ") + SDL_GetError());
        }
    }

    template<typename OtherDeleter>
    void blit(const basic_surface<OtherDeleter>& to) {
        auto status = SDL_BlitSurface(to.surface.get(), nullptr, surface.get(), nullptr);
        if(status < 0) {
            throw error();
        }
    }

    bool is_valid() const noexcept {
        return surface != nullptr;
    }
};

struct surface_deleter {
    void operator()(SDL_Surface* surface) const noexcept {
        SDL_FreeSurface(surface);
        surface = nullptr;
    }
};

struct surface_viewer {
    void operator()(SDL_Surface*) const noexcept {}
};

using surface      = basic_surface<surface_deleter>;
using surface_view = basic_surface<surface_viewer>;
} // sdl

#endif // SDLPP_VIDEO_SURFACE_HPP
