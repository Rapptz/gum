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

#ifndef SDLPP_VIDEO_WINDOW_HPP
#define SDLPP_VIDEO_WINDOW_HPP

#include "surface.hpp"
#include <SDL_video.h>
#include <string>
#include <cstdint>

namespace sdl {
struct window {
private:
    std::unique_ptr<SDL_Window, decltype(SDL_DestroyWindow)*> ptr;
    surface_view surf;
    public:
        static const auto npos     = SDL_WINDOWPOS_UNDEFINED;
        static const auto centered = SDL_WINDOWPOS_CENTERED;

        enum flags : uint32_t {
            fullscreen         = SDL_WINDOW_FULLSCREEN,
            fullscreen_desktop = SDL_WINDOW_FULLSCREEN_DESKTOP,
            opengl             = SDL_WINDOW_OPENGL,
            hidden             = SDL_WINDOW_HIDDEN,
            borderless         = SDL_WINDOW_BORDERLESS,
            resizable          = SDL_WINDOW_RESIZABLE,
            minimized          = SDL_WINDOW_MINIMIZED,
            maximized          = SDL_WINDOW_MAXIMIZED,
            input_grabbed      = SDL_WINDOW_INPUT_GRABBED,
            highdpi            = SDL_WINDOW_ALLOW_HIGHDPI
        };

        window(const std::string& title, int width, int height, uint32_t f = 0):
        ptr(SDL_CreateWindow(title.c_str(), npos, npos, width, height, f), SDL_DestroyWindow) {
            if(ptr == nullptr) {
                throw error();
            }

            surf = surface_view(SDL_GetWindowSurface(ptr.get()));
        }

        bool is_open() const noexcept {
            return ptr != nullptr;
        }

        void fill(const color& c) {
            surf.fill(c);
        }

        SDL_Window* data() const noexcept {
            return ptr.get();
        }

        void close() {
            ptr.reset(nullptr);
        }

        template<typename Deleter>
        void display(const basic_surface<Deleter>& s) {
            surf.blit(s);
        }

        void update() {
            SDL_UpdateWindowSurface(ptr.get());
        }
};
} // sdl

#endif // SDLPP_VIDEO_WINDOW_HPP
