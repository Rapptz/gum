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

#ifndef GUM_VIDEO_WINDOW_HPP
#define GUM_VIDEO_WINDOW_HPP

#include "../core/error.hpp"
#include "traits.hpp"
#include <SDL_video.h>
#include <SDL_render.h>
#include <memory>
#include <string>
#include <cstdint>

namespace sdl {
struct window_deleter {
    void operator()(SDL_Window* window) const noexcept {
        if(window != nullptr) {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
    }
};

struct renderer_deleter {
    void operator()(SDL_Renderer* renderer) const noexcept {
        if(renderer != nullptr) {
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }
    }
};

namespace renderer {
enum : uint32_t {
    software       = SDL_RENDERER_SOFTWARE,
    accelerated    = SDL_RENDERER_ACCELERATED,
    present_vsync  = SDL_RENDERER_PRESENTVSYNC,
    target_texture = SDL_RENDERER_TARGETTEXTURE,
};
} // renderer

struct window {
private:
    std::unique_ptr<SDL_Window, window_deleter> ptr;
    std::unique_ptr<SDL_Renderer, renderer_deleter> render;
public:
    static const auto npos     = SDL_WINDOWPOS_UNDEFINED;
    static const auto centered = SDL_WINDOWPOS_CENTERED;

    enum : uint32_t {
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


    window(const std::string& title, const SDL_DisplayMode& display, uint32_t flag = 0):
        window(title, display.w, display.h, flag) {}

    window(const std::string& title, int width, int height, uint32_t flag = 0):
    ptr(SDL_CreateWindow(title.c_str(), npos, npos, width, height, flag)) {
        if(ptr == nullptr) {
            GUM_ERROR_HANDLER();
        }
        render.reset(SDL_CreateRenderer(ptr.get(), -1, renderer::accelerated));

        if(render == nullptr) {
            GUM_ERROR_HANDLER();
        }
    }

    bool is_open() const noexcept {
        return ptr != nullptr;
    }

    void clear(const colour& c = colour::black) {
        SDL_SetRenderDrawColor(render.get(), c.r, c.g, c.b, c.a);
        SDL_RenderClear(render.get());
    }

    SDL_Window* data() const noexcept {
        return ptr.get();
    }

    SDL_Renderer* renderer() const noexcept {
        return render.get();
    }

    template<typename Drawable>
    void draw(Drawable& drawable) {
        static_assert(is_renderer_drawable<Drawable>::value, "Must provide a void draw(SDL_Renderer*) member function");
        drawable.draw(render.get());
    }

    float brightness() const noexcept {
        return SDL_GetWindowBrightness(ptr.get());
    }

    void brightness(float bright) {
        if(SDL_SetWindowBrightness(ptr.get(), bright)) {
            GUM_ERROR_HANDLER();
        }
    }

    int id() const noexcept {
        return SDL_GetWindowID(ptr.get());
    }

    uint32_t flags() const noexcept {
        return SDL_GetWindowFlags(ptr.get());
    }

    void grab_input(bool b) noexcept {
        SDL_SetWindowGrab(ptr.get(), b == true ? SDL_TRUE : SDL_FALSE);
    }

    bool is_input_grabbed() const noexcept {
        return SDL_GetWindowGrab(ptr.get());
    }

    void close() noexcept {
        ptr.reset(nullptr);
    }

    void display() noexcept {
        SDL_RenderPresent(render.get());
    }
};
} // sdl

#endif // GUM_VIDEO_WINDOW_HPP
